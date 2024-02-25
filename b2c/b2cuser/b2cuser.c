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
#include "CyWin.h"
#include "inc/b2cuser.h"
//#include "../Dongle/dongle_b.c"

static void _redisp();
static void init_high_scores( void );
static void destroy_high_scores( void );
static void init_graphics();
static void destroy_graphics();
static void init_sprites();
static void destroy_sprites();
static void init_print();
static void destroy_print();
static void init_input();
static void destroy_input();
static void init_music();
static void destroy_music();
static void init_fileio();
static void destroy_fileio();
static void init_menu();
static void destroy_menu();
static void init_3d();
static void destroy_3d();
static void empty_queue();

#define SAME(a,b) (strcmp(a,b)==0)

extern int _c_coords;
extern int _n_sprites;
extern int _n_rooms;
extern int _n_3dsprites;
extern int _show_;
extern int _escape_;
extern int _help_;
extern int _multitask_;
extern int error;

struct module_t *_ptr_main_module;

enum {
    MODE_READ,
    MODE_WRITE,
    MODE_APPEND,
	MODE_ARCHIVE
};

enum {
	MUSIC_LOAD,
	MUSIC_PLAY,
	MUSIC_STOP
};

static char uppercase[] = {
/*32*/ ' ','!','"','#','$','%','&','"','(',')','*','+','<','_','>','?',
/*48*/ ')','!','@','#','$','%','^','&','*','(',':',':','<','+','>','?',
/*64*/ '@','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
/*80*/ 'p','q','r','s','t','u','v','w','x','y','z','{','|','}','^','_',
/*96*/ '~','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
/*112*/'P','Q','R','S','T','U','V','W','X','Y','Z','{','|','}','~','~'
};

static char controlcase[] = {
/*32*/ ' ','!','"','#','$','%','&','"','[',']','*','+','<','_','>','?',
/*48*/ ')','@','}','@','$','3','%','*','+','8','-',':','<','+','>','?',
/*64*/ ' ','@','}','@','$','3','%','*','+','8','-','_','=','>','<','9',
/*80*/ '0','1','4','&','5','7','{','2','#','6','"','{',':','}','?','_',
/*64*/ ' ','@','}','@','$','3','%','*','+','8','-','_','=','>','<','9',
/*80*/ '0','1','4','&','5','7','{','2','#','6','"','{',':','}','?','_',
};

/** the major structure **/
struct _b2cuser *b2c;

//__inline void DBG(char *s) {}
void DBG(char *s) {}
//#define DBG TRACE

static void _basic_error(char *s);
int _basic_ask_exit(char *s);
static void _cyberpeek();

static time_t cyberpeek_timer;
static int _background_=0;

//struct _b2cuser _b2cdata;

static char appname[16] = {0x17,0x98,0x70,0x9e,0x2f,0xcb,0x4e,0xca,0x9d,0x3a,0xac,0xca,0xe7,0x7e,0xbf,0x73};

/**** UTILITIES ****/
static int is_in_archive(char *fname)
{
	int i;
	int n;
	char *s;
	struct Archive *archive = b2c->main_module.m_process->module->archive;
	n = Archive_count_entries(archive);
	for(i=0; i<n; i++)
	{
		s = Archive_get_name(archive, i);
		if (strcmp(fname, s)==0) return +1;
	}
	return 0;
}

void _init_b2c()
{
    b2c = (struct _b2cuser *) calloc(1, sizeof(struct _b2cuser));

    init_module(&b2c->main_module);
    _ptr_main_module = &b2c->main_module;

    // seed the random number generator
    srand((int)clock());
	cyberpeek_timer = time();

	init_high_scores();
	init_graphics();
	init_sprites();
	init_print();
	init_input();
	init_music();
	init_fileio();
	init_menu();
	init_3d();
}

void _destroy_b2c()
{
	empty_queue();
	destroy_3d();
	destroy_menu();
	destroy_fileio();
	destroy_music();
	destroy_input();
	destroy_print();
	destroy_sprites();
	destroy_graphics();
	destroy_high_scores();
    free(b2c);
}

static void _font_update()
{
    b2c->ht = Font_get_char_height(b2c->font);
    b2c->nlines = MAX_PIXELS_HEIGHT / b2c->ht;
    b2c->font_changed = 0;
}

static void _error_noise()
{
    stop_tone();
    AppGeneric_pause(b2c->main_module.m_process, 50);
    play_tone(0);
    AppGeneric_pause(b2c->main_module.m_process, 125);
    stop_tone();
}

static void _cyberpeek()
{
	cyberpeek_timer = 0;
	return;
//	if (cyberpeek_timer && (time() - cyberpeek_timer > MAX_CYBERPEEK))
//	{
//		cyberpeek_timer = 0;
//		pw_check(&b2c->main_module, appname, 0);
//	}
}

void _wait(int tsecs)
{
	long milliseconds = tsecs*100;
	long then = clock();
	long now = clock();

	while(now-then < milliseconds)
	{
		_key(0);
		now = clock();
	}
    return;
}

void _escape(int how)  // how is ignored. sorry
{
    _key(KEY_ESC);
}

static void empty_queue()
{
	struct Message* message;
	message = cWinApp_get_message(b2c->main_module.m_process, 1, 1, MSG_USER+1024);
	while(message)
	{
		cWinApp_defproc(b2c->main_module.m_process, message);
		Message_delete(message);
		message = cWinApp_get_message(b2c->main_module.m_process, 1, 1, MSG_USER+1024);
	}
}

void _exit_basic(char *s)
{
    play_tone(-1);
    set_clicks_enabled(1);
    if (s) _basic_error(s);
    _destroy_b2c();
    exit(0);
}

static void _basic_error(char *s)
{
   struct cDialog exit_dialog;
   char *disp;

   play_tone(-1);
   disp = (char* ) malloc( TGraph_get_bytes_total( b2c->main_module.m_gfx ) );
   memcpy(disp,
    DisplayGraphics_get_page_ptr(b2c->main_module.m_gfx, 0),
    TGraph_get_bytes_total(b2c->main_module.m_gfx));
   cDialog_ctor( &exit_dialog, "ERROR", s, mbOk, 0, b2c->main_module.m_process );
   cDialog_ShowModal( &exit_dialog );
   cDialog_dtor( &exit_dialog, LEAVE_MEMORY );
   TGraph_put_background(b2c->main_module.m_gfx, disp );
   free(disp);
}

static int _basic_ask_exit(char *s)
{
   struct cDialog exit_dialog;
   int rc;
   char *disp;

   play_tone(-1);
   disp = (char* ) malloc( TGraph_get_bytes_total( b2c->main_module.m_gfx ) );
   memcpy(disp,
    DisplayGraphics_get_page_ptr(b2c->main_module.m_gfx, 0),
    TGraph_get_bytes_total(b2c->main_module.m_gfx));
   cDialog_ctor( &exit_dialog, "EXIT", s, mbYes | mbNo, 0, b2c->main_module.m_process );
   rc = ( cDialog_ShowModal( &exit_dialog ) == mrYes );
   cDialog_dtor( &exit_dialog, LEAVE_MEMORY );
   TGraph_put_background(b2c->main_module.m_gfx, disp );
   free(disp);
   return rc;
}

int _rnd(int x)
{
   return (int)random(x+1);
}

/*#include "fixed.c"*/
#include "fileio.c"
#include "graphics.c"
#include "input.c"
#include "music.c"
#include "print.c"
#include "score.c"
#include "sprite.c"
#include "string.c"
#include "msg.c"
#include "menu.c"
#include "dialog.c"
#include "3d.c"
#include "load.c"
#include "FileListForm.c"
