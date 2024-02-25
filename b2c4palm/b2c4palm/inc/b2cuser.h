#ifndef _B2CUSER_H_
#define _B2CUSER_H_

#define __native

#include <PalmOs.h>
#include <unix_stdio.h>
#include <unix_stdarg.h>
#include <unix_string.h>

#define _ourMinVersion sysMakeROMVersion( 3, 0, 0, sysROMStageRelease, 0 )
#define _Version3_5 sysMakeROMVersion( 3, 5, 0, sysROMStageRelease, 0 )

//
// the keyboard mapping
//
#define KEY_APPS 0x108
#define KEY_PWR 0x208
#define KEY_PWR2 0x11E
#define KEY_PWR3 0x113
#define KEY_PWR4 0x120
#define KEY_ABCDE 0x110
#define KEY_12345 0x111
#define KEY_MENU 0x105
#define KEY_CALC 0x10B
#define KEY_FIND 0x10A
#define KEY_LEFT 0x204
#define KEY_RIGHT 0x205
#define KEY_UP 0x00B
#define KEY_DOWN 0x00C
#define KEY_ENTER 0x206
#define KEY_SELECT 0x207
#define KEY_HELP 0x10E
#define KEY_BS 0x08
#define MAX_MENU 20
#define B2C_WHITE (-1)
#define B2C_BLACK (-2)

//
// the b2c global data structure
//
typedef struct b2c_t {
	int penx;
	int peny;
	int key;
	int ink;
	int paper;
	char buf[256];
	EventType* event;
	Boolean (*handleEvent)(EventPtr eventP);
	WinHandle screen;
	WinHandle win[2];
	int currwin;
	RectangleType screenRect;
	int show;
	char *menu_list[MAX_MENU];
} _B2C;

//
// the global b2c object
//
extern _B2C *_b2c;

//
// b2cuser.cpp
//
Boolean _B2CHandleEvent_FullyConforming( EventPtr eventP );
Boolean _B2CHandleEvent_PartiallyConforming( EventPtr eventP );
Boolean _B2CHandleEvent_NonConforming( EventPtr eventP );
void _StopApplication( void );
UInt16 _StartApplication( void );
void *_GetObjectPtr( UInt16 objectID, UInt16 formID );
void _SwitchDisplayMode( void );
Err _RomVersionCompatible( UInt32 requiredVersion );
void _B2CMain( void );

//
// graphics.cpp
//
void _printxy(int x, int y, Char *formatStr, ...);
void _stringxy(int x, int y, char *s);
void _show();
void _line(int x0, int y0, int x1, int y1);
void _point(int x0, int y0);
void _ink(int color);
void _paper(int color);
void _cls();
void _font(char *fontname);
int _stringwidth(char *s);
int _stringheight(char *s);
void _rect(int x0, int y0, int w, int h);
void _rectfill(int x0, int y0, int w, int h);
void _circle(int x, int y, int r);
void _circfill(int x, int y, int r);
void _menu(int x, int y, int *choice, ...);

//
// input.cpp
//
int _key(int n);
int _getkey();
void _inputxy_int(int x, int y, int *d, char *prompt);
void _inputxy_long(int x, int y, long *d, char *prompt);
void _inputxy_char(int x, int y, char *d, char *prompt);
void _inputxy_string(int x, int y, char *s, int len, char *prompt);

//
// sound.cpp
//
void _beep(int freq, int duration, int amplitude);

//
// math.cpp
//
int _rnd(int modval);

//
// string.cpp
//
void _sprint(char *var, char *fmt, ...);
void _mid(char *a, char *b, int start, int len);
void _right(char *a, char *b, int len);
void _tokenize(char *s, char *seps, ...);

//
// compatibility
//
#define atoi StrAToI
#define atol StrAToI
#define SAME(a,b) (StrCompareAscii(a,b)==0)
#define ISAME(a,b) (StrCaselessCompare(a,b)==0)

#endif //_B2CUSER_H_