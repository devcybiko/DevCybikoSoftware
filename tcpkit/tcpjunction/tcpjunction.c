/**
  * The TCPKIT framework is a set of programs and libraries
  * that allow a set of Cybiko computers to communicate on
  * the internet.
  *
  *  Copyright 2004 by Gregory Smith
  *  (greg@alcorgrp.com)
  *
  *  This program is free software; you can redistribute it and/or
  *  modify it under the terms of the GNU General Public License
  *  as published by the Free Software Foundation; either version 2
  *  of the License, or (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  *
  * @author Gregory Smith (http://www.greg-smith.com, Greg@AlcorGrp.com)
  * @version 1.0
  */
#include <cybiko.h>
#include "..\tcpmsgs.h"
#include "..\tcplib\tcperror.h"

/**
 ** tcpjunction
 **
 **/
#define LINELEN 32
#define USE_CHECKSUM true

struct module_t main_module;
char readbuf[TCPMSG_MESSAGE_MAX+4];
char msgbuf[TCPMSG_MESSAGE_MAX+4];
char tmp[50];
int nchars=0;
int tcpcnt=0;
int cycnt=0;
com_t tty;
char display[10][LINELEN];
char lineno=0;

#define END 0300
#define ESC 0333
#define ESC_END 0334
#define ESC_ESC 0335

void do_nothing(char *s){}
void printf(char *s);

void load(char *filename)
{
	struct Input *in;
	struct FileOutput *out;
	struct Archive *archive = main_module.m_process->module->archive;
	int c;

	sprintf(tmp, "/%s/%s", DEFAULT_DRIVE_NAME, filename);
	TRACE(tmp);

    if (File_exists(tmp)) return;

	printf("You must install");
	printf(filename);
	printf("to continue");
	printf("reboot your cybiko");
	printf("and download it");
	while(1); //wait here forever

	in = Archive_open_Ex(archive, filename);
	out = malloc(sizeof(struct FileOutput));
	FileOutput_ctor_Ex(out,tmp, 1); // create the file

	while(!Input_is_eof(in))
	{
		c = Input_read_byte(in); // this is hanging - why???
		FileOutput_write_byte(out, c);
	}

    FileOutput_dtor(out, FREE_MEMORY);
	Input_dtor(in, FREE_MEMORY);
}

void redraw()
{
	int i;

    DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
    DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
    DisplayGraphics_set_font( main_module.m_gfx, mini_normal_font );
    for(i=0; i<10; i++)
	{
		DisplayGraphics_draw_text( main_module.m_gfx, display[i], 0, i*10 );
	}
    DisplayGraphics_show( main_module.m_gfx );
}

void printf(char *s)
{
	strncpy(display[lineno], s, LINELEN);
	display[lineno][LINELEN-1]=0;
    DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
	DisplayGraphics_draw_text( main_module.m_gfx, display[lineno], 0, 0 );
	redraw();
	lineno++;
	if (lineno == 10) lineno=0;
}

void serial_write(char *buf, int len)
{
    int i;
	int c;

    i=0;
	c = END;
    com_write(tty, c, 0); // clear the buffer
    for(i=0; i<len; i++)
    {
		switch(buf[i]) {
		case END: 
			c = ESC;
			com_write(tty, c, 0);
			c = ESC_END;
			com_write(tty, c, 0);
			break;
		case ESC:
			c = ESC;
			com_write(tty, c, 0);
			c = ESC_ESC;
			com_write(tty, c, 0);
			break;
		default:
			com_write(tty, buf[i], 0);
			break;
		}
    }
	c = END;
    com_write(tty, c, 0); // end the string
}

void serial_flush() {
	int x;
	com_flush(tty);
    while(1)
	{
		x = com_read(tty, 1);
		if (x==-1) return; // nothing to read
	}
}

