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
void profile_edit()
{
    static Jed *profile_form=0;
    static Jed_item *tmp;
    static Jed_item *profile_uin;
    static Jed_item *profile_nick;
    static Jed_item *profile_passwd;
    static Jed_item *profile_server;
    static Jed_item *profile_port;
    static Jed_item *profile_ok;
    static Jed_item *profile_cancel;
    static Jed_item *rtn_ji;
    static Jed_item *profile_title;
    static Jed_item *profile_buddies;
    char szuin[20];
    char szport[20];
    int true=1;

    if (contacts.nick[0] == 0)
    {
        strcpy(contacts.nick, finder.mf.f_nick);
    }
    if (contacts.server[0] == 0)
    {
        strcpy(contacts.server, "icq.mirabilis.com");
        contacts.port = 4000;
    }
    sprintf(szuin, "%ld", contacts.uin);
    sprintf(szport, "%d", contacts.port);

    if (profile_form == 0)
    {
        jed_open(&profile_form, &main_module, NULL);
        jed_text_new(&profile_title, profile_form, 0, 0, 160, 12, "EDIT PROFILE", cool_bold_font);
        jed_text_new(&tmp, profile_form, 0, 14, 0, 0, "UIN:", cool_bold_font);
        jed_text_new(&tmp, profile_form, 0, 28, 0, 0, "Passwd:", cool_bold_font);
        jed_text_new(&tmp, profile_form, 0, 42, 0, 0, "NickName:", cool_bold_font);
        jed_text_new(&tmp, profile_form, 0, 56, 0, 0, "Server", cool_bold_font);
        jed_text_new(&tmp, profile_form, 0, 70, 0, 0, "Port", cool_bold_font);
        jed_string_new(&profile_uin, profile_form,    60, 14, 100, 14, 10, szuin, cool_normal_font);
        jed_string_new(&profile_passwd, profile_form, 60, 28, 100, 14, 19, contacts.passwd, cool_normal_font);
        jed_string_new(&profile_nick, profile_form,   60, 42, 100, 14, 19, contacts.nick, cool_normal_font);
        jed_string_new(&profile_server, profile_form, 60, 56, 100, 14, 63, contacts.server, cool_normal_font);
        jed_string_new(&profile_port, profile_form,   60, 70, 100, 14, 10, szport, cool_normal_font);
        jed_button_new(&profile_ok, profile_form,     10, 85, 40, 15, "OK", cool_bold_font);
        jed_button_new(&profile_buddies, profile_form, 60, 85, 40, 15, "Buds", cool_bold_font);
        jed_button_new(&profile_cancel, profile_form, 110, 85, 40, 15, "Cancel", cool_bold_font);
    }

    rtn_ji = 0;
    while( true )
    {
        current_form = profile_form;
        jed_main(profile_form, &rtn_ji, 1000);
        if (rtn_ji == profile_buddies)
        {
            if (contacts_edit()) break;
        }
        else if (rtn_ji == profile_ok) break;
        else if (rtn_ji == profile_cancel) break;
        else if (rtn_ji == 0) break;
    }

    if (rtn_ji == profile_ok)
    {
        strcpy(contacts.nick, jed_get_value(profile_nick));
        strcpy(contacts.server, jed_get_value(profile_server));
        strcpy(contacts.passwd, jed_get_value(profile_passwd));
        contacts.uin = atoul(jed_get_value(profile_uin));
        contacts.port= (int) atoul(jed_get_value(profile_port));

        contacts_write();
    }
}

