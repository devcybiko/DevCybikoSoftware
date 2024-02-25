/**
  * The QuinciChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the ICQ protocol.
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

struct module_t main_module;
char readbuf[256];
char msgbuf[256];
char tmp[50];
int nchars=0;
int icqcnt=0;
int cycnt=0;
com_t tty;
long client_cyid=0;

#include "load.c"

#define DBG do_nothing

void do_nothing(char *s){}

void redraw()
{
    DBG(">redraw");
    DisplayGraphics_fill_screen( main_module.m_gfx, CLR_WHITE );
    DisplayGraphics_set_color( main_module.m_gfx, CLR_BLACK );
    DisplayGraphics_set_font( main_module.m_gfx, cool_normal_font );
    sprintf(tmp, "ICQ   =%d", icqcnt);
    DisplayGraphics_draw_text( main_module.m_gfx, tmp, 50, 35 );
    sprintf(tmp, "Cybiko=%d", cycnt);
    DisplayGraphics_draw_text( main_module.m_gfx, tmp, 50, 50 );
    DisplayGraphics_show( main_module.m_gfx );
    DBG("<redraw");
}

void serial_write(char *buf)
{
    int i;

    DBG(">serial_write");
    i=0;
    com_write(tty, 0, 0); // clear the buffer
    while(buf[i])
    {
        com_write(tty, buf[i++], 0);
    }
    com_write(tty, 0, 0); // end the string
    DBG("<serial_write");
}

void serial_read()
{
    int x;

    DBG(">serial_read");

    x = com_read(tty, 1);
    if (x==-1) return;
    if (x==0)
    {
        readbuf[nchars]=(char)x;
        nchars=0;
        send_remote_msg(client_cyid, "quinciclient", MSG_USER, 0, 0, readbuf, strlen(readbuf)+1);
        icqcnt=icqcnt+1;
        redraw();
    }
    else
    {
        if (nchars < sizeof(readbuf)-1)
        {
            readbuf[nchars]=(char)x;
            nchars=nchars+1;
        }
    }
    DBG("<serial_read");
}

void message_loop( struct module_t* ptr_main_module )
{
  bool exit_application = FALSE;

   DBG(">message_loop");
  while( !exit_application )
  {
    struct Message* ptr_message = 
      cWinApp_get_message( ptr_main_module->m_process, 1, 1, MSG_USER );

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
            Buffer_load( Message_get_buffer( ptr_message ), msgbuf,0,sizeof(msgbuf)-1);
            msgbuf[sizeof(msgbuf)-1]=0;
            serial_write(msgbuf);
            client_cyid = ptr_message->cyid_from;
            cycnt=cycnt+1;
            redraw();
         }
         break;
      }
      default: // Processes all unprocessed messages
        cWinApp_defproc( ptr_main_module->m_process, ptr_message );
    } 
    Message_delete( ptr_message );
  }
   DBG("<message_loop");
}

long main( int argc, char* argv[], bool start )
{

   DBG(">main");
    init_module( &main_module );

    load("ComPort.dl");

    tty = com_open(COMM_DEV_DEFAULT, 1000);
    message_loop( &main_module );
    com_close(tty);

   DBG("<main");
    return 0L;
}

