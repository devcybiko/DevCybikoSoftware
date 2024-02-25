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
#ifndef JED_JED_H
#define JED_JED_H

#include "CyWin.h"

#define JED_GENERIC 0
#define JED_TEXT 1
#define JED_BUTTON 2
#define JED_STRING 3
#define JED_CONSOLE 4
#define JED_LIST 5

typedef long Jed_rc;
#define JED_SUCCESS 0

typedef struct jed {
    struct module_t *mm;
    int bgnd, fgnd, other1, other2; //colors
    struct Font *font;
    void *child;
} Jed;

#define nlines buflen
#define topline leftchar
#define maxlines rightchar
#define selected_item cursor

typedef struct jed_item {
    int type;
    short dummy1;
    Jed *jed;
    struct Font *font;
    short char_w, char_h;
    struct jed_item *next;
    int x, y, w, h; //pixels
    char *value;  // console-lines
    int buflen;   // console-nlines # lines in window
    int cursor;
    int leftchar; // console-topline
    int rightchar;// console-maxlines # lines in buffer
    int nitems; //number of items in the list
    char selected;
    char selectable;
    char return_on_enter;
    char dummy;
    int dx, dy;
    int start_x, start_y;
    int end_x, end_y;
    int mid_x, mid_y;
} Jed_item;

Jed_rc jed_process_message(Jed *jed, struct Message *message);

Jed_rc jed_open(Jed **jed, struct module_t *mm, struct Font *font);
Jed_rc jed_close(Jed *jed);
Jed_rc jed_repaint(Jed *jed);
Jed_rc jed_repaint_item(Jed_item *jed, bool repaint);
Jed_rc jed_motion(
    Jed_item *ji,
    int rate,
    int start_x,
    int start_y,
    int end_x,
    int end_y);
Jed_rc jed_main(Jed *jed, Jed_item **rtn_ji, long timeout);
void jed_error_noise(Jed *jed);
char *jed_get_value(Jed_item *ji);
Jed_rc jed_set_value(Jed_item *ji, char *s);
Jed_rc jed_repaint(Jed *jed);
Jed_rc jed_destroy_item(Jed_item *ji);

Jed_rc jed_button_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, char *value, struct Font *font);
Jed_rc jed_button_destroy(Jed_item *ji);
Jed_rc jed_button_repaint(Jed_item *ji);
char *jed_button_get_value(Jed_item *ji);
Jed_rc jed_button_set_value(Jed_item *ji, char *s);

Jed_rc jed_string_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, int buflen, char *value, struct Font *font);
Jed_rc jed_string_destroy(Jed_item *ji);
Jed_rc jed_string_repaint(Jed_item *ji);
Jed_rc jed_string_set_value(Jed_item *ji, char *value);
char *jed_string_get_value(Jed_item *ji);

Jed_rc jed_text_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, char *value, struct Font *font);
Jed_rc jed_text_destroy(Jed_item *ji);
Jed_rc jed_text_repaint(Jed_item *ji);
char *jed_text_get_value(Jed_item *ji);
Jed_rc jed_text_set_value(Jed_item *ji, char *s);

Jed_rc jed_console_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, int lines, struct Font *font);
Jed_rc jed_console_destroy(Jed_item *ji);
Jed_rc jed_console_repaint(Jed_item *ji);
Jed_rc jed_console_add_text(Jed_item *ji, char *s);
Jed_rc jed_console_clear(Jed_item *ji);

Jed_rc jed_list_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, int lines, struct Font *font);
Jed_rc jed_list_destroy(Jed_item *ji);
Jed_rc jed_list_repaint(Jed_item *ji);
Jed_rc jed_list_add_item(Jed_item *ji, char *s);
char *jed_list_get_value(Jed_item *ji);
Jed_rc jed_list_clear(Jed_item *ji);
Jed_rc jed_list_set_value(Jed_item *ji, char *s);

#endif
