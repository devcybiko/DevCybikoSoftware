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
char portvar[64];
int g_port=23;
char line[32];
int cnt=0;
char outline[128];
int n_outline = 0;

long tcpqueue=0;
long exit_application = FALSE;
int flag_new_host = 0;

int dialog_show(char *title, char *text, char *rtn_s, int len);
int telnet_handler(int tcpqueue, char *data, char *user_data);

///// TELNET CODES /////
#define SE 240
#define NOP 241
#define DM 242
#define IAC 0xff
#define DONT 0xfe
#define DO 0xfd
#define WONT 0xfc
#define WILL 0xfb
#define SB 0xfa
#define GA 0xf9

char telnet_options[] = {
	IAC, DO, 3, //suppress go ahead
	IAC, WONT, 24, //terminal type
	IAC, WONT, 31, // naws (window size)
	IAC, WONT, 32, // terminal speed
	IAC, WONT, 33, // remote flow control
	IAC, WONT, 34, // line mode
	IAC, WONT, 36, // new-environment
};

void send_char(int c) {
	if (tcpqueue != 0) {
		char s[2];
		s[0] = c;
		s[1] = 0;
		tcp_write(tcpqueue, s, 1);
	}
}

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

char lastline[64];
void putchar(char c);

static int get_number_of_chars_char_wrap(int w, char *s)
{
	int i;
	int len = strlen(s);
	int pixels;

	for(i=0; i<len; i++)
	{
		pixels = DisplayGraphics_string_width_Ex(main_module.m_gfx, s, i+1);
		if (pixels == w) {
			return i+1;
		} else if (pixels > w) {
			return i;
		}
	}
	return i;
}

void printf(char *s) 
{
	strcpy(lastline, s);
	DisplayGraphics_set_color( main_module.m_gfx, CLR_WHITE );
	DisplayGraphics_fill_rect( main_module.m_gfx, 0, 88, 160, 9);
	DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
	DisplayGraphics_draw_text( main_module.m_gfx, lastline, 0, 88 );
	DisplayGraphics_show( main_module.m_gfx );
	println();
}

void putchar(char c) 
{
	int wraplen = get_number_of_chars_char_wrap(160, lastline);
	char s[2];
	s[0] = c;
	s[1] = 0;

	if (strlen(lastline) > wraplen) {
		println();
	}
	if (c >=32 || c <128) strcat(lastline, s);
	if (c == 0x0d) {
		println();
	} else {
		DisplayGraphics_set_color( main_module.m_gfx, CLR_WHITE );
		DisplayGraphics_fill_rect( main_module.m_gfx, 0, 88, 160, 9);
		DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
		DisplayGraphics_draw_text( main_module.m_gfx, lastline, 0, 88 );
		DisplayGraphics_show( main_module.m_gfx );
	}
}

