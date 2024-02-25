/**
  * The B2C project is a set of programs and libraries
  * that comprise a languate translator.  B2C compiles
  * a BASIC program into C which is compiled by the Cybiko
  * SDK 2.10 into an application.
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
static void _redisp()
{
    int i;

    DBG(">_redisp");
    if (b2c->font_changed) _font_update();
    TGraph_fill_screen (b2c->main_module.m_gfx, b2c->paper);
    Graphics_set_font(b2c->main_module.m_gfx, b2c->font);
    Graphics_set_color(b2c->main_module.m_gfx, b2c->ink);
    b2c->x = 0;
    b2c->y = 0;

    for(i=0; i<b2c->currline; i++)
    {
        Graphics_draw_text(b2c->main_module.m_gfx, b2c->lines[i], b2c->x, b2c->y);
        b2c->y += b2c->ht;
    }
    if (b2c->y)
    {
        b2c->x = Graphics_string_width(b2c->main_module.m_gfx, b2c->lines[i-1]);
        b2c->y -= b2c->ht;
//        if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);
        DisplayGraphics_show(b2c->main_module.m_gfx);
    }
    DBG("<_redisp");
}

static void destroy_print()
{
    int i;
    DBG(">_destroy_print");

    for(i=0; i<MAX_LINES; i++)
        free(b2c->lines[i]);
    free(b2c->lines);

    DBG("<_destroy_print");
}

static void init_print()
{
    int i;
    DBG(">_init_print");
	
    b2c->ht = Font_get_char_height(b2c->font);
    b2c->nlines = MAX_PIXELS_HEIGHT / b2c->ht;
    b2c->currline = 0;
    b2c->font_changed = 0;
    b2c->lines = (char **) calloc(sizeof(char *), MAX_LINES);

    for(i=0; i<MAX_LINES; i++)
    {
        b2c->lines[i] = (char *) calloc(LINE_LENGTH, sizeof(char));
    }
    DBG("<_init_print");
}

void _print(char *fmt, ...)
{
    va_list parameters;
    int i;

    va_start( parameters, fmt );
    vsprintf( b2c->buf, fmt, parameters );
    va_end( parameters );

	if (cyberpeek_timer) _cyberpeek();
    //TRACE(">_print %s", b2c->buf);

    while (b2c->currline >= b2c->nlines)
    {
        /** Scroll **/
        char *tmp = b2c->lines[0];
        memmove(&b2c->lines[0], &b2c->lines[1], sizeof(char *)*(b2c->nlines-1));
        b2c->lines[b2c->nlines-1] = tmp;
        b2c->currline--;
    }
    strncpy(b2c->lines[b2c->currline], b2c->buf, LINE_LENGTH);
    b2c->lines[b2c->currline][LINE_LENGTH-1]=0;

    b2c->currline++;

    _redisp();

    DBG("<_print");
}

