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
static Jed *fonts_form=0;
char *fontname[] = {"Default", "Times", "Arial", "Courier", 0};
char *colors[] = {"Default", "Black", "White", "Red", "Orange", "Yellow",
                "Green", "Blue", "Indigo", "Violet", 0};
char *fontsize[] = {"-2", "-1", "0", "1", "2", "3", "4", "5", 0};

int str_lookup(char **list, char *s)
{
    int i;

    for(i=0; list[i]; i++)
        if (SAME(list[i], s)) return i;
    return -1;
}

int fonts_edit()
{
    static Jed_item *tmp;
    static Jed_item *fonts_fontlist;
    static Jed_item *fonts_fontsize;
    static Jed_item *fonts_bgcolor;
    static Jed_item *fonts_fgcolor;
    static Jed_item *fonts_prefix;
    static Jed_item *fonts_suffix;
    static Jed_item *fonts_ok;
    static Jed_item *fonts_cancel;
    static Jed_item *rtn_ji;
    static Jed_item *fonts_title;
    char sztmp[20];
    int true=1;
    int i;

    if (fonts_form == 0)
    {
        jed_open(&fonts_form, &main_module, NULL);
        jed_text_new(&fonts_title, fonts_form, 0, 0, 160, 12, "EDIT FONTS", cool_bold_font);
        jed_text_new(&tmp, fonts_form, 15, 14, 0, 0, "Font:", mini_bold_font);
        jed_text_new(&tmp, fonts_form, 15, 28, 0, 0, "Prefix:", mini_bold_font);
        jed_text_new(&tmp, fonts_form, 15, 40, 0, 0, "Suffix", mini_bold_font);
        jed_text_new(&tmp, fonts_form, 15, 52, 0, 0, "FGColor", mini_bold_font);
        jed_text_new(&tmp, fonts_form, 15, 64, 0, 0, "BGColor", mini_bold_font);
        jed_list_new(&fonts_fontlist, fonts_form, 60, 14, 50, 14, 10, mini_normal_font);
        jed_list_new(&fonts_fontsize, fonts_form, 110, 14, 50, 14, 10, mini_normal_font);
        jed_string_new(&fonts_prefix, fonts_form, 60, 28, 50, 14, 63, contacts.prefix, mini_normal_font);
        jed_string_new(&fonts_suffix, fonts_form, 60, 42, 50, 14, 10, contacts.suffix, mini_normal_font);
        jed_list_new(&fonts_fgcolor, fonts_form, 60, 54, 50, 14, 10, mini_normal_font);
        jed_list_new(&fonts_bgcolor, fonts_form, 60, 68, 50, 14, 10, mini_normal_font);
        jed_button_new(&fonts_ok, fonts_form,     26, 85, 40, 15, "OK", cool_bold_font);
        jed_button_new(&fonts_cancel, fonts_form, 92, 85, 40, 15, "Cancel", cool_bold_font);
        for(i=0; fontname[i]; i++)
            jed_list_add_item(fonts_fontlist, fontname[i]);
        for(i=0; fontsize[i]; i++)
            jed_list_add_item(fonts_fontsize, fontsize[i]);
        for(i=0; colors[i]; i++)
        {
            jed_list_add_item(fonts_fgcolor, colors[i]);
            jed_list_add_item(fonts_bgcolor, colors[i]);
        }
    }

    sprintf(sztmp, "%d", contacts.fontsize);
    jed_set_value(fonts_fontsize, sztmp);
    jed_set_value(fonts_fontlist, fontname[contacts.fontname]);
    jed_set_value(fonts_prefix, contacts.prefix);
    jed_set_value(fonts_suffix, contacts.suffix);
    jed_set_value(fonts_fgcolor, colors[contacts.fgcolor]);
    jed_set_value(fonts_bgcolor, colors[contacts.bgcolor]);

    rtn_ji = 0;
    while( true )
    {
        current_form = fonts_form;
        jed_main(fonts_form, &rtn_ji, 1000);
        if (rtn_ji == fonts_ok) break;
        else if (rtn_ji == fonts_cancel) break;
        else if (rtn_ji == 0) break;
    }

    if (rtn_ji == fonts_ok)
    {
        strcpy(contacts.prefix, jed_get_value(fonts_prefix));
        strcpy(contacts.suffix, jed_get_value(fonts_suffix));
        contacts.fontname = str_lookup(fontname, jed_get_value(fonts_fontlist));
        contacts.fontsize = (int) atoul(jed_get_value(fonts_fontsize));
        contacts.fgcolor = str_lookup(colors, jed_get_value(fonts_fgcolor));
        contacts.bgcolor = str_lookup(colors, jed_get_value(fonts_bgcolor));
        contacts_write();
        send_font();
        return 0;
    }
    return 0;
}