void println()
{
	struct rect_t rect;

	memmove(display[0], display[1], sizeof(display)-32);
	strncpy(display[10], lastline, 31);
	lastline[0]=0;
	DisplayGraphics_scroll( main_module.m_gfx, 0, 0, 160, 97, 0, -8);
	DisplayGraphics_set_color( main_module.m_gfx, CLR_WHITE );
	DisplayGraphics_fill_rect( main_module.m_gfx, 0, 88, 160, 9);
	DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
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

int cybiko_handler(struct Message *msg)
{
	//printf("cybiko_handler");

	switch( msg->msgid )
	{
		int key;

		case MSG_SHUTUP: // Processes the system exit signal
		case MSG_QUIT:
			exit_application = TRUE;
			break;
		case MSG_GOTFOCUS: // Redraws the screen
			redraw();
			break;
		case MSG_KEYDOWN: // Processes keyboard messages
			key = Message_get_key_param( msg )->scancode;
			if( key == KEY_ESC )
			{
				struct Message *ptr_msg;
				tcp_close(tcpqueue);
				tcpqueue = 0;
				ptr_msg = Message_new(sizeof(struct Message));
				ptr_msg->msgid = MSG_QUIT;
				Message_post(ptr_msg, cWinApp_get_name(main_module.m_process), get_own_id());
			}
			break;
		case MSG_KEYUP: // Processes keyboard messages
			key = Message_get_key_param( msg )->scancode;
			if ( key == KEY_SELECT)
			{
				dialog_show("TELNET", "Enter a domain name", hostvar, sizeof(hostvar)-1);
				if (dialog_show("TELNET", "Enter port", portvar, sizeof(portvar)-1))
				{
					g_port = atoul(portvar);
					if (tcpqueue) tcp_close(tcpqueue);
					tcpqueue = tcp_connect(hostvar, g_port, 512, telnet_handler, 0);
				}
				redraw();
			}
			else if (key == KEY_HELP) {
				tcp_ack(tcpqueue);
			}
			else if (key == KEY_ENTER) {
				if (tcpqueue != 0) {
					outline[n_outline++] = '\n';
					outline[n_outline] = 0;
					tcp_write(tcpqueue, outline, n_outline);
					println();
					n_outline = 0;
				}
			}
			break;
		case MSG_USER: //process rf messages
		{
			//printf("MSG_USER");
		}

		case MSG_CHARTYPED:
		{
			key = Message_get_key_param(msg)->ch;
			//send_char(key);
			putchar(key);
			outline[n_outline++]=key;
			break;
		}
	}
	return 0;
}

int telnet_handler(int tcpqueue, char *data, char *user_data)
{
	unsigned char *s;
	static int inside=1;
	static int x=0;
	static long llen;
	static short len;
	static int quotemode=0;

	//printf("telnet_handler");

	switch(tcp_msgid(data)) {
		case TCPMSG_WRITE_RESPONSE: 
		{
			//printf("WRITE_RESPONSE");
			tcp_write_accept(data); 
			break;
		}
		case TCPMSG_CLOSE_RESPONSE: 
		{
			//printf("CLOSE_RESPONSE");
			tcp_close_accept(data); 
			tcpqueue = 0;
			printf("<CLOSED>");
			break;
		}
		case TCPMSG_FILTER_RESPONSE: 
		{
			//printf("FILTER_RESPONSE");
			//printf("Wrote message!");
			break;
		}
		case TCPMSG_CONNECT_RESPONSE:
		{
			//printf("CONNECT_RESPONSE");
			tcp_connect_accept(data);
			if (tcp_errno)
			{
				printf("ERROR DETECTED");
				tcp_close(tcp_tcpqueue(data));
				break;
			}
			tcp_write(tcpqueue, telnet_options, sizeof(telnet_options));
			//tcp_filter(tcp_tcpqueue(data), TCP_FILTER_HTML);
			break;
		}
		case TCPMSG_READ_RESPONSE:
		{
			int i;
			//printf("READ_RESPONSE");
			tcp_read_accept(data);
			s = tcp_getdata(data, &llen);
			//printf(s);
			len = (short) llen;
			for(i=0; i<len; i++) {
				if (s[i] == IAC) {
					if (s[i+1] == DO) {
						char will[4];
						//printf("GOT DO");
						will[0] = IAC;
						will[1] = WONT;
						will[2] = s[i+2];
						tcp_write(tcpqueue, will, 3);
						i+=2;
					} else if (s[i+1] == SB) {
						i+=3;
						//printf("GOT SB");
					}
					else if (s[i+1] == SE) {
						i+=1;
						//printf("GOT SE");
					}
					else if (s[i+1] == WILL) {
						char will[4];
						//printf("GOT WILL");
						will[0] = IAC;
						will[1] = WONT;
						will[2] = s[i+2];
						tcp_write(tcpqueue, will, 3);
						i+=2;
					}
					else {
						char s[32];
						i+=1;
						sprintf(s, "GOT OTHER %d", s[i]);
						//printf(s);
					}
				} else {
					putchar(s[i]);
				}
			}
			break;
		}
		default:
		{
		}
	}
	return 0;
}

long main(int argc, char* argv[], bool start)
{
    int i;
	long cyid;
int x = 1;
TRACE("%d", x++);
    init_module(&main_module);
TRACE("%d", x++);

	cyid = tcp_init(&main_module);
TRACE("%d", x++);

	redraw();
TRACE("%d", x++);
	printf("Press SELECT to select Host");
TRACE("%d", x++);

	strcpy(hostvar, "devcybiko.com");
TRACE("%d", x++);
	strcpy(portvar, "23");
TRACE("%d", x++);

	while(!exit_application)
	{
TRACE("%d", x++);
		tcp_get_message(0, cybiko_handler);
	}

EARLY_EXIT:
	return 0L;
}

