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
static char **menu_list;
#define MAX_MENU 10
static void init_menu()
{
    int i;
    DBG(">_init_menu");
	menu_list = calloc(MAX_MENU, sizeof(char *));
    DBG("<_init_menu");
}

static void destroy_menu()
{
    int i;
    DBG(">_destroy_menu");
	free(menu_list);
    DBG("<_destroy_menu");
}

static void display_menu(int n, int item, int x, int y)
{
    int max_width = 0;
    int i;
    int w,h;

    for(i=0; i<n; i++)
    {
        w = Font_string_width(b2c->font, menu_list[i]);
        if (max_width < w) max_width = w;
    }
    w = max_width;
    h = b2c->ht * n;
	if (x > 160)
	{
		x = (160 - w)/2;
		y = (100 - h)/2;
	}
    DisplayGraphics_set_color(b2c->main_module.m_gfx, b2c->paper);
    DisplayGraphics_fill_rect(b2c->main_module.m_gfx, x-1, y-1, w+2, h+2);
    DisplayGraphics_set_color(b2c->main_module.m_gfx, b2c->ink);
    DisplayGraphics_set_font(b2c->main_module.m_gfx, b2c->font);
    for(i=0; i<n; i++)
    {
        DisplayGraphics_draw_text(b2c->main_module.m_gfx,
            menu_list[i],
            x,
            y+i*b2c->ht);
    }
    DisplayGraphics_fill_rect(b2c->main_module.m_gfx,
        x,
        y+item*b2c->ht,
        w,
        b2c->ht);
    DisplayGraphics_set_color(b2c->main_module.m_gfx, b2c->paper);
    DisplayGraphics_draw_text(b2c->main_module.m_gfx,
        menu_list[item],
        x,
        y+item*b2c->ht);
    DisplayGraphics_show(b2c->main_module.m_gfx);
}

void _menu(int x, int y, int *choice, ...)
{
    va_list parameters;
    int i;
	char *s;
    int key;
	int xtruex = 1;

    va_start( parameters, choice );
	s = va_arg(parameters, char *);
	for(i=0; s; i++)
	{
		menu_list[i] = s;
        s = va_arg(parameters, char *);
	}
    va_end( parameters );

    if (!_c_coords)  // x>160 causes the menu to be centered
	{
		x=x+80;
		y=50-y;
	}

    *choice = 0;
    display_menu(i,0, x, y);
    while(xtruex)
    {
		int key = _getkey();
        if (key == KEY_ENTER) break;
        if (key == KEY_DOWN)
        {
            (*choice)++;
            if (*choice >= i) *choice=0;
            display_menu(i, *choice, x, y);
        }
        if (key == KEY_UP)
        {
            (*choice)--;
            if (*choice < 0) *choice=i-1;
            display_menu(i, *choice, x, y);
        }
		_wait(1);
    }
    (*choice)++;
    DBG("<_menu");
}