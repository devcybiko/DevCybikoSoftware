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
#ifndef _B2CUSER_H_
#define _B2CUSER_H_

#include <cywin.h>
#include "fixed.h"

#ifndef NULL
#define NULL 0
#endif

#define _int(a) (xtoi(a))
#define _abs(a) ((a)<0? -(a) : (a))

extern struct module_t *_ptr_main_module;
/* b2cuser */
extern void _init_b2c();
extern void _destroy_b2c();

/* 3d */
extern void _3d_room(int n);
extern void _3d_wall(int x0, int y0, int x1, int y1, char *tex);
extern void _3d_redraw();
extern void _3d_move(int n, int x, int y, int z);
extern void _3d_rmove(int n, int dist, int direction, int z);
extern void _3d_get(int n, int *x, int *y, int *z);
extern int _3d_collision(int a, int b, int dist);
extern void _3d_sprite(int n, char *filename);
extern int _3d_collision(int a, int b, int dist);

/* dialog */
extern int _dialog(char *info, char *text, char *data, int len);

/* fileio */
#define ERROR_FILE_SEEK 52
#define ERROR_FILE_WRITE 53
#define ERROR_FILE_READ 54
#define ERROR_FILE_OPEN 56
#define ERROR_FILE_CREATE 57
#define ERROR_FILE_CLOSE 100
#define ERROR_FILE_NUMBER 101
#define ERROR_FILE_ALREADY_OPEN 102
#define ERROR_FILE_ALREADY_CLOSED 103
#define ERROR_FILE_UNOPENED 104

#define ALIGN_LEFT 0
#define ALIGN_RIGHT 1
#define ALIGN_CENTER 2

#define WRAP_CHAR 0
#define WRAP_WORD 1

extern void _close(int filenum);
extern void _open(int mode, char *filename, int filenum);
extern int _eof(int filenumber);
extern void _put(int filenum, long filepos, void *data, int size);
extern void _get(int filenum, long filepos, void *data, int size);
extern void _printno(int filenum, char *fmt, ...);
extern void _findfile(char *pattern);
extern int _nextfile(char *s);
extern int _filelist(
	char* title,				//(in)title of the form
	char* filter,				//(in)filter for file list
	char* filename,				//(out)filename selected
	struct cWinApp* ptr_win_app	//(in)application pointer(main_module.m_process)
);


/* graphics */
extern void _printxy(int x, int y, char *fmt, ...);
extern void _line(int x0, int y0, int x1, int y1);
extern void _point(int x, int y);
extern void _ink(int ink);
extern void _paper(int paper);
extern void _font(char *s);
extern void _cls();
extern void _rect(int x0, int y0, int x1, int y1);
extern void _rectfill(int x0, int y0, int x1, int y1);
extern void _page(int page);
extern void _pagecopy(int from, int to, int x, int y, int w, int h);
extern int _stringwidth(char *s);
extern int _stringheight(char *s);
extern int _wrap(int x, int y, int w, int h, int align, int wraptype, char *s);
extern void _circle(int x, int y, int r);
extern void _circfill(int x, int y, int r);

/* input */
extern void _input_fixed(fixed *d, char *prompt);
extern void _input_int(int *d, char *prompt);
extern void _input_char(char *d, char *prompt);
extern void _input_string(char *s, int len, char *prompt);
extern void _input_long(long *d, char *prompt);
extern void _inputxy_fixed(int x, int y, fixed *d, char *prompt);
extern void _inputxy_int(int x, int y, int *d, char *prompt);
extern void _inputxy_char(int x, int y, char *d, char *prompt);
extern void _inputxy_string(int x, int y, char *s, int len, char *prompt);
extern void _inputxy_long(int x, int y, long *d, char *prompt);
extern int _key(int which);
extern void _keyclick(int state);
extern int _getkey();
extern int _char(int which);
extern int _getchar();

/* load */
extern void _load(char *filename);

/* menu */
extern void _menu(int x, int y, int *var, ...);

/* msg */
extern void onmessage(long cyid, int msgno, char *buffer);
extern void _msg_send(long cyid, int msgno, char *appname, char *buffer);
extern long _user_menu(char *caption, long *skip);
extern long _tocyid(char *name);
extern char *_touser(long cyid);

/* music */
extern void _music(int opn, int channel, char *filename);
extern void _vibrate(int x);
extern void _beep(int sound);

/* print */
extern void _print(char *fmt, ...);

/* score */
extern void _show_high_scores(void);
extern void _update_high_scores(long scores);

/* sprite */
extern void _sprite(int n, char *filename);
extern void _move(int n, int x, int y, int z, int mode);
extern void _redraw(int n);
extern int _collision(int a, int b);
extern void _sprite_get(int n, int *x, int *y, int *z, int *mode, int *w, int *h);

/* string */
extern void _mid(char *a, char *b, int start, int len);
extern void _right(char *a, char *b, int len);
extern void _tokenize(char *s, char *seps, ...);
extern void _sprint(char *var, char *fmt, ...);
extern void _sprite_get(int n, int *x, int *y, int *z, int *mode, int *w, int *h);

/* other */
extern void _wait(int tsecs);
extern void _escape(int how);
extern int _rnd(int x);
extern void _exit_basic(char *s);

/***
 *** Things you should never touch
 *** But I know - you will
 ***/
#define LINE_LENGTH 40
#define MAX_PIXELS_WIDTH 160
#define MAX_PIXELS_HEIGHT 100
#define MAX_FILES 10
#define MAX_LINES 25
#define MAX_SPRITES 32
#define MAX_CYBERPEEK 60
#define MAX_MSGBUF 1024

struct _b2c_sprite {
	struct BitmapSequence *bitmap;
	struct rect_t rect;
	int z;
	int mode;
	int collision;
};

struct _wall {
	raster_t *top_tex;
	raster_t *bottom_tex;
	point_t p0;
	point_t p1;
	struct _wall *next;
	fixed_t m, b;
};

struct _3dsprite {
	raster_t *tex;
	point_t p0;
	int z;
};

struct _room {
	struct _wall *walls;
	struct _3dsprite *sprites;
};

struct _b2cuser {
    struct module_t main_module;
    struct DirectKeyboard* dk;
    void *files[MAX_FILES];
	char *msgbuf;
    int file_modes[MAX_FILES];
    int x, y;
    int ink, paper;
    int nlines;
    int ht;
    int currline;
    int cursor;
    int colors[4];
	int font_in_memory;
    struct Font *font;
    char **lines;
    char buf[256];
    struct _b2c_sprite *sprites;
	struct MSequence *channel[2];
	struct score_t *high_scores;
	struct _room *rooms;
	int curr_room;
	int z_buffer[160];
	struct FileFind searcher;
	struct File file_info;
	int find_in_progress;

    int font_changed;
    int background_playing;
    int keyclicks;
};

/***
 *** This is the pointer to 
 *** all the B2C data
 *** 
 *** Enter at your own risk!
 ***/
extern struct _b2cuser *b2c;

#endif
