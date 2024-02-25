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
#include <Cybiko.h>
#include "..\tcplib.h"
#include "..\tcperror.h"

struct module_t main_module;
char display[12][32];
char tmpline[1024];
int lineno=0;
char tmp[64];
char hostvar[64];

long tcpqueue=0;
long exit_application = FALSE;
int flag_new_host = 0;

int dialog_show(char *title, char *text, char *rtn_s, int len);
int html_handler(int tcpqueue, char *data, char *user_data);

void redraw()
{
	int i;

    DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
    DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
    DisplayGraphics_set_font( main_module.m_gfx, mini_normal_font );
    for(i=0; i<12; i++)
	{
		DisplayGraphics_draw_text( main_module.m_gfx, display[i], 0, i*8 );
	}
    DisplayGraphics_show( main_module.m_gfx );
}

#ifdef OLD_REDRAW
void printf(char *s)
{
	sprintf(tmpline, "%d %s", lineno, s);
	strncpy(display[lineno%12], tmpline, 31);
	lineno++;
	redraw();
}
#endif

void printf(char *s)
{
	struct rect_t rect;

	sprintf(tmpline, "%d %s", lineno, s);
	memmove(display[0], display[1], sizeof(display)-32);
	strncpy(display[11], tmpline, 31);
	lineno++;
	/*
	rect.x = 0;
	rect.y = 0;
	rect.w = 160;
	rect.h = 92;
	DisplayGraphics_scroll( main_module.m_gfx, &rect, 0, -8 );
	*/
	DisplayGraphics_scroll( main_module.m_gfx, 0, 0, 160, 97, 0, -8);
	DisplayGraphics_set_color( main_module.m_gfx, CLR_WHITE );
	DisplayGraphics_fill_rect( main_module.m_gfx, 0, 88, 160, 9);
	DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
	DisplayGraphics_draw_text( main_module.m_gfx, display[11], 0, 88 );
    DisplayGraphics_show( main_module.m_gfx );
}

int dialog_show(char *title, char *text, char *rtn_s, int len)
{
    struct cDialog *dialog;
    int rc;

    dialog = (struct cDialog *) calloc(1, sizeof(struct cDialog));
	cDialog_ctor(dialog, title, text, mbOk | mbCancel | mbEdit, len, main_module.m_process);
    cDialog_SetEditText( dialog, rtn_s );
    rc = cDialog_ShowModal(dialog);
    if (rc == mrOk)
    {
        cDialog_GetEditText(dialog, rtn_s);
        rtn_s[len-1]=0;
        rc = 1;
    }
    else
    {
        rc = 0;
    }

    cDialog_dtor(dialog, FREE_MEMORY);
    return rc;
}

//
// cybiko messages handled here
//
int cybiko_handler(struct Message *msg)
{
	//printf("cybiko_handler");

	switch( msg->msgid )
	{
		int key;

		case MSG_SHUTUP: 
		case MSG_QUIT:
			// Processes the system exit signal
			exit_application = TRUE;
			break;
		case MSG_GOTFOCUS: 
			// Redraws the screen
			redraw();
			break;
		case MSG_KEYDOWN: 
			// Processes keyboard messages
			key = Message_get_key_param( msg )->scancode;
			if( key == KEY_ESC )
			{
				//
				// exit the app
				//
				struct Message *ptr_msg;
				tcp_close(tcpqueue); // get out

				//
				// send a quit message to ourselves
				//
				ptr_msg = Message_new(sizeof(struct Message));
				ptr_msg->msgid = MSG_QUIT;
				Message_post(ptr_msg, cWinApp_get_name(main_module.m_process), get_own_id());
			}
			break;
		case MSG_KEYUP: 
			// Processes keyboard messages
			key = Message_get_key_param( msg )->scancode;
			if ( key == KEY_SPACE)
			{
				//
				// select a host to view
				//
				if (dialog_show("TCP-HTML", "Enter a domain name", hostvar, sizeof(hostvar)-1))
				{
					//
					// close the old queue
					//
					if (tcpqueue) tcp_close(tcpqueue);

					//
					// open the new queue
					// html_handler is the proc t ocall on new messages
					//
					tcpqueue = tcp_connect(hostvar, 80, 512, html_handler, 0);
				}
				redraw();
			}
			//
			// this is a hack
			// sends an ACK message to the tcpgate
			// this is defunct since i removed all
			// the gate<-->client acks for speed
			if (key == KEY_A) tcp_ack(tcpqueue);
			break;
		case MSG_USER: //process rf messages
		{
			//printf("MSG_USER");
		}
	}
	return 0;
}

//
// messages from your socket go here
//
int html_handler(int tcpqueue, char *data, char *user_data)
{
	char *s;
	static int inside=1;
	static int x=0;
	static long llen;
	static short len;
	static int quotemode=0;

	//printf("html_handler");

	switch(tcp_msgid(data)) {
		case TCPMSG_WRITE_RESPONSE: 
		{
			// 
			// this is now defunct, i dont do write responses anymore
			//
			//printf("WRITE_RESPONSE");
			tcp_write_accept(data); 
			break;
		}
		case TCPMSG_CLOSE_RESPONSE: 
		{
			//
			// the socket has been closed.
			// this happens at the end of each page
			//
			//printf("CLOSE_RESPONSE");
			tcp_close_accept(data);  // do whatever is necessary behind the scenes
			tcpqueue = 0; // let the rest of the program know we're done
			printf("<CLOSED>");
			break;
		}
		case TCPMSG_FILTER_RESPONSE: 
		{
			//
			// when you make a filter request, you get a filter response
			//
			//printf("FILTER_RESPONSE");
			tcp_filter_accept(data);  // update tcp internals
			//
			// now that you are filtering the data,
			// get the page
			//
			tcp_write(tcp_tcpqueue(data), "GET /index.html HTTP/1.0\n\n", 26);
			//printf("Wrote message!");
			break;
		}
		case TCPMSG_CONNECT_RESPONSE:
		{
			//printf("CONNECT_RESPONSE");
			tcp_connect_accept(data); // update tcp internals
			if (tcp_errno)
			{
				printf("ERROR DETECTED");
				tcp_close(tcp_tcpqueue(data));
				break;
			}
			//
			// now that the connection is established,
			// request HTML filtering
			//
			tcp_filter(tcp_tcpqueue(data), TCP_FILTER_HTML);
			break;
		}
		case TCPMSG_READ_RESPONSE:
		{
			//
			// we got a message, process it
			//
			//printf("READ_RESPONSE");
			tcp_read_accept(data);  // update tcp internals
			s = tcp_getdata(data, &llen); // get the data portion of the message
			len = (short) llen; // convert from long to short
			printf(s); // print the text to the screen
			break;
		}
		default:
		{
			//char t[32];
			//sprintf(t, "%d", tcp_msgid(data));
			//printf(t);
		}
	}
	return 0;
}

long main(int argc, char* argv[], bool start)
{
    int i;
	long cyid;
struct Message *msg;

    init_module(&main_module);

	//
	// ask the user to select a junction.
	//
	cyid = tcp_init(&main_module);

	redraw();
	printf("Press SPACE to select Host");

	//
	// default host
	//
	strcpy(hostvar, "devcybiko.com");

	while(!exit_application)
	{
		//
		// wait forever for a message
		// returns only when a tcp message is encountered
		//
		tcp_get_message(0, cybiko_handler);
	}

EARLY_EXIT:
	return 0L;
}

