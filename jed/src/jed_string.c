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
 
#define KEY_FUNCTION KEY_CONTROL

static char uppercase[] = {
/*32*/ ' ','!','"','#','$','%','&','"','(',')','*','+','<','_','>','?',
/*48*/ ')','!','@','#','$','%','^','&','*','(',':',':','<','+','>','?',
/*64*/ '@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
/*80*/ 'p','q','r','s','t','u','v','w','x','y','z','{','|','}','^','_',
/*96*/ '~','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
/*112*/'P','Q','R','S','T','U','V','W','X','Y','Z','{','|','}','~','~'
};
Jed_rc jed_string_repaint(Jed_item *ji);
Jed_rc jed_string_handle_char(Jed_item *ji, int c);

Jed_rc jed_string_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, int buflen, char *value, struct Font *font)
{
    DBG(">jed_string_new");
    ji[0] = CALLOC(1, Jed_item);
    ji[0]->jed = jed;
    ji[0]->type = JED_STRING;
    ji[0]->x = x;
    ji[0]->y = y;
    ji[0]->w = w;
    ji[0]->h = h;
    ji[0]->value = CALLOC(buflen+1, char);
    ji[0]->buflen = buflen;
    strncpy(ji[0]->value, value, buflen);
    ji[0]->value[buflen] = 0;
    ji[0]->selectable = TRUE;
    ji[0]->selected = FALSE;
    if (font == NULL)
    {
        ji[0]->font = jed->font;
    }
    else
    {
        ji[0]->font = font;
    }
    ji[0]->char_w = Font_get_char_width(ji[0]->font,  'm');
    ji[0]->char_h = Font_get_char_height(ji[0]->font);
    jed_generic_add(jed, ji[0]);
//    jed_string_repaint(ji[0]);
    DBG(">jed_string_new");
    return JED_SUCCESS;
}

Jed_rc jed_string_destroy(Jed_item *ji)
{
    DBG(">jed_string_destroy");
    free(ji->value);
    free(ji);
    DBG("<jed_string_destroy");
}

int jed_string_len(Jed_item *ji, char *s, int w)
{
    char *tmp = strdup(s);
    int len = strlen(tmp);
    int x;

    DBG(">jed_string_len");
    for(x = Font_string_width(ji->font, tmp);
        x > w;
        x = Font_string_width(ji->font, tmp))
    {
        len--;
        tmp[len] = 0;
    }
    free(tmp);
    DBG("<jed_string_len");
    return len;
}

Jed_rc jed_string_repaint(Jed_item *ji)
{
    char *tmp;
    int x;
    int len;
    int box;

    DBG(">jed_string_repaint");
    if (ji->selected)
    {
        box = ji->jed->other2;
    }
    else
    {
        box = ji->jed->bgnd;
    }
    TGraph_set_color(ji->jed->mm->m_gfx, box);
    TGraph_fill_rect(ji->jed->mm->m_gfx, ji->x, ji->y, ji->w, ji->h);

    TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->other1);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x, ji->y, ji->x+ji->w-1, ji->y);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x, ji->y, ji->x, ji->y+ji->h-1);

    TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->fgnd);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x+1, ji->y+1, ji->x+ji->w-2, ji->y+1);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x+1, ji->y+1, ji->x+1, ji->y+ji->h-2);

    TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->bgnd);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x+1, ji->y+ji->h-2, ji->x+ji->w-2, ji->y+ji->h-2);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x+ji->w-2, ji->y+ji->h-2, ji->x+ji->w-2, ji->y-1);

    TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->other2);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x, ji->y+ji->h-1, ji->x+ji->w-1, ji->y+ji->h-1);
    TGraph_draw_line(ji->jed->mm->m_gfx, ji->x+ji->w-1, ji->y+ji->h-1, ji->x+ji->w-1, ji->y);

    len = jed_string_len(ji, &ji->value[ji->leftchar], ji->w-4);
    while (ji->cursor > ji->leftchar+len)
    {
        ji->leftchar++;
        len = jed_string_len(ji, &ji->value[ji->leftchar], ji->w-4);
    }
    tmp = strdup(&ji->value[ji->leftchar]);
    tmp[len] = 0;
    Graphics_set_font(ji->jed->mm->m_gfx, ji->font);
    TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->fgnd);
    DisplayGraphics_draw_text(ji->jed->mm->m_gfx, tmp, ji->x+2, ji->y+2);
//    ji->rightchar = strlen(tmp)+ji->leftchar;
    if (ji->selected)
    {
        tmp[ji->cursor - ji->leftchar] = 0;
        x = Font_string_width(ji->font, tmp);

        TGraph_draw_line(ji->jed->mm->m_gfx, ji->x+x+1, ji->y, ji->x+x+1, ji->y+ji->char_h);
    }
    free(tmp);
    DBG("<jed_string_repaint");
    return JED_SUCCESS;
}

