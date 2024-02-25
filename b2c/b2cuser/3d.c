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
static int load_cy3d_dl = 1;

void init_3d() {
	int i;

	b2c->rooms=calloc(_n_rooms, sizeof(struct _room));
	b2c->curr_room = 0;
	for(i=0; i<_n_rooms; i++)
	{
		b2c->rooms[i].sprites=calloc(_n_3dsprites, sizeof(struct _3dsprite));
	}
}

static void destroy_walls(struct _wall *walls)
{
	struct _wall *next;
	struct _wall *tmp;

	if (walls== (struct _wall *) NULL) return;
	for(next=walls; next; next=tmp)
	{
		tmp = next->next;
		if (next->bottom_tex) free(next->bottom_tex);
		if (next->top_tex) free(next->top_tex);
		free(next);
	}
}

void destroy_3d() {
	int i;

	for(i=0; i<_n_rooms; i++)
	{
		destroy_walls(b2c->rooms[i].walls);
		free(b2c->rooms[i].sprites);
	}
}

void _3d_room(int n) {
	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}
	b2c->curr_room=n;
}

void _3d_wall(int x0, int y0, int x1, int y1, char *tex) {
	int i = b2c->curr_room;
	struct _wall *next;
	char *dot;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}
	if (b2c->rooms[i].walls == (struct _wall *) NULL)
		next = NULL;
	else
		next = b2c->rooms[i].walls;
	b2c->rooms[i].walls = calloc(1, sizeof(struct _wall));
	b2c->rooms[i].walls->next = next;
	b2c->rooms[i].walls->p0.p_x = x0;
	b2c->rooms[i].walls->p0.p_y = y0;
	b2c->rooms[i].walls->p1.p_x = x1;
	b2c->rooms[i].walls->p1.p_y = y1;

	strcpy(b2c->buf, tex);
	strcat(b2c->buf, "1");
	if (!is_in_archive(b2c->buf))
	{
		b2c->rooms[i].walls->bottom_tex = cy3d_load(tex);
		b2c->rooms[i].walls->top_tex = NULL;
	}
	else /* 2 separate spr files */
	{
		strcpy(b2c->buf, tex);
		strcat(b2c->buf, "1");
		b2c->rooms[i].walls->top_tex = cy3d_load(b2c->buf);
		strcpy(b2c->buf, tex);
		strcat(b2c->buf, "2");
		b2c->rooms[i].walls->bottom_tex = cy3d_load(b2c->buf);
	}
	//b2c->rooms[i].walls->m = ((y1-y0)*256)/(x1-x0);
	//b = y0-(m*256)*x0;
	//b2c->rooms[i].walls->b = b;
}

void _3d_redraw() {
	int flip = 0;
	int i = b2c->curr_room;
	int j;
	char *display = DisplayGraphics_get_page_ptr(b2c->main_module.m_gfx, 0);
	struct _wall *w = b2c->rooms[i].walls;
	point_t pt1;
	point_t pt2;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}
	for(j=0; j<160; j++) b2c->z_buffer[j] = 0x7fff;

	cy3d_draw_sky( display, CLR_WHITE);
	
	for(w=b2c->rooms[i].walls; w; w=w->next)
	{
		if (w->bottom_tex)
		{
			flip = 1;
			pt1 = cy3d_warp(w->p0, b2c->rooms[i].sprites[0].p0, b2c->rooms[i].sprites[0].z);
			pt2 = cy3d_warp(w->p1,  b2c->rooms[i].sprites[0].p0, b2c->rooms[i].sprites[0].z);
			cy3d_draw_wall(display, pt1, pt2, w->bottom_tex, 0, 0, b2c->z_buffer);
		}
	}

	if (flip) cy3d_mirror_buffer(display);

	for(j=0; j<160; j++) b2c->z_buffer[j] = 0x7fff;

	cy3d_draw_sky(display, CLR_LTGRAY);

	for(w=b2c->rooms[i].walls; w; w=w->next)
	{
		if (w->top_tex)
		{
			pt1 = cy3d_warp(w->p0, b2c->rooms[i].sprites[0].p0, b2c->rooms[i].sprites[0].z);
			pt2 = cy3d_warp(w->p1, b2c->rooms[i].sprites[0].p0, b2c->rooms[i].sprites[0].z);
			cy3d_draw_wall(display, pt1, pt2, w->top_tex, 0, 0, b2c->z_buffer);
		}
	}
	for(j=1; j<_n_3dsprites; j++)
	{
		if (b2c->rooms[i].sprites[j].tex)
		{
			pt1 = cy3d_warp(b2c->rooms[i].sprites[j].p0, b2c->rooms[i].sprites[0].p0, b2c->rooms[i].sprites[0].z);
			cy3d_draw_sprite(display, pt1, b2c->rooms[i].sprites[j].tex, b2c->rooms[i].sprites[j].z, b2c->z_buffer);
		}
	}
    if (_show_)DisplayGraphics_show(b2c->main_module.m_gfx);
}

void _3d_move(int n, int x, int y, int z)
{
	int i = b2c->curr_room;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}
	b2c->rooms[i].sprites[n].p0.p_x = x;
	b2c->rooms[i].sprites[n].p0.p_y = y;
	b2c->rooms[i].sprites[n].z = z;
}

void _3d_rmove(int n, int dist, int direction, int z)
{
	int i = b2c->curr_room;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}
	b2c->rooms[i].sprites[n].p0 = cy3d_move(b2c->rooms[i].sprites[n].p0, dist, direction);
	if (n) b2c->rooms[i].sprites[n].z = z;
	else b2c->rooms[i].sprites[n].z = direction;
}

void _3d_get(int n, int *x, int *y, int *z)
{
	int i = b2c->curr_room;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}
	*x = b2c->rooms[i].sprites[n].p0.p_x;
	*y = b2c->rooms[i].sprites[n].p0.p_y;
	*z = b2c->rooms[i].sprites[n].z;
}

void _3d_sprite(int n, char *filename)
{
	int i = b2c->curr_room;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}

	b2c->rooms[i].sprites[n].tex = cy3d_load(filename);
}

int _3d_collision(int a, int b, int dist)
{
	long dist2 = dist * dist;
	long dist0;
	int i = b2c->curr_room;

	if (load_cy3d_dl)
	{
		load_cy3d_dl = 0;
		_load("cy3d.dl");
	}

	dist0 = cy3d_distance2(
		b2c->rooms[i].sprites[a].p0,
		b2c->rooms[i].sprites[b].p0);

	return (dist0 < dist2) ;
}