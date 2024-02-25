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

void onConnected()
{
    music_play("connected.mus");
    jed_console_add_text(console, ".Connected");
    jed_repaint(current_form);
    send_login();
}

void onLogged()
{
    int i;

    music_play("logged.mus");
    jed_console_add_text(console, ".Logged in - sending contact list");
    jed_repaint(current_form);
    for(i=0; contacts.buddy_array[i]; i++)
    {
        send_contact(contacts.buddy_array[i]);
    }
    send_list();
}

int msg_cnt=0;

void onRecv_msg()
{
    char *txt;
    long uin;

    msg_cnt++;
    if (msg_cnt==10)
    {
        pw_check(&main_module, appname, 0);
    }
    music_play("recv_msg.mus");
    txt=strtok(NULL, "|"); //uin
    uin=atoul(txt);
    txt=strtok(NULL, "|"); // hour
    txt=strtok(NULL, "|"); // min
    txt=strtok(NULL, "|"); // day
    txt=strtok(NULL, "|"); // mon
    txt=strtok(NULL, "|"); // year
    txt=strtok(NULL, "|"); // msg

    chat_add_message(uin, txt);
}

void onUser_online()
{
    char *txt;
    long uin;
    char *nick;

    music_play("user_online.mus");
    txt = strtok(NULL, "|"); //uin
    uin=atoul(txt);
    txt = strtok(NULL, "|");// status
    txt = strtok(NULL, "|");//ip
    txt = strtok(NULL, "|");//port
    txt = strtok(NULL, "|");//real_ip
    txt = strtok(NULL, "|");//tcp_flag

    nick = contacts_lookup_name(uin);
    if (nick == NULL)
    {
        send_info(uin);
        nick="?";
    }

    sprintf(msgbuf2, ".%ld (%s) is online", uin, nick);
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
    chat_add_message(uin, ".online");
}

void onUser_offline()
{
    char *txt;
    long uin;

    music_play("user_offline.mus");
    txt = strtok(NULL, "|"); //uin
    uin=atoul(txt);
    sprintf(msgbuf2, ".%ld is offline", uin);
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
    //remove from chat list
}

void onWrong_password()
{
    music_play("badness.mus");
    sprintf(msgbuf2, ".cannot login, invalid password");
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
}    

void onInvalid_uin()
{
    music_play("badness.mus");
    sprintf(msgbuf2, ".cannot login, invalid UIN");
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
}    

void onDisconnected()
{
    music_play("badness.mus");
    sprintf(msgbuf2, ".disconnected");
    jed_console_add_text(console, msgbuf2);
    jed_repaint(current_form);
    // delete entire chat list
}    

void onInfo_reply()
{
    char *txt;
    long uin;
    char *nick;

    txt = strtok(NULL, "|"); //uin
    uin=atoul(txt);
    nick = strtok(NULL, "|");// nick
    txt = strtok(NULL, "|");// first
    txt = strtok(NULL, "|");// last
    txt = strtok(NULL, "|");// email
    txt = strtok(NULL, "|");// auth

}

