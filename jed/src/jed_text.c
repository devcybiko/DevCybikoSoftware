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

Jed_rc jed_text_repaint(Jed_item *ji);

Jed_rc jed_text_new(Jed_item **ji, Jed *jed,
    int x, int y, int w, int h, char *value, struct Font *font)
{
    ji[0] = CALLOC(1, Jed_item);
    ji[0]->jed = jed;
    ji[0]->type = JED_TEXT;
    ji[0]->x = x;
    ji[0]->y = y;
    ji[0]->w = w;
    ji[0]->h = h;
    ji[0]->value = strdup(value);
    ji[0]->selectable = 0;
    ji[0]->selected = 0;
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
//    jed_text_repaint(ji[0]);
    return JED_SUCCESS;
}

Jed_rc jed_text_destroy(Jed_item *ji)
{
    free(ji->value);
    free(ji);
    return JED_SUCCESS;
}

Jed_rc jed_text_repaint(Jed_item *ji)
{
    if (ji->w && ji->h)
    {
        TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->fgnd);
        Graphics_set_font(ji->jed->mm->m_gfx, ji->font);
        DisplayGraphics_draw_text_Ex(ji->jed->mm->m_gfx, ji->value,
            ji->x+(ji->w-Font_string_width(ji->font, ji->value))/2,
            ji->y+(ji->h-ji->char_h)/2, ji->w);
    }
    else
    {
        TGraph_set_color(ji->jed->mm->m_gfx, ji->jed->fgnd);
        Graphics_set_font(ji->jed->mm->m_gfx, ji->font);
        Graphics_draw_text(ji->jed->mm->m_gfx, ji->value, ji->x, ji->y);
    }
    return JED_SUCCESS;
}

char *jed_text_get_value(Jed_item *ji)
{
    return ji->value;
}

Jed_rc jed_text_set_value(Jed_item *ji, char *s)
{
    if (ji->value) free(ji->value);
    ji->value = strdup(s);
    return JED_SUCCESS;
}
