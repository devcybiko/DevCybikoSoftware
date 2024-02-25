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
static void init_sprites()
{
    b2c->sprites = (struct _b2c_sprite *) calloc(_n_sprites, sizeof(struct _b2c_sprite));
}

static void destroy_sprites()
{
	int i;

    for(i=0; i<_n_sprites; i++)
    {
        if (b2c->sprites[i].bitmap)
        {
            BitmapSequence_dtor(b2c->sprites[i].bitmap, FREE_MEMORY);
            b2c->sprites[i].bitmap = NULL;
        }
    }
    free(b2c->sprites);
}


void _sprite(int n, char *filename)
{
	if (b2c->sprites[n].bitmap)
	{
		BitmapSequence_dtor(b2c->sprites[n].bitmap, FREE_MEMORY);
		b2c->sprites[n].bitmap = NULL;
	}

	if (filename)
	{
		b2c->sprites[n].bitmap = malloc(sizeof(struct BitmapSequence));
		if (filename[0] == '/')
		{
			struct FileInput file_input;
			FileInput_ctor_Ex( &file_input, filename);
			BitmapSequence_ctor(b2c->sprites[n].bitmap);
			if (BitmapSequence_load(b2c->sprites[n].bitmap, &file_input))
			{
				error = 0;
			}
			else
			{
				error = ERROR_FILE_OPEN;
			}
			FileInput_dtor( &file_input, LEAVE_MEMORY );
		}
		else
		{
			BitmapSequence_ctor_Ex(b2c->sprites[n].bitmap, filename);
		}
	}

	return;
}

void _move(int n, int x, int y, int z, int mode)
{
	if (b2c->sprites[n].bitmap)
	{
        if (_c_coords)
        {
            b2c->sprites[n].rect.x=x;
            b2c->sprites[n].rect.y=y;
        }
        else
        {
            b2c->sprites[n].rect.x=x+80;
            b2c->sprites[n].rect.y=50-y;
        }
		b2c->sprites[n].z = z;
		b2c->sprites[n].mode = mode;
	}
}

void _sprite_get(int n, int *x, int *y, int *z, int *mode, int *w, int *h)
{
	int cnt;
    struct Bitmap *bm;
    cnt = BitmapSequence_get_size(b2c->sprites[n].bitmap);
    bm = BitmapSequence_get_bitmap(
               b2c->sprites[n].bitmap, 
               b2c->sprites[n].z % cnt);
    *x = b2c->sprites[n].rect.x;
    *y = b2c->sprites[n].rect.y;
    *w = bm->w;
    *h = bm->h;
	*z = b2c->sprites[n].z;
	*mode = b2c->sprites[n].mode;
}

static void redraw_one(int i)
{
    int n;
    struct Bitmap *bm;

    if (!b2c->sprites[i].bitmap) return;

    DisplayGraphics_set_draw_mode(b2c->main_module.m_gfx, DM_OR);
    DisplayGraphics_set_bkcolor(b2c->main_module.m_gfx, b2c->paper);
    n = BitmapSequence_get_size(b2c->sprites[i].bitmap);
    bm = BitmapSequence_get_bitmap(
        b2c->sprites[i].bitmap, 
        b2c->sprites[i].z % n);
    b2c->sprites[i].rect.w = bm->w;
    b2c->sprites[i].rect.h = bm->h;
    DisplayGraphics_draw_bitmap(
        b2c->main_module.m_gfx,
        bm,
        b2c->sprites[i].rect.x,
        b2c->sprites[i].rect.y,
        b2c->sprites[i].mode<<1);
}

static void redraw_zero()
{
    int x;
    struct Bitmap *bm;
    int dx, dy;
    int w, h;
    int i, j;

    if (b2c->sprites[0].bitmap == (struct BitmapSequence *)NULL)
        DisplayGraphics_fill_screen(b2c->main_module.m_gfx, b2c->paper);
    else
    {
        DisplayGraphics_set_draw_mode(b2c->main_module.m_gfx, DM_PUT);
        x = BitmapSequence_get_size(b2c->sprites[0].bitmap);
        bm = BitmapSequence_get_bitmap(
                   b2c->sprites[0].bitmap, 
                   b2c->sprites[0].z % x);
        dx = b2c->sprites[0].rect.x;
        dy = b2c->sprites[0].rect.y;
        while (dx>0) dx-=bm->w;
        while (dy>0) dy-=bm->h;
        w = bm->w;
        h = bm->h;
        for(i=dx; i<160; i+=w)
        {
            for(j=dy; j<100; j+=h)
            {
                DisplayGraphics_draw_bitmap(
                        b2c->main_module.m_gfx,
                        bm,
                        i,
                        j,
                        b2c->sprites[0].mode<<1);
            }
        }
    }
}

void _redraw(int n)
{
    int i;

    if (cyberpeek_timer) _cyberpeek();
    if (n==0) redraw_zero();
    else if (n>0) redraw_one(n);
    else if (n==-1)
    {
       redraw_zero();
       for(i=1; i<_n_sprites; i++)
       {
          redraw_one(i);
       }
       if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);
    }
    else if (n==-2)
    {
       if (!_background_) DisplayGraphics_show(b2c->main_module.m_gfx);
    }
}

int _collision(int a, int b)
{
        struct rect_t tmprect;
		if (b2c->sprites[a].bitmap && b2c->sprites[b].bitmap)
			return rect_and(&tmprect, &b2c->sprites[a].rect, &b2c->sprites[b].rect);
		else
			return 0;
}
