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

Jed_rc jed_console_repaint(Jed_item *ji);
Jed_rc jed_console_handle_char(Jed_item *ji, int c);

Jed_rc jed_console_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, int lines, struct Font *font)
{
    ji[0] = CALLOC(1, Jed_item);
    ji[0]->jed = jed;
    ji[0]->type = JED_CONSOLE;
    ji[0]->x = x;
    ji[0]->y = y;
    ji[0]->w = w;
    ji[0]->h = h;
    ji[0]->value = (char *) CALLOC(lines, char *);
    ji[0]->maxlines = lines;
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
    ji[0]->nlines = (h-4) / ji[0]->char_h;
    ji[0]->topline = ji[0]->maxlines - ji[0]->nlines;
    jed_generic_add(jed, ji[0]);
    return JED_SUCCESS;
}

Jed_rc jed_console_destroy(Jed_item *ji)
{
    int i;
    char **lines = ji->value;
    for(i=0; i<ji->buflen; i++)
    {
        if (lines[i]) free(lines[i]);
    }
    free(ji->value);
    free(ji);
    return JED_SUCCESS;
}

Jed_rc jed_console_repaint(Jed_item *ji)
{
    int box;
    int i, j;
    char **lines = ji->value;

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

    TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->fgnd);

    lines = ji->value;

    Graphics_set_font(ji->jed->mm->m_gfx, ji->font);

    j=ji->y+1;
    for(i=ji->topline; i<ji->topline+ji->nlines; i++)
    {
        if (lines[i]!=NULL)
        {
            int len = jed_string_len(ji, lines[i], ji->w-6);
            lines[i][len]=0;
            DisplayGraphics_draw_text(ji->jed->mm->m_gfx, lines[i], ji->x+3, j);
        }
        j += ji->char_h;
    }
    return JED_SUCCESS;
}

static void jed_console_scroll(Jed_item *ji, int direction)
{
    int tmp;
    char **lines;

    tmp = ji->topline + ji->nlines*direction;

    lines = (char **) ji->value;
    if ((direction == -1) && (lines[ji->topline] == NULL))
    {
        jed_error_noise(ji->jed);
        return;
    }
    if ((direction == -1) && (ji->topline == 0))
    {
        jed_error_noise(ji->jed);
        return;
    }
    if ((direction == +1) && (ji->topline==ji->maxlines-ji->nlines))
    {
        jed_error_noise(ji->jed);
        return;
    }
    if (tmp < 0)
    {
        tmp = 0;
    }

    if (tmp > ji->maxlines-ji->nlines)
    {
        tmp = ji->maxlines-ji->nlines;
    }

    ji->topline = tmp;
    jed_repaint_item(ji, TRUE);
    return;
}

Jed_rc jed_console_handle_char(Jed_item *ji, int c)
{
    switch(c)
    {
        case KEY_UP:
        {
            jed_console_scroll(ji, -1);
        } break;
        case KEY_DOWN:
        {
            jed_console_scroll(ji, +1);
        } break;
        default:
            break;
    }
EARLY_EXIT:
    return JED_SUCCESS;
}

/*
Jed_rc jed_console_add_text(Jed_item *ji, char *s)
{
    char **lines = ji->value;
    if (lines[0] != NULL) free(lines[0]);
    memmove(&lines[0], &lines[1], sizeof(char *)*ji->maxlines);
    lines[ji->maxlines-1] = strdup(s);
    ji->topline = ji->maxlines - ji->nlines;
    return JED_SUCCESS;
}
*/

static void add_one_line(Jed_item *ji, char *s)
{
    char **lines = ji->value;
    if (lines[0] != NULL) free(lines[0]);
    memmove(&lines[0], &lines[1], sizeof(char *)*ji->maxlines);
    lines[ji->maxlines-1] = strdup(s);
    ji->topline = ji->maxlines - ji->nlines;
}

static int fit_text(Jed_item *ji, char *s, int len)
{
    int hi = len;
    int lo = 0;
    int last_len = 0;
    int width;

    width = Font_string_width_Ex(ji->font, s, len);
    if (width <= ji->w-6) return len;

    while(last_len != len)
    {
        last_len = len;
        len=(hi+lo)/2;
        width = Font_string_width_Ex( ji->font, s, len );
        if (width < ji->w-6)
        {
            lo=len;
        }
        else if (width > ji->w-6)
        {
            hi=len;
        }
    }
    return len;
}

static char txtbuf[64];
Jed_rc jed_console_add_text(Jed_item *ji, char *s)
{
    int len = strlen(s);
    int newlen=0;
    char *r;

    r = s;
    while(*r)
    {
        len = strlen(r);
        newlen = fit_text(ji, r, len);
        strncpy(txtbuf, r, newlen);
        txtbuf[newlen]=0;
        add_one_line(ji, txtbuf);
        r = &r[newlen];
    }
    return JED_SUCCESS;
}


Jed_rc jed_console_clear(Jed_item *ji)
{
    int i;
    char **lines = ji->value;

    for(i=0; i<ji->maxlines; i++)
    {
        if (lines[i]) free(lines[i]);
        lines[i] = 0;
    }
    ji->topline = ji->maxlines - ji->nlines;
    return JED_SUCCESS;
}
