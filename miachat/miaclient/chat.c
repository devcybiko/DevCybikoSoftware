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

    for(i=0; chat_nick[i][0]; i++)
    {
        jed_list_add_item(chat_list, chat_nick[i]);
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
    char *sn = jed_get_value(chat_list);
    strcpy(current_buddy, sn);
    sprintf(msgbuf2, "MIA: %s", current_buddy);
    jed_set_value(title, msgbuf2);
    jed_console_clear(console);
    for(i=0; last_msg[i]; i++)
    {
        if (0==stricmp(chat_nick[i],current_buddy))
        {
            update_window(i);
            awaiting_chat[i]=0;
            refresh_buddy_list();
            jed_repaint(current_form);
            break;
        }
    }
}

int msglen(char *s)
{
    int i=0;

    while(!(s[i]==0 && s[i+1]==0)) i++;
    return i;
}

void append_user(char *sn, char *msg)
{
    int i;
    for(i=0; last_msg[i]; i++)
    {
        //
        // found a user
        //
        if (0==stricmp(chat_nick[i],sn))
        {
            break;
        }
    }
    if (last_msg[i])
    {
        sprintf(msgbuf2, "<%s", msg);
        append_chat(i, msgbuf2);
        update_window(i);
        jed_repaint(current_form);
    }
}

void append_chat(int i, char *msg)
{
    int len=msglen(last_msg[i]);
    int mlen = strlen(msg);
    while (mlen+len > MAX_CHAT_BUFFER)
    {
        int slen = strlen(last_msg[i]);
        memmove(last_msg[i],
                &last_msg[i][slen+1],
                len-slen+1);
        len = len - slen+1;
    }
    if (len != 0) len++;
    strcpy(&last_msg[i][len],msg);
    last_msg[i][len+mlen+2]=0;
}

void chat_add_message(char *sn, char *msg)
{
    int i;
    int online = (0==strcmp(msg, ".online"));
    int this_buddy = 0==stricmp(current_buddy, sn);

    for(i=0; last_msg[i]; i++)
    {
        //
        // found a user
        //
        if (0==stricmp(chat_nick[i],sn))
        {
            break;
        }
    }
    //
    // unknown user sent message
    //
    if (last_msg[i] == 0)
    {
        strcpy(&chat_nick[i][0],sn);
        last_msg[i] = calloc(1, MAX_CHAT_BUFFER);
    }

    sprintf(msgbuf2, ">%s", msg);
    append_chat(i, msgbuf2);
    if (!online && !this_buddy) awaiting_chat[i]=1;
    refresh_buddy_list();

    //
    // we werent talking to anyone so pop this guy onscreen
    //
    if (current_buddy[0] == 0)
    {
        sprintf(current_buddy, "%s", sn);
        sprintf(msgbuf2, "MIA: %s", current_buddy);
        jed_set_value(title, msgbuf2);
    }

    //
    // the message comes from the current user
    //
    if (0==stricmp(current_buddy, sn))
    {
        update_window(i);
        jed_repaint(current_form);
    }
}
