/**
  * The JED project is a library that offers a simple
  * GUI for the Cybiko Handheld Computer for Teens
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
  */#include "alcor.h"
#include "jed.h"

#ifdef DEBUG
#define DBG TRACE
#else
#define DBG debug
debug(char *fmt, ...) {}
#endif

Jed_rc jed_string_handle_char(Jed_item *ji, int c);
Jed_rc jed_console_handle_char(Jed_item *ji, int c);
Jed_rc jed_list_handle_char(Jed_item *ji, int c);
int jed_string_len(Jed_item *ji, char *s, int w);

#ifdef DL
main()
{}

Jed_rc jed_process_message(Jed *jed, struct Message *message)
{}
#endif

Jed_rc jed_open(Jed **jed, struct module_t *mm, struct Font *font)
{
    DBG(">jed_open");
    jed[0] = CALLOC(1, Jed);
    jed[0]->mm = mm;
    jed[0]->bgnd = CLR_LTGRAY;
    jed[0]->fgnd = CLR_BLACK;
    jed[0]->other1= CLR_DKGRAY;
    jed[0]->other2= CLR_WHITE;
    if (font == NULL)
    {
        jed[0]->font = mini_normal_font;
    }
    else
    {
        jed[0]->font = font;
    }
//    TGraph_fill_screen(mm->m_gfx, jed[0]->bgnd);
//    DisplayGraphics_show(mm->m_gfx);
    DBG("<jed open");
    return JED_SUCCESS;
}

Jed_rc jed_repaint_item(Jed_item *ji, bool repaint)
{
    DBG(">jed_repaint_item %d", ji->type);
    switch(ji->type)
    {
        case JED_TEXT:
            jed_text_repaint(ji);
            break;
        case JED_BUTTON:
            jed_button_repaint(ji);
            break;
        case JED_STRING:
            DBG("...calling jed_string_repaint");
            jed_string_repaint(ji);
            DBG("...returning from jed_string_repaint");
            break;
        case JED_CONSOLE:
            jed_console_repaint(ji);
            break;
        case JED_LIST:
            jed_list_repaint(ji);
            break;
       default :
            TRACE(">>> Unknown type in jed_repaint_item");
            break;
    }
    if (repaint)
        DisplayGraphics_show(ji->jed->mm->m_gfx);
    DBG("<jed_repaint_item");
    return JED_SUCCESS;
}

Jed_rc jed_repaint(Jed *jed)
{
    Jed_item *ji;

    DBG(">jed_repaint");
    TGraph_fill_screen(jed->mm->m_gfx, jed->bgnd);
    for(ji=jed->child; ji; ji = ji->next)
    {
        DBG("calling jed_repaint_item\n");
        jed_repaint_item(ji, FALSE);
    }
    DBG("calling DisplayGrahics_show\n");
    DisplayGraphics_show(jed->mm->m_gfx);
    DBG("<jed_repaint");
    return JED_SUCCESS;
}

void jed_detach_item(Jed_item *ji)
{
    Jed_item *prev;

    // special case - remove the first child
    if (ji == ji->jed->child)
    {
        ji->jed->child = ji->next;
        return;
    }
    // find previous node
    for(prev=ji->jed->child; prev; prev=prev->next)
    {
        if (prev->next == ji) break;
    }
    if (prev == NULL) return; // no such node?
    prev->next = ji->next;
    return;
}

Jed_rc jed_destroy_item(Jed_item *ji)
{
    DBG(">jed_destroy_item");
    jed_detach_item(ji);
    switch(ji->type)
    {
        case JED_TEXT:
            jed_text_destroy(ji);
            break;
        case JED_BUTTON:
            jed_button_destroy(ji);
            break;
        case JED_STRING:
            jed_string_destroy(ji);
            break;
        case JED_CONSOLE:
            jed_console_destroy(ji);
            break;
        case JED_LIST:
            jed_list_destroy(ji);
            break;
       default :
            TRACE(">>> Unknown type in jed_destroy_item");
            break;
    }
    DBG("<jed_destroy_item");
    return JED_SUCCESS;
}

Jed_rc jed_close(Jed *jed)
{
    Jed_item *next_ji;
    Jed_item *ji;

    DBG(">jed_close");
    for(ji = jed->child; ji; ji = next_ji)
    {
        DBG("...Deleting %08x", ji);
        next_ji = ji->next;
        jed_destroy_item(ji);
    }
    free(jed);
    DBG("<jed_close");
    return JED_SUCCESS;
}

