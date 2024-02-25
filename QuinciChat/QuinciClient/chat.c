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
Jed *chat_form;
Jed_item *chat_list;
Jed_item *chat_exit;
Jed_item *chat_title;

void chat_create()
{
    Jed_item *rtn_ji;

    if (chat_form == 0)
    {
        jed_open(&chat_form, &main_module, NULL);
        jed_text_new(&chat_title, chat_form, 0, 0, 160, 12, "CURRENT CHAT LIST", cool_bold_font);
        jed_list_new(&chat_list, chat_form, 0, 12, 160, 68, 100, mini_normal_font);
        jed_button_new(&chat_exit, chat_form, 94, 80, 40, 20, "Exit", cool_bold_font);
    }
}

void chat_select()
{
    Jed_item *rtn_ji;
    int i;

    jed_list_clear(chat_list);

    for(i=0; chat_uin[i]; i++)
    {
        char item[40];
        sprintf(item, "%ld (%s)", chat_uin[i], chat_nick[i]);
        jed_list_add_item(chat_list, item);
    }
    rtn_ji = 0;
    while(rtn_ji != chat_exit)
    {
        current_form = chat_form;
        jed_main(chat_form, &rtn_ji, 1000);

        if (rtn_ji == 0) break;
        else if (rtn_ji == chat_list)
        {
            chat_make_current();
            break;
        }
    }
}

void chat_make_current()
{
    int i;
    char *szuin = jed_get_value(chat_list);
    current_uin = atoul(szuin);
    strcpy(sz_buddy_uin, szuin);
    sprintf(msgbuf2, "Quinci: %s", sz_buddy_uin);
    jed_set_value(title, msgbuf2);
    jed_console_clear(console);
    for(i=0; last_msg[i]; i++)
    {
        if (chat_uin[i]==current_uin)
            jed_console_add_text(console, last_msg[i]);
    }
}

void chat_add_message(long uin, char *msg)
{
    int i;
    for(i=0; last_msg[i]; i++)
    {
        if (chat_uin[i] == uin)
        {
            if (last_msg[i]) free(last_msg[i]);
            last_msg[i]=strdup(msg);
            break;
        }
    }
    if (last_msg[i] == 0)
    {
        char *nick = contacts_lookup_name(uin);
        chat_uin[i] = uin;
        if (nick==NULL)
        {
            nick="?";
        }
        strcpy(&chat_nick[i][0], nick);
        sprintf(msgbuf2, ">%s", msg);
        last_msg[i]=strdup(msgbuf2);
    }
    if (current_uin == 0)
    {
        char *nick = contacts_lookup_name(uin);
        current_uin = uin;
        sprintf(sz_buddy_uin, "%ld (%s)", uin, nick);
        sprintf(msgbuf2, "Quinci: %s", sz_buddy_uin);
        jed_set_value(title, msgbuf2);
    }

    if (uin == current_uin)
    {
        sprintf(msgbuf2, ">%s", msg);
        jed_console_add_text(console, msgbuf2);
        jed_repaint(current_form);
    }
}

void chat_del(long uin)
{
    // todo
}
