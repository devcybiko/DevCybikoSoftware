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
Jed *contact_form=0;
Jed_item *contact_list;

int contacts_edit()
{

    static Jed_item *contact_add;
    static Jed_item *contact_del;
    static Jed_item *contact_call;
    static Jed_item *contact_exit;
    static Jed_item *contact_title;
    Jed_item *rtn_ji;
    int i;
    int rc=0;

    if (contact_form == 0)
    {
        jed_open(&contact_form, &main_module, NULL);
        jed_text_new(&contact_title, contact_form, 0, 0, 160, 12, "BUDDY LIST", cool_bold_font);
        jed_list_new(&contact_list, contact_form, 0, 12, 160, 68, 100, mini_normal_font);
        jed_button_new(&contact_call, contact_form, 0, 80, 40, 20, "Call", cool_bold_font);
        jed_button_new(&contact_add, contact_form, 40, 80, 40, 20, "Add", cool_bold_font);
        jed_button_new(&contact_del, contact_form, 80, 80, 40, 20, "Del", cool_bold_font);
        jed_button_new(&contact_exit, contact_form, 120, 80, 40, 20, "Exit", cool_bold_font);
    }

    jed_list_clear(contact_list);

    for(i=0; contacts.buddy_array[i]; i++)
    {
        char item[40];
        sprintf(item, "%ld (%s)", contacts.buddy_array[i], contacts.nick_array[i]);
        jed_list_add_item(contact_list, item);
    }
    rtn_ji = 0;
    while(rtn_ji != contact_exit)
    {
        current_form=contact_form;
        jed_main(contact_form, &rtn_ji, 1000);

        if (rtn_ji == 0) break;
        else if ((rtn_ji == contact_call) || (rtn_ji == contact_list))
        {
            contacts_call();
            rc = 1;
            break;
        }
        else if (rtn_ji == contact_add) contacts_add();
        else if (rtn_ji == contact_del) contacts_del();
    }
    return rc;
}

void contacts_call()
{
    int i;
    char *szuin = jed_get_value(contact_list);
    current_uin = atoul(szuin);
    strcpy(sz_buddy_uin, szuin);
    sprintf(msgbuf2, "Qunici: %s (%ld)", sz_buddy_uin, contacts.uin);
    jed_set_value(title, msgbuf2);
    jed_console_clear(console);
    for(i=0; last_msg[i]; i++)
    {
        if (chat_uin[i]==current_uin)
            jed_console_add_text(console, last_msg[i]);
    }
}

int dialog_show(char *title, char *text, char *rtn_s, int len)
{
    struct cDialog *dialog;
    int rc;

    dialog = (struct cDialog *) malloc(sizeof(struct cDialog));
    cDialog_ctor(dialog, title, text, mbOk | mbCancel | mbEdit, len, main_module.m_process);
    rc = cDialog_ShowModal(dialog);
    if (rc == mrOk)
    {
        cDialog_GetEditText(dialog, rtn_s);
        rtn_s[len]=0;
        rc = 1;
    }
    else
    {
        rc = 0;
    }

    cDialog_dtor(dialog, FREE_MEMORY);
    return rc;
}

void contacts_add()
{
    int rc;
    int i;
    int len;
    char szuin[21];
    char nick[21];
    char tmp[41];
    long uin;

    if (dialog_show("Quinci Add", "Enter the UIN of the new user", szuin, 20))
    {
        uin = atoul(szuin);
        if (uin == 0) goto EARLY_EXIT;
        if (dialog_show("Quinci Add", "Enter the nickname of the new user", nick, 20))
        {
            for(i=0; contacts.buddy_array[i]; i++);
            contacts.buddy_array[i] = uin;
            strcpy(contacts.nick_array[i], nick);
            sprintf(tmp, "%s (%s)", szuin, nick);
            jed_list_add_item(contact_list, tmp);
            contacts_write();
            send_contact(uin);
            send_list();
        }
    }
EARLY_EXIT:
    jed_repaint(current_form);
}

void contacts_del()
{
    int i;
    char *szuin = jed_get_value(contact_list);
    long uin = atoul(szuin);

    for(i=0; contacts.buddy_array[i]; i++)
    {
        if (contacts.buddy_array[i] == uin)
        {
            memcpy(&contacts.buddy_array[i], &contacts.buddy_array[i+1], 4*(100-i-1));
            memcpy(&contacts.nick_array[i], &contacts.nick_array[i+1], 20*(100-i-1));
            contacts_write();
            break;
        }
    }
    jed_list_clear(contact_list);

    for(i=0; contacts.buddy_array[i]; i++)
    {
        char item[40];
        sprintf(item, "%ld (%s)", contacts.buddy_array[i], contacts.nick_array[i]);
        jed_list_add_item(contact_list, item);
    }
}

void contacts_read()
{
    struct FileInput fi;
    memset(&contacts, 0, sizeof(contacts));
    FileInput_ctor(&fi);
    if (!FileInput_open(&fi, "quinciclient.dat"))
    {
        profile_edit();
    }
    else
    {
        FileInput_read(&fi, &contacts, sizeof(contacts));
    }
    FileInput_dtor(&fi, LEAVE_MEMORY);
}

char *contacts_lookup_name(long uin)
{
    char *rtn_s = "";
    int i;

    for(i=0; contacts.buddy_array[i]; i++)
    {
        if (contacts.buddy_array[i] == uin)
            return contacts.nick_array[i];
    }
    for(i=0; chat_uin[i]; i++)
    {
        if (chat_uin[i] == uin)
            return &chat_nick[i][0];
    }
    return NULL;
}

void contacts_write()
{
    struct FileOutput fo;

    FileOutput_ctor(&fo);
    if (!FileOutput_open(&fo, "quinciclient.dat", TRUE))
    {
        return;
    }
    else
    {
        FileOutput_write(&fo, &contacts, sizeof(contacts));
    }
    FileOutput_dtor(&fo, LEAVE_MEMORY);
}