Jed_rc jed_next_item(Jed *jed)
{
    Jed_item *ji;

    DBG(">jed_next_item");
    for(ji=jed->child; ji; ji=ji->next)
    {
        if (ji->selected)
        {
            ji->selected = FALSE;
            jed_repaint_item(ji, TRUE);
            break;
        }
    }

    if (ji)
    {
        for(ji=ji->next; ji; ji=ji->next)
        {
            if (ji->selectable) break;
        }
    }

    if (!ji)
    {
        for(ji=jed->child; ji; ji=ji->next)
        {
            if (ji->selectable) break;
        }
    }
    if (ji)
    {
        ji->selected = TRUE;
        jed_repaint_item(ji, TRUE);
    }
    DBG("<jed_next_item");
    return JED_SUCCESS;
}

Jed_rc jed_currently_selected_item(Jed *jed, Jed_item **rtn_ji)
{
    Jed_item *ji;

    DBG(">jed_currently_selected_item");
    for(ji=jed->child; ji; ji=ji->next)
    {
        if (ji->selected) break;
    }
    rtn_ji[0] = ji;
    DBG("<jed_currently_selected_item");
    return JED_SUCCESS;
}

Jed_rc jed_handle_char(Jed *jed, int c)
{
    Jed_item *ji;

    DBG(">jed_handle_char");
    jed_currently_selected_item(jed, &ji);
    switch(ji->type)
    {
        case JED_TEXT:
        case JED_GENERIC:
        case JED_BUTTON:
            break;
        case JED_CONSOLE:
            jed_console_handle_char(ji, c);
            break;
        case JED_LIST:
            jed_list_handle_char(ji, c);
            break;
        case JED_STRING:
            jed_string_handle_char(ji, c);
            break;
    }
    DBG("<jed_handle_char");
    return JED_SUCCESS;
}

static long isqrt(long r)
{
	long s;
	long s2;
	long hi = r;
	long lo = 0;

	while((hi-lo) > 1)
	{
		s = (hi+lo)/2;
		s2 = s*s;
		if (s2 > r) hi = s;
		else if (s2 < r) lo = s;
		else return s;
	}
	return (hi+lo)/2;
}

Jed_rc jed_motion(
    Jed_item *ji,
    int rate,
    int start_x,
    int start_y,
    int end_x,
    int end_y)
{
    long r;
    long dx = (end_x - start_x);
    long dy = (end_y - start_y);
    long r2 = dx*dx+dy*dy;

    DBG(">jed_motion");
    r = isqrt(r2);

    ji->dx = (r<<8)/dx*rate;
    ji->dy = (r<<8)/dy*rate;
    ji->start_x = start_x << 8;
    ji->start_y = start_y << 8;
    ji->end_x = end_x << 8;
    ji->end_y = end_y << 8;
    DBG("<jed_motion");
    return JED_SUCCESS;
}

Jed_rc jed_animate(Jed *jed)
{
    Jed_item *ji;
    int done;
    int paint_item = 0;

    DBG(">jed_animate");
    done = 1;
    for(ji=jed->child; ji; ji = ji->next)
    {
        if (ji->dx || ji->dy)
        {
            ji->x = ji->start_x >> 8;
            ji->y = ji->start_y >> 8;
	        ji->mid_x = ji->start_x;
	        ji->mid_y = ji->start_y;
            done = 0;
        }
    }

//    jed_repaint(jed);
    while(!done)
    {
        done = 1;
        for(ji=jed->child; ji; ji = ji->next)
        {
            paint_item = FALSE;
            if (ji->dx > 0)
            {
                if (ji->x <= (ji->end_x>>8))
                {
                    done = 0;
                    paint_item = TRUE;
                    ji->mid_x += ji->dx;
        		    ji->x = ji->mid_x>>8;
                }
	        }
    	    else if (ji->dx < 0)
	        {
                if (ji->x >= (ji->end_x>>8))
                {
                    done = 0;
                    paint_item = TRUE;
                    ji->mid_x += ji->dx;
                    ji->x = ji->mid_x>>8;
                }
            }
            if (ji->dy > 0)
            {
                if (ji->y < (ji->end_y>>8))
                {
                    done = 0;
                    paint_item = TRUE;
                    ji->mid_y += ji->dy;
        		    ji->y = ji->mid_y>>8;
                }
	        }
    	    else if (ji->dy < 0)
	        {
                if (ji->y > (ji->end_y>>8))
                {
                    done = 0;
                    paint_item = TRUE;
                    ji->mid_y += ji->dy;
                    ji->y = ji->mid_y>>8;
                }
            }
            if (paint_item) jed_repaint_item(ji, TRUE);
        }
    }
    jed_repaint(jed);
    DBG("<jed_animate");
    return JED_SUCCESS;
}

void jed_error_noise(Jed *jed)
{
    DBG(">jed_error_noise");
    stop_tone();
    AppGeneric_pause(jed->mm->m_process, 50);
    play_tone(0);
    AppGeneric_pause(jed->mm->m_process, 125);
    stop_tone();
    DBG("<jed_error_noise");
}

