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

Jed_rc jed_list_repaint(Jed_item *ji);
Jed_rc jed_list_handle_char(Jed_item *ji, int c);

Jed_rc jed_list_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, int lines, struct Font *font)
{
    ji[0] = CALLOC(1, Jed_item);
    ji[0]->jed = jed;
    ji[0]->type = JED_LIST;
    ji[0]->x = x;
    ji[0]->y = y;
    ji[0]->w = w;
    ji[0]->h = h;
    ji[0]->value = (char *) CALLOC(lines, char *);
    ji[0]->maxlines = lines;
    ji[0]->selectable = TRUE;
    ji[0]->selected = FALSE;
    ji[0]->topline = 0;
    ji[0]->selected_item = 0;
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
    ji[0]->nlines = (h-4) / ji[0]->char_h;
//    jed_list_repaint(ji[0]);
    return JED_SUCCESS;
}

Jed_rc jed_list_destroy(Jed_item *ji)
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

Jed_rc jed_list_repaint(Jed_item *ji)
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
        if (lines[i])
        {
            char *tmp;
            int len = jed_string_len(ji, lines[i], ji->w-6);
            tmp = strdup(lines[i]);
            tmp[len]=0;
            if (i == ji->selected_item)
            {
                TGraph_fill_rect(ji->jed->mm->m_gfx, ji->x+2, j, ji->w-2, ji->char_h);
                TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->bgnd);
            }
            DisplayGraphics_draw_text_Ex(ji->jed->mm->m_gfx, tmp, ji->x+3, j, ji->w-3);
            if (i == ji->selected_item)
            {
                TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->fgnd);
            }
            free(tmp);
        }
        j += ji->char_h;
    }
    return JED_SUCCESS;
}

static void jed_list_scroll(Jed_item *ji, int direction)
{
    int tmp;
    char **lines;

    lines = ji->value;

    ji->selected_item += direction;
    if (ji->selected_item < 0)
    {
        jed_error_noise(ji->jed);
        ji->selected_item = 0;
    }

    if (ji->selected_item >= ji->nitems)
    {
        jed_error_noise(ji->jed);
        ji->selected_item = ji->nitems-1;
    }

    if (ji->selected_item <= ji->nlines/2)
    {
        ji->topline = 0;
    }
    else if (ji->selected_item >= ji->nitems-ji->nlines/2)
    {
        ji->topline = ji->nitems-ji->nlines;
        if (ji->topline < 0) ji->topline = 0;
    }
    else
    {
        ji->topline = ji->selected_item-ji->nlines/2;
        if (ji->topline < 0) ji->topline = 0;
    }
    jed_repaint_item(ji, TRUE);
}

Jed_rc jed_list_handle_char(Jed_item *ji, int c)
{
    switch(c)
    {
        case KEY_UP:
        {
            jed_list_scroll(ji, -1);
        } break;
        case KEY_DOWN:
        {
            jed_list_scroll(ji, +1);
        } break;
        default:
            break;
    }
EARLY_EXIT:
    return JED_SUCCESS;
}

Jed_rc jed_list_add_item(Jed_item *ji, char *s)
{
    char **lines = ji->value;
    int i;
    if (ji->nitems >= ji->maxlines) return -1;
    i = ji->nitems++;
    lines[i] = strdup(s);
    if (i > ji->topline+ji->nlines)
    {
        ji->topline = i - ji->nlines;
        if (ji->topline < 0) ji->topline = 0;
    }
    ji->selected_item = i;
    return JED_SUCCESS;
}

Jed_rc jed_list_clear(Jed_item *ji)
{
    int i;
    char **lines = ji->value;
    for(i=0; i<ji->nitems; i++)
    {
        if (lines[i]) free(lines[i]);
        lines[i] = 0;
    }
    ji->selected_item = 0;
    ji->topline = 0;
    ji->nitems = 0;
    return JED_SUCCESS;
}

char *jed_list_get_value(Jed_item *ji)
{
    char **lines = ji->value;
    return lines[ji->selected_item];
}

Jed_rc jed_list_set_value(Jed_item *ji, char *s)
{
    int i;
    char **lines = ji->value;

    for(i=0; i<ji->nitems; i++)
    {
        if (SAME(lines[i], s))
        {
            ji->selected_item = i+1;
            jed_list_scroll(ji, -1);
            //ji->topline = i - ji->nlines;
            //if (ji->topline < 0) ji->topline = 0;
            //if (ji->topline > ji->maxlines-ji->nlines)
            //{
            //    ji->topline = ji->maxlines-ji->nlines;
            //    if (ji->topline < 0)
            //        ji->topline = 0;
            //}
        }
    }
    return JED_SUCCESS;
}