Jed_rc jed_string_handle_char(Jed_item *ji, int c)
{
    static short shift=0;

    DBG(">jed_string_handle_char");
    switch(c)
    {
        case KEY_SHIFT:
        {
            if (shift == KEY_SHIFT) shift = 0;
            else shift = KEY_SHIFT;
        } break;
        case KEY_FUNCTION:
        {
            if (shift == KEY_FUNCTION) shift = 0;
            else shift = KEY_FUNCTION;
        } break;
        case KEY_LEFT:
        {
            if (ji->cursor == 0)
            {
                jed_error_noise(ji->jed);
                shift = 0;
                goto EARLY_EXIT;
            }
            if (shift)
            {
                ji->cursor = 0;
                ji->leftchar = 0;
            }
            else
            {
                ji->cursor--;
                if (ji->cursor < ji->leftchar)
                    ji->leftchar = ji->cursor;
            }
            jed_repaint_item(ji, TRUE);
            shift = 0;
        } break;
        case KEY_RIGHT:
        {
            if (ji->cursor == strlen(ji->value))
            {
                jed_error_noise(ji->jed);
                shift = 0;
                goto EARLY_EXIT;
            }
            if (shift)
            {
                ji->cursor = strlen(ji->value);
                while (ji->cursor > jed_string_len(ji, &ji->value[ji->leftchar], ji->w-4)+ji->leftchar)
                {
                    ji->leftchar++;
                }
            }
            else
            {
                ji->cursor++;
            }
            jed_repaint_item(ji, TRUE);
            shift = 0;
        } break;
        case KEY_UP:
        case KEY_DOWN:
            shift=0;
            break;
        case KEY_BACKSPACE:
        case KEY_DEL:
            if (!shift && ji->cursor == 0)
            {
                jed_error_noise(ji->jed);
                shift = 0;
                goto EARLY_EXIT;
            }
            if (shift)
            {
                ji->value[0] = 0;
                ji->leftchar = 0;
                ji->cursor = 0;
            }
            else
            {
                memmove(&ji->value[ji->cursor-1],
                    &ji->value[ji->cursor],
                    strlen(&ji->value[ji->cursor]));
                ji->value[strlen(ji->value)-1] = 0;
                ji->cursor--;
            }
            shift = 0;
            jed_repaint_item(ji, TRUE);
            break;
#ifdef COMMENT
        case KEY_DEL:
            if (!shift && ji->value[ji->cursor] == 0)
            {
            if (shift)
            {
                ji->value[0] = 0;
                ji->leftchar = 0;
                ji->cursor = 0;
            }
                jed_error_noise(ji->jed);
                shift = 0;
                goto EARLY_EXIT;
            }
            if (shift)
            {
                ji->value[ji->cursor] = 0;
            }
            else
            {
                memmove(&ji->value[ji->cursor],
                    &ji->value[ji->cursor+1],
                    strlen(&ji->value[ji->cursor]));
            }
            shift = 0;
            jed_repaint_item(ji, TRUE);
            break;
#endif
        default:
            if (c >=32 && c <128)
            {
                if (strlen(ji->value) == ji->buflen)
                {
                    jed_error_noise(ji->jed);
                    shift = 0;
                    goto EARLY_EXIT;
                }
                else
                {
                    if (shift == KEY_SHIFT)
                    {
                        c = uppercase[c-32];
                    }
                    memmove(&ji->value[ji->cursor+1],
                        &ji->value[ji->cursor],
                        ji->buflen-ji->cursor+1);
                    ji->value[ji->cursor] = (char) c;
                    if (ji->cursor != strlen(ji->value))
                        ji->cursor++;
                    shift = 0;
                    jed_repaint_item(ji, TRUE);
                }
            }
            else
            {
                jed_error_noise(ji->jed);
                shift = 0;
                goto EARLY_EXIT;
            }
            shift = 0;
            break;
    }
EARLY_EXIT:
    DBG("<jed_string_handle_char");
    return JED_SUCCESS;
}


Jed_rc jed_string_set_value(Jed_item *ji, char *value)
{
    DBG(">jed_string_set_value");
    strncpy(ji->value, value, ji->buflen);
    ji->value[ji->buflen] = 0;
    ji->cursor = strlen(ji->value);
    ji->leftchar = 0;
    while (ji->cursor > jed_string_len(ji, &ji->value[ji->leftchar], ji->w-4)+ji->leftchar)
    {
        ji->leftchar++;
    }
    jed_repaint_item(ji, TRUE);
    DBG("<jed_string_set_value");
    return JED_SUCCESS;
}

char *jed_string_get_value(Jed_item *ji)
{
    DBG(">jed_string_get_value");
    DBG("<jed_string_get_value");
    return ji->value;
}