void serial_read()
{
    int x;
	int true = 1;
	struct tcpgj_header *hdr;
	char end=(char)END;
	char esc=(char)ESC;
	char esc_end=(char)ESC_END;
	char esc_esc=(char)ESC_ESC;
	long sent_checksum;
	long recv_checksum;
	int i;
	char c;

    while(true)
	{
		x = com_read(tty, 1);
		if (x==-1) return; // nothing to read
		if (x == END)
		{
			// end of slp packet
			if (nchars==0) return; //no bytes retrieved

			hdr = (struct tcpgj_header *) readbuf;
			memcpy(&sent_checksum, &hdr->data[nchars-sizeof(*hdr)-4], 4);
			recv_checksum = 0;
			for (i=0; i<nchars-4; i++)
			{
				recv_checksum += readbuf[i];
			}
			//sprintf(tmp, "len=%d sent=%ld recv=%ld", nchars, *sent_checksum, recv_checksum);
			//printf(tmp);

			sprintf(tmp, "len=%d chksum=%ld %ld", nchars, sent_checksum, recv_checksum);
			printf(tmp);
			if (sent_checksum != recv_checksum)
			{
				// send NACK
				serial_flush();
				c = 0x82;
				com_write(tty, c, 0);
				nchars=0;
				continue; //try again to receive it
			}
			// send ACK
			c = 0x81;
			com_write(tty, c, 0);

			send_remote_msg(
				hdr->cyid, 
				hdr->appname,
				(short) hdr->msg_queue,
				0, 
				0, 
				hdr->data,
				nchars-sizeof(*hdr)-4);  // take off the checksum
			nchars=0;
			tcpcnt=tcpcnt+1;
			goto EARLY_EXIT;
		}
		if (x == ESC)
		{
			while((x = com_read(tty, 1)) == -1);
			if (x == ESC_END) x = END;
			else if (x == ESC_ESC) x = ESC;
		}
		if (nchars < sizeof(readbuf))
		{
			readbuf[nchars]=(char)x;
			nchars=nchars+1;
		}
	}
EARLY_EXIT:
	return;
}

void message_loop( struct module_t* ptr_main_module )
{
	bool exit_application = FALSE;

	while( !exit_application )
	{
		struct Message* ptr_message = 
			cWinApp_get_message(
				ptr_main_module->m_process, 
				1, 
				1, 
				MSG_USER );

		if (ptr_message == 0)
			serial_read();
		else switch( ptr_message->msgid )
		{
			case MSG_SHUTUP: // Processes the system exit signal
			case MSG_QUIT:
				exit_application = TRUE;
				break;
			case MSG_GOTFOCUS: // Redraws the screen
				redraw();
				break;
			case MSG_KEYDOWN: // Processes keyboard messages
				if( Message_get_key_param( ptr_message )->scancode == KEY_ESC )
				{
					exit_application = TRUE;
				}
				break;
			case MSG_USER: //process rf messages
			{
				if( Message_has_buffer( ptr_message ) )
				{
					struct Buffer *buffer;
					int len;
					buffer=Message_get_buffer(ptr_message);
					len = Buffer_get_size(buffer);
					Buffer_load(buffer, msgbuf,0,sizeof(msgbuf));
					serial_write(msgbuf, len);
					cycnt=cycnt+1;
					//sprintf(tmp, "cybiko=%d", cycnt);
					//printf(tmp);
				}
				break;
			}
			default: // Processes all unprocessed messages
			cWinApp_defproc( ptr_main_module->m_process, ptr_message );
		} 
		Message_delete( ptr_message );
	}
}

void init()
{
	int i;

    init_module( &main_module );
}

long main( int argc, char* argv[], bool start )
{
	struct COMMConfig config;

	init();

    load("ComPort.dl");

	printf("TCPJunction");

    tty = com_open(COMM_DEV_DEFAULT, 1000);
	com_get_config (tty, &config );
	config.baud_rate = COMM_BAUD_9600;
	com_set_config (tty, &config );

    message_loop( &main_module );
    com_close(tty);

    return 0L;
}
