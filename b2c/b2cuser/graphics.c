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
static void init_graphics()
{
    b2c->colors[0] = CLR_WHITE;
    b2c->colors[1] = CLR_LTGRAY;
    b2c->colors[2] = CLR_DKGRAY;
    b2c->colors[3] = CLR_BLACK;

    b2c->paper = b2c->colors[0];
    b2c->ink = b2c->colors[3];

    b2c->font = cool_bold_font;

    TGraph_fill_screen(b2c->main_module.m_gfx, b2c->paper);
    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
    DisplayGraphics_show(b2c->main_module.m_gfx);
}

static void destroy_graphics()
{
}

void _rect(int x0, int y0, int w, int h)
{
    DBG(">_rect");

    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
    if (_c_coords)
        DisplayGraphics_draw_rect(b2c->main_module.m_gfx, x0, y0, w, h);
    else
        DisplayGraphics_draw_rect(b2c->main_module.m_gfx, 80+x0, 50-y0, w, h);
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);

    DBG("<_rect");
}

void _rectfill(int x0, int y0, int w, int h)
{
    DBG(">_rectfill");

    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
    if (_c_coords)
        DisplayGraphics_fill_rect(b2c->main_module.m_gfx, x0, y0, w, h);
    else
        DisplayGraphics_fill_rect(b2c->main_module.m_gfx, 80+x0, 50-y0, w, h);
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);

    DBG("<_rectfill");
}

void _printxy(int x, int y, char *fmt, ...)
{
    va_list parameters;
    int i;

    DBG(">_printxy");

    va_start( parameters, fmt );
    vsprintf( b2c->buf, fmt, parameters );
    va_end( parameters );


	if (cyberpeek_timer) _cyberpeek();
    Graphics_set_font(b2c->main_module.m_gfx, b2c->font);
    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
    if (_c_coords)
        DisplayGraphics_draw_text(b2c->main_module.m_gfx, b2c->buf, x, y);
    else
        DisplayGraphics_draw_text(b2c->main_module.m_gfx, b2c->buf, 80+x, 50-y);
    if (_show_)DisplayGraphics_show(b2c->main_module.m_gfx);

    DBG("<_printxy");
}

void _line(int x0, int y0, int x1, int y1)
{
    DBG(">_line");

    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
    if (_c_coords)
        DisplayGraphics_draw_line(b2c->main_module.m_gfx, x0, y0, x1, y1);
    else
        DisplayGraphics_draw_line(b2c->main_module.m_gfx, 80+x0, 50-y0, 80+x1, 50-y1);
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);

    DBG("<_line");
}

void _point(int x, int y)
{
    DBG(">_point");

    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
    if (_c_coords)
        DisplayGraphics_set_pixel(b2c->main_module.m_gfx, x, y, b2c->ink);
    else
        DisplayGraphics_set_pixel(b2c->main_module.m_gfx, 80+x, 50-y, b2c->ink);
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);

    DBG("<_point");
}

void _ink(int ink)
{
    b2c->ink = b2c->colors[ink&3];
}

void _paper(int paper)
{
    b2c->paper = b2c->colors[paper&3];
}

void _font(char *s)
{
	if (b2c->font_in_memory)
	{
		Font_dtor(b2c->font, FREE_MEMORY);
		b2c->font_in_memory = FALSE;
		b2c->font = cool_normal_font;
	}
    if (SAME(s, "cool_bold_font")) b2c->font = cool_bold_font;
    else if (SAME(s, "cool_normal_font")) b2c->font = cool_normal_font;
    else if (SAME(s, "mini_normal_font")) b2c->font = mini_normal_font;
    else if (SAME(s, "mini_bold_font")) b2c->font = mini_bold_font;
    else
    {
		b2c->font = malloc(sizeof(struct Font));
        Font_ctor_Ex(b2c->font, s, FALSE, 0 );
		b2c->font_in_memory = TRUE;
    }
    b2c->font_changed = 1;
	_font_update();
}

void _cls()
{
    TGraph_fill_screen(b2c->main_module.m_gfx, b2c->paper);
    b2c->currline = 0;
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);
}

void _page(int page)
{
	DisplayGraphics_set_page(b2c->main_module.m_gfx, page % 2);
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);
}
void _pagecopy(int from, int to, int x, int y, int w, int h)
{
	DisplayGraphics_page_copy(b2c->main_module.m_gfx, from % 2, to % 2, x, y ,w ,h);
    if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);
}

int _stringwidth(char *s)
{
    Graphics_set_font(b2c->main_module.m_gfx, b2c->font);
	return Graphics_string_width(b2c->main_module.m_gfx, s);
}

int _stringheight(char *s)
{
    Graphics_set_font(b2c->main_module.m_gfx, b2c->font);
	return Graphics_get_char_height(b2c->main_module.m_gfx );
}

static int get_number_of_chars_char_wrap(int w, char *s)
{
	int i;
	int len = strlen(s);
	int pixels;

	for(i=0; i<len; i++)
	{
		if (s[i] == '\n') return i+1;
		pixels = DisplayGraphics_string_width_Ex(b2c->main_module.m_gfx, s, i+1);
		if (pixels == w) return i+1;
		else if (pixels > w) return i;
	}
	return i;
}

static int get_number_of_chars_word_wrap(int w, char *s)
{
	int i;
	int len = strlen(s);
	int pixels;

	for(i=0; i<len; i++)
	{
		if (s[i] == '\n') return i+1;
		pixels = DisplayGraphics_string_width_Ex(b2c->main_module.m_gfx, s, i+1);
		if (pixels >= w) 
		{
			int n = i;
			while(s[n] != ' ' && s[n] != '\n')
				n--;
			return n+1;
		}
	}
	return i;
}