Jed_rc jed_main(Jed *jed, Jed_item **rtn_ji, long timeout)
{
      return jed_main_ex(jed, rtn_ji, timeout, 1);//no repaint
}

Jed_rc jed_select(Jed_item *in_ji)
{
    Jed *jed = ji->jed;
    Jed_item *ji;

    for(ji=jed->child; ji; ji = ji->next)
        ji->selected = 0;
    in_ji->selected=1;
    return JED_SUCCESS;
}
Jed_rc jed_main_ex(Jed *jed, Jed_item **rtn_ji, long timeout, int repaint)
{
      struct Message* message;
      bool exit_loop = FALSE;
      int key;
      Jed_item *ji;


      DBG(">jed_main_ex");

      if (repaint)
      {
        for(ji=jed->child; ji; ji = ji->next)
            ji->selected = 0;

        jed_next_item(jed);
 
         //jed_animate(jed);

        jed_repaint(jed);
      }
      //  Main loop of the application.
      while(!exit_loop)
      {
        // poll every timeout thousandths of a second for a message
        message = cWinApp_get_message(jed->mm->m_process, timeout, 1, MSG_USER);
        if (message==NULL)
        {
            jed_process_message(jed, message);
        }
        else switch(message->msgid)
        {
            case MSG_SHUTUP:     //  Processes system exit signal.
            case MSG_QUIT:
                exit_loop = TRUE;
                break;
            case MSG_GOTFOCUS:   //  Redraws screen.
                break;
            case MSG_KEYDOWN:    //  Processes keyboard messages.
            case MSG_CHARTYPED:
                key = Message_get_key_param(message)->scancode;
                switch(key)
                {
                    case KEY_ESC:
                    {
                        exit_loop = TRUE;
                        rtn_ji[0] = NULL;
                        break;
                    }
                    case KEY_TAB:
                    {
                        jed_next_item(jed);
                        break;
                    }
                    case KEY_ENTER:
                    {
                        jed_currently_selected_item(jed, rtn_ji);
                        if (!rtn_ji[0]) break;
                        if (rtn_ji[0]->type == JED_BUTTON ||
                            rtn_ji[0]->type == JED_STRING ||
                            rtn_ji[0]->type == JED_LIST)
                        {
                            exit_loop = TRUE;
                            break;
                        }
                    }
                    case KEY_UP:
                    case KEY_DOWN:
                    case KEY_LEFT:
                    case KEY_RIGHT:
                    case KEY_DEL:
                    case KEY_BACKSPACE:
                    {
                        jed_handle_char(jed, key);
                        break;
                    }
                    default:
                    {
                        DBG("...Entering jed_handle_char");
                        if (message->msgid == MSG_CHARTYPED)
                        {
                            key = Message_get_key_param(message)->ch;
                            jed_handle_char(jed, key);
                        }
                        DBG("...Exiting jed_handle_char");
                        break;
                    }
                }
                break;
            default:             //  Processes all unprocessed messages.
                {
                    Jed_rc rc;
                    rc = jed_process_message(jed, message);
                    if (rc == 0)
                        cWinApp_defproc(jed->mm->m_process, message);
                }
                break;
       }
       DBG("...About to delete message");
       if (message) Message_delete(message);
       DBG("...Exiting message");
    }  //  while(!exit_loop)
    DBG("<jed_main");
    return JED_SUCCESS;
}

char *jed_get_value(Jed_item *ji)
{
    switch(ji->type) {
        case JED_BUTTON: return jed_button_get_value(ji);
        case JED_STRING: return jed_string_get_value(ji);
        case JED_LIST: return jed_list_get_value(ji);
        case JED_TEXT: return jed_text_get_value(ji);
        default: return "JED cannot return a value";
    }
}

Jed_rc jed_set_value(Jed_item *ji, char *s)
{
    switch(ji->type) {
        case JED_BUTTON: return jed_button_set_value(ji, s);
        case JED_STRING: return jed_string_set_value(ji, s);
        case JED_LIST: return jed_list_set_value(ji,s );
        case JED_TEXT: return jed_text_set_value(ji, s);
        default: return -1;
    }
    return -1;
}

Jed_rc jed_generic_add(Jed *jed, Jed_item *ji)
{
    if (!jed->child)
    {
        jed->child = ji;
    }
    else
    {
        Jed_item *x;
        for(x=jed->child; x->next; x = x->next);
        x->next = ji;
    }
    return 0;
}

#include "jed_string.c"
#include "jed_button.c"
#include "jed_text.c"
#include "jed_console.c"
#include "jed_list.c"

