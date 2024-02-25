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
#include "tcplib.h"
#include "tcperror.h"

struct module_t main_module;
char display[10][32];
char lineno=0;
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
    for(i=0; i<10; i++)
	{
		DisplayGraphics_draw_text( main_module.m_gfx, display[i], 0, i*10 );
	}
    DisplayGraphics_show( main_module.m_gfx );
}

void printf(char *s)
{
	sprintf(display[lineno%10], "%d %s", lineno, s);
	redraw();
	lineno++;
}

int dialog_show(char *title, char *text, char *rtn_s, int len)
{
    struct cDialog *dialog;
    int rc;

    dialog = (struct cDialog *) malloc(sizeof(struct cDialog));
	cDialog_ctor(dialog, title, text, mbOk | mbCancel | mbEdit, len, main_module.m_process);
    //cDialog_SetEditText( dialog, rtn_s );
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
				tcp_close(1);
				ptr_msg = Message_new(sizeof(struct Message));
				ptr_msg->msgid = MSG_QUIT;
				Message_post(ptr_msg, cWinApp_get_name(main_module.m_process), get_own_id());
			}
			if ( key == KEY_SPACE)
			{
				flag_new_host = 1;
			}
			break;
		case MSG_USER: //process rf messages
		{
			//printf("MSG_USER");
		}
	}
	return 0;
}

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
			//printf("WRITE_RESPONSE");
			tcp_write_accept(data); 
			break;
		}
		case TCPMSG_CLOSE_RESPONSE: 
		{
			//printf("CLOSE_RESPONSE");
			tcp_close_accept(data); 
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
			tcp_write(tcp_tcpqueue(data), "GET /index.html HTTP/1.0\n\n", 26);
			//printf("Wrote message!");
			break;
		}
		case TCPMSG_READ_RESPONSE:
		{
			//printf("READ_RESPONSE");
			tcp_read_accept(data);
			s = tcp_getdata(data, &llen);
			len = (short) llen;
			while(len>0)
			{
				if (*s == '"') quotemode = !quotemode;
				if (!quotemode && (*s == '<')) 
				{
					inside=1;
					if ((s[1]&0x5f)=='B' && (s[2]&0x5f)=='R')
					{
						tmp[x]=0;
						printf(tmp);
						x=0;
					}
				}
				if (!inside)
				{
					if (*s >= 32) tmp[x++]=*s;
					if (x==28)
					{
						tmp[x]=0;
						printf(tmp);
						x=0;
					}
				}
				if (!quotemode && (*s == '>')) inside=0;
				s++;
				len--;
			}
			if (x)
			{
				tmp[x]=0;
				printf(tmp);
				x=0;
			}
			break;
		}
		default:
		{
			char t[32];
			sprintf(t, "%d", tcp_msgid(data));
			printf(t);
		}
	}
	return 0;
}

long main(int argc, char* argv[], bool start)
{
    int i;
	long cyid;

    init_module(&main_module);

	cyid = tcp_init(&main_module);

	sprintf(tmp, "cyid=%ld", cyid);
	printf(tmp);

	printf("Press SPACE to select Host");

	strcpy(hostvar, "devcybiko.com");

	while(!exit_application)
	{
		tcp_get_message(0, cybiko_handler);
		if (flag_new_host)
		{
			flag_new_host = 0;
			if (tcpqueue) tcp_close(tcpqueue);
			dialog_show("Select Host", "Enter Hostname", hostvar, 32);
			tcpqueue = tcp_connect(hostvar, 80, html_handler, NULL);
			if (tcp_errno)
			{
				printf("ERROR CONNECTING");
			}
			sprintf(tmp, "tcpqueue=%d", tcpqueue);
			printf(tmp);
			sprintf(tmp, "errno=%d", tcp_errno);
			printf(tmp);
		}
	}

EARLY_EXIT:
	return 0L;
}