static void align_text(int x, int y, int w, int align, char *s)
{
	int len=0;
	int pixels;

	switch(align) {
		case ALIGN_LEFT:
		{
			while (s[0] == ' ' || s[0] == '\n')	strcpy(s, &s[1]);
			DisplayGraphics_draw_text(b2c->main_module.m_gfx, s, x, y);
			break;
		}
		case ALIGN_RIGHT:
		{
			while (s[0] == ' ' || s[0] == '\n')	strcpy(s, &s[1]);
			len = strlen(s);
			while (len && (s[len-1]==' ' || s[len-1]=='\n'))
			{
				len--;
				s[len]=0;
			}
			pixels = DisplayGraphics_string_width(b2c->main_module.m_gfx, s);
			DisplayGraphics_draw_text(b2c->main_module.m_gfx, s, x+(w-pixels), y);
			break;
		}
		case ALIGN_CENTER:
		{
			while (s[0] == ' ' || s[0] == '\n')	strcpy(s, &s[1]);
			len = strlen(s);
			while (len && (s[len-1]==' ' || s[len-1]=='\n'))
			{
				len--;
				s[len]=0;
			}
			pixels = DisplayGraphics_string_width(b2c->main_module.m_gfx, s);
			DisplayGraphics_draw_text(b2c->main_module.m_gfx, s, x+(w-pixels)/2, y);
			break;
		}
	}
}

int _wrap(int x, int y, int w, int h, int align, int wraptype, char *s)
{
	int i;
	int len = strlen(s);
	int n;
	int max_y;
	int new_y;
	int new_x;

    Graphics_set_font(b2c->main_module.m_gfx, b2c->font);
    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
	if (!_c_coords) 
	{
		x=x+80;
		y=50-y;
	}
	max_y = y+h;
	new_y = y;
	new_x = x;
	for(i=0; i<len; /**/)
	{
		if (new_y+b2c->ht >= max_y) break;
		switch(wraptype) {	
		case WRAP_CHAR: n = get_number_of_chars_char_wrap(w, &s[i]); break;
		case WRAP_WORD: n = get_number_of_chars_word_wrap(w, &s[i]); break;
		}
		strncpy(b2c->buf, &s[i], n);
		b2c->buf[n] = 0;
		align_text(x, new_y, w, align, b2c->buf);
		i = i + n;
		new_y = new_y + b2c->ht;
	}
    if (_show_)DisplayGraphics_show(b2c->main_module.m_gfx);

	return i;
}

static void CirclePoints(int x, int y, int dx, int dy)
{
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x+dx, y+dy, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x+dy, y+dx, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x+dy, y-dx, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x+dx, y-dy, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x-dx, y-dy, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x-dy, y-dx, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x-dy, y+dx, b2c->ink);
	DisplayGraphics_set_pixel( b2c->main_module.m_gfx, x-dx, y+dy, b2c->ink);
}
void _circle(int x, int y, int r)
{
	int dx, dy;
	int d, deltaE, deltaSE;

	if (!_c_coords) 
	{
		x=x+80;
		y=50-y;
	}
	dx=0;
	dy=r;
	d = 1 - r;
	deltaE = 3;
	deltaSE = -2*r+5;
    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
	CirclePoints(x,y,dx,dy);

	while (dy > dx)
	{
		if (d < 0)
		{
			d = d+deltaE;
			deltaE=deltaE+2;
			deltaSE=deltaSE+2;
			dx=dx+1;
		}
		else
		{
			d=d+deltaSE;
			deltaE=deltaE+2;
			deltaSE=deltaSE+2;
			dx=dx+1;
			dy=dy-1;
		}
		CirclePoints(x,y,dx,dy);
	}
    if (_show_)DisplayGraphics_show(b2c->main_module.m_gfx);
}

static void CircleLines(int x, int y, int dx, int dy)
{
	DisplayGraphics_draw_line(b2c->main_module.m_gfx, x+dx, y+dy, x-dx, y+dy);
	DisplayGraphics_draw_line(b2c->main_module.m_gfx, x+dy, y+dx, x-dy, y+dx);
	DisplayGraphics_draw_line(b2c->main_module.m_gfx, x+dy, y-dx, x-dy, y-dx);
	DisplayGraphics_draw_line(b2c->main_module.m_gfx, x+dx, y-dy, x-dx, y-dy);
}

void _circfill(int x, int y, int r)
{
	int dx, dy;
	int d, deltaE, deltaSE;

	if (!_c_coords) 
	{
		x=x+80;
		y=50-y;
	}
	dx=0;
	dy=r;
	d = 1 - r;
	deltaE = 3;
	deltaSE = -2*r+5;
    TGraph_set_color(b2c->main_module.m_gfx, b2c->ink);
	CircleLines(x,y,dx,dy);

	while (dy > dx)
	{
		if (d < 0)
		{
			d = d+deltaE;
			deltaE=deltaE+2;
			deltaSE=deltaSE+2;
			dx=dx+1;
		}
		else
		{
			d=d+deltaSE;
			deltaE=deltaE+2;
			deltaSE=deltaSE+2;
			dx=dx+1;
			dy=dy-1;
		}
		CircleLines(x,y,dx,dy);
	}
    if (_show_)DisplayGraphics_show(b2c->main_module.m_gfx);
}