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
void send_contact(long buddy_uin)
{
    sprintf(msgbuf2, "contact_add|%ld", buddy_uin);
    msg_send(msgbuf2);
}

void send_list()
{
    msg_send("send_list");
}

void send_message(char *s)
{
    if (*s == 0) return;
    if (*sz_buddy_uin==0)
    {
        jed_console_add_text(console, ".select a buddy");
        jed_repaint(current_form);
        return;
    }
        
    sprintf(msgbuf2, "send_msg|%s|%s", sz_buddy_uin, s);
    msg_send(msgbuf2);

    sprintf(msgbuf2, "<%s", s);
    jed_console_add_text(console, msgbuf2);
    jed_set_value(string, "");
    jed_repaint(current_form);
}

void send_connect()
{
    sprintf(msgbuf, "connect|%ld|%s|%s|%s|%d",
        contacts.uin,
        contacts.passwd,
        contacts.nick,
        contacts.server,
        contacts.port);
    msg_send(msgbuf);
}

void send_login()
{
    sprintf(msgbuf, "login");
    msg_send(msgbuf);
}

void send_logout()
{
    sprintf(msgbuf, "logout");
    msg_send(msgbuf);
}

void send_disconnect()
{
    sprintf(msgbuf, "disconnect");
    msg_send(msgbuf);
}

void send_info(long uin)
{
    sprintf(msgbuf, "send_info|%ld", uin);
    msg_send(msgbuf);
}
