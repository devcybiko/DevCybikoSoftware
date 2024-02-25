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
void send_contact(char *sn)
{
    sprintf(msgbuf2, "contact_add|%s", sn);
    msg_send(msgbuf2);
}

void send_message(char *s)
{
    if (*s == 0) return;
    if (current_buddy[0]==0)
    {
        jed_console_add_text(console, ".select a buddy");
        jed_repaint(current_form);
        return;
    }
        
    sprintf(msgbuf2, "send_msg|%s|%s%s%s",
        current_buddy,
        contacts.prefix,
        s,
        contacts.suffix);
    msg_send(msgbuf2);

    sprintf(msgbuf, "%s%s%s",
        contacts.prefix,
        s,
        contacts.suffix);
    append_user(current_buddy, msgbuf);
    jed_set_value(string, "");
    jed_repaint(current_form);
}

void send_connect()
{
    sprintf(msgbuf, "connect|%s|%s|%s|%d",
        contacts.sn,
        contacts.passwd,
        contacts.server,
        contacts.port);
    msg_send(msgbuf);
}

void send_logout()
{
    sprintf(msgbuf, "logout");
    msg_send(msgbuf);
}

void send_font()
{
    sprintf(msgbuf, "font|%d|%d|%d|%d",
        contacts.fontname,
        contacts.fontsize,
        contacts.bgcolor,
        contacts.fgcolor);
    msg_send(msgbuf);
}
