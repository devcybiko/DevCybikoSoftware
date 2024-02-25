/**
  * The MiaChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the AIM protocol.
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

void onConnected()
{
    int i;
    char msg[32];
    sprintf(msg, ".Connected as %s", contacts.sn);
    music_play("connected.mus");
    jed_console_add_text(console, msg);
    jed_repaint(current_form);
    jed_console_add_text(console, ".Logged in - sending contact list");
    jed_repaint(current_form);
    for(i=0; contacts.nick_array[i][0]; i++)
    {
        send_contact(contacts.nick_array[i]);
    }
}

int msg_cnt=0;

void onRecv_msg()
{
    char *txt;
    char *sn;

    msg_cnt++;
    if (msg_cnt==10)
    {
        pw_check(&main_module, appname, 0);
    }
    music_play("recv_msg.mus");
    sn=strtok(NULL, "|"); //uin
    txt=strtok(NULL, "|"); // msg

    chat_add_message(sn, txt);
}

void onUser_online()
{
    char *sn;

    music_play("user_online.mus");
    sn = strtok(NULL, "|"); //uin

    sprintf(msgbuf2, ".%s is online", sn);
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
    chat_add_message(sn, ".online");
}

void remove_buddy_from_list(char *sn)
{
    int i;
    for(i=0; 0!=stricmp(sn, chat_nick[i]); i++);
    if (i<MAX_CHAT_NICKS)
    {
        memcpy(&chat_nick[i][0], &chat_nick[i+1][0], MAX_NICK_LEN*(MAX_CHAT_NICKS-i-1));
        memcpy(&last_msg[i], &last_msg[i+1], 4*(MAX_CHAT_NICKS-i-1));
        memcpy(&awaiting_chat[i], &awaiting_chat[i+1], (MAX_CHAT_NICKS-i-1));
    }
}

void onBad_password()
{
    char *sn;

    music_play("user_offline.mus");
    sprintf(msgbuf2, ".bad screen name or password ");
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
}

void onUser_offline()
{
    char *sn;

    music_play("user_offline.mus");
    sn = strtok(NULL, "|"); //uin
    sprintf(msgbuf2, ".%s is offline", sn);
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
    remove_buddy_from_list(sn);
    refresh_buddy_list();
}
