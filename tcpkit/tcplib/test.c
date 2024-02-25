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

struct module_t main_module;
char display[12][32];
char tmpline[64];
int lineno=0;

long exit_application = FALSE;

void redraw()
{
	int i;

    DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
    DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
    for(i=0; i<12; i++)
	{
		DisplayGraphics_draw_text( main_module.m_gfx, display[i], 0, i*8 );
	}
    DisplayGraphics_show( main_module.m_gfx );
}

void printf(char *s)
{
	lineno = lineno % 12;
	sprintf(tmpline, "%d %s", lineno, s);
	strncpy(display[lineno%12], tmpline, 31);
	lineno++;
	redraw();
}

long main(int argc, char* argv[], bool start)
{
	struct Message *msg;

    init_module(&main_module);
	printf("Begin Testing");

    DisplayGraphics_set_font( main_module.m_gfx, mini_normal_font );

	while(!exit_application)
	{
		msg = cWinApp_get_message(main_module.m_process, 0, 1, MSG_USER );
		if (msg == 0) continue;
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
					ptr_msg = Message_new(sizeof(struct Message));
					ptr_msg->msgid = MSG_QUIT;
					Message_post(ptr_msg, cWinApp_get_name(main_module.m_process), get_own_id());
				}
				break;
			default:
				cWinApp_defproc(main_module.m_process, msg);
				break;
		}
	    DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
	    DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
		sprintf(tmpline, "%d", lineno++);
		DisplayGraphics_draw_text( main_module.m_gfx, tmpline, 0, 0 );
	    DisplayGraphics_show( main_module.m_gfx );
		Message_delete(msg);
	}

EARLY_EXIT:
	return 0L;
}

