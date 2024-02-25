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
%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "b2c.h"
#include "bterm.h"
#include "bprogram.h"
#include "bstatement.h"
#include "bdim.h"
#include "bop.h"
#include "bstatement.h"
#include "bfor.h"
#include "bif.h"
#include "bthen.h"
#include "belse.h"
#include "bexit.h"
#include "belseif.h"
#include "bprint.h"
#include "blist.h"
#include "bwhile.h"
#include "bfunction.h"
#include "bparam.h"
#include "bfunccall.h"
#include "binput.h"
#include "binputxy.h"
#include "bprintxy.h"
#include "bmath.h"
#include "bopen.h"
#include "bput.h"
#include "bexitfunction.h"
#include "bprintno.h"
#include "bmid.h"
#include "binline.h"
#include "boutline.h"
#include "blabel.h"
#include "bgoto.h"
#include "btype.h"
#include "bsprite.h"
#include "bredraw.h"
#include "bmusic.h"
#include "bongoto.h"
#include "bongosub.h"
#include "bscore.h"
#include "bmenu.h"
#include "bmenuxy.h"
#include "bexitprogram.h"
#include "bchar.h"
#include "bsprint.h"
#include "btokenize.h"
#include "bcommand.h"
#include "bsprite_get.h"
#include "bget.h"

//#define DBG0 printf
#define YYERROR_VERBOSE 6

char yacctext[1024];
char tmp_filename[256];
int c_strings=0;
int c_coords=0;
int n_sprites=32;
int n_3dsprites=8;
int n_rooms=8;
int _show_=1;
int _escape_ = 1;
int _help_ = 1;
int _multitask_=1;
int _onmessage_defined_ = 0;
int _show_main_ = 1;

extern int yylineno;
extern int yylex();
extern void yyerror(char *s);

Node *curr_func=0;
Node *in_function=0;

Node *body_stack[256];
int body_stack_n=0;

#define YYDEBUG 1

char *fix_string(char *s);
char *uppercase(char *s);
char *lowercase(char *s);

Node *do_bterm(
     char *name,
     int datatype,
     int literal,
	 int dimension);
Node *do_bstatement(
  Node *expr,
  int lineno);
Node *do_bdim(
	char *var,
	int datatype,
	Node *expr,
	char *typename);
Node *do_bexpr(Bterm *term);
Bexpr *do_bop(
     Bexpr *left,
     int op,
     Bexpr *right);
Node *do_bfor(
     char *name,
     Node *from,
     Node *to,
     Node *step);
Node *do_bwhile(Node *expr);
Node *do_bfunction(
     char *name,
     Node *parameters,
     int datatype);
Node *do_bif(Node *exp);
Node *do_bif2(Node *exp, Node *stmp);
Node *do_belseif(Node *exp);
Node *do_belse();
Node *do_bexitfor();
Node *do_bexitwhile();
Node *do_bexitfunction();
void push(Node *node);
Node *pop(int type);
Node *pop2(int type1, int type2);
Node *pop3(
     int type1,
     int type2,
     int type3);
Node *do_bprint(Node *list);
Node *do_bsprint(Node *var, Node *list);
Node *do_bprintxy(
     Bexpr *x,
     Bexpr *y,
     Node *list);
Node *do_list(
     Node *expr1,
     Node *expr2);
Node *do_paramlist(
     Node *expr1,
     Node *expr2);
Node *do_param(
     char *name,
     int datatype,
     int dimension,
     int passed_by,
     Bexpr *initial_value);
Bexpr *do_funccall(
     char *name,
     Blist *paramlist);
Node *do_funclist(
     Node *expr1,
     Node *expr2);
Node *do_input(
     Bexpr *prompt,
     Bterm *term);
Node *do_inputxy(
	 Bexpr *x,
	 Bexpr *y,
     Bexpr *prompt,
     Bterm *term);
Node *do_char(Bexpr *exp);
Node *do_math(
     char *name,
     Bexpr *exp,
	 int type);
Node *do_math2(
     char *name,
     Bexpr *exp1,
     Bexpr *exp2,
	 int type);
Node *do_open(
     Bexpr *exp1, /* filename */
     int mode,
     Bexpr *exp2); /* filenumber */
Node *do_put(
     Bexpr *exp1, /* filenumber */
     Bexpr *exp2, /* filepos - optional */
     Bterm *name); /* variable name */
Node *do_bprintno(
     Bexpr *fileno,
     Node *list);
Node *do_mid(
     Bterm *dest,
     Bexpr *src,
     Bexpr *start,
     Bexpr *len);
Node *do_binline(
     char *code);
Node *do_boutline(
     char *code);
Node *do_bgoto(char *name);
Node *do_blabel(char *label);
Node *do_btype(char *name);
Node *do_btype2(char *varname, Node *subscript, int datatype, char *typename);
Node *do_bsprite(Bexpr *n, Bexpr *name);
Node *do_bredraw(Bexpr *n);
Node *do_bmusic(int opn, int channel, Bexpr *bexp);
Node *do_bongoto(Bexpr *exp, Node *list);
Node *do_bongosub(Bexpr *exp, Node *list);
Node *do_varterm(char *name);
Node *do_bscore(Bexpr *exp);
Node *do_bmenu(char *varname, Node *list);
Node *do_bmenuxy(Bexpr *x, Bexpr *y, char *varname, Node *list);
void update_lineno(char *filename, char *lineno);
Node *do_bexitprogram();
Node *do_variable(Bterm *bterm, Node *subscript);
Node *do_btokenize(Node *var, Node *tokens, Node *list);
Node *do_bcommand(char *command_name, ...);
Bdim *find_member_name(Btype *btype, char *name);
Node *do_bsprite_get(Bexpr *n, Node *x, Node *y, Node *z, Node *mode, Node *w, Node *h);
Node *do_get(exp1,exp2, name);

#define null_term bterm_new("NULL")
#define zero_term bterm_new("0")

%}

/* BISON Declarations */

%token  LITERAL_CHAR
%token	LITERAL_INT
%token	LITERAL_LONG
%token	LITERAL_STRING
%token	LITERAL_DOUBLE
%token  VAR

%token	DIM
%token	CHAR
%token	INT
%token	LONG
%token	DOUBLE
%token	AS
%token  COMMENT
%token	FOR
%token	TO
%token	STEP
%token	NEXT
%token	EXIT
%token	IF
%token	THEN
%token	END
%token	ELSE
%token	ELSEIF
%token	PRINT
%token  SPRINT
%token	WHILE
%token	WEND
%token	FUNCTION
%token	SUB
%token  CALL
%token  WAIT
%token  INPUT
%token	INPUTXY
%token	LINE
%token  POINT
%token	INK
%token	PAPER
%token	CLS
%token  PRINTXY
%token  SIN
%token  SINH
%token  ASIN
%token  ASINH
%token  COS
%token  COSH
%token  ACOS
%token  ACOSH
%token  TAN
%token  ACTAN
%token	ACTANH
%token  ATAN
%token  ATANH
%token  SQRT
%token  EXP
%token  LOG
%token  LOG10
%token  LOG2
%token  POW2
%token  RND
%token	INV
%token  POW
%token  SQR_POW
%token  KEY
%token  BEOF
%token  OPEN
%token  READ
%token  WRITE
%token  APPEND
%token  CLOSE
%token  PUT
%token  GET
%token	AND
%token	OR
%token	NEQ
%token	BEEP
%token	BY_REF
%token	BY_VAL
%token	LE
%token	GE
%token	MID
%token	RIGHT
%token	INLINE
%token	OUTLINE
%token	FONT
%token	GOTO
%token	TYPE
%token	SPRITE
%token	MOVE
%token	REDRAW
%token	COLLISION
%token	MUSIC
%token	FOREGROUND
%token	BACKGROUND
%token	STOP
%token	PLAY
%token	FLIP_X
%token	FLIP_Y
%token	VIBRATE
%token	OPTION
%token	C_STRINGS
%token	CYBASIC_STRINGS
%token	ON
%token	GOSUB
%token	ALL
%token	SHOW
%token	C_COORDS
%token	CYBASIC_COORDS
%token	SPRITES
%token	D3SPRITES
%token	D3ROOMS
%token	WHITE
%token	LTGREY
%token	DKGREY
%token	BLACK
%token	SCORE
%token	MENU
%token	MENUXY
%token	ENDIF
%token	FILENAME
%token	KEYCLICK
%token	OFF
%token	PROGRAM
%token	NOT
%token	MOD
%token  ABS
%token	DABS
%token  INT
%token	ESCAPE
%token	HELP
%token	MULTITASK
%token	GETCHAR
%token	GETKEY
%token  SENDMESSAGE
%token	TOKENIZE
%token	USERMENU
%token  TOCYID
%token  TOUSER
%token	DIALOG
%token	D3ROOM
%token	D3SPRITE
%token	D3WALL
%token	D3COLLISION
%token	D3MOVE
%token	D3REDRAW
%token	D3RMOVE
%token	D3GET
%token  CAMERA
%token  B2C_TRUE
%token  B2C_FALSE
%token  ERROR
%token  SPRITE_GET
%token	FINDFILE
%token	REMOVE
%token	RENAME
%token	EXISTS
%token	NEXTFILE
%token	FILELIST
%token	MAIN
%token	RECT
%token	RECTFILL
%token	PAGE
%token	PAGECOPY
%token	LOAD
%token	LEN
%token	STRINGWIDTH
%token	STRINGHEIGHT
%token	WRAP
%token	LEFT
%token	CENTER
%token	WORD
%token	ARCHIVE
%token	CIRCLE
%token	CIRCFILL

%token	'\n'
%left	'-' '+'
%left	'*' '/' MOD
%token	'(' ')' '[' ']'
%left AND OR
%left '='
%left	NEG     /* negation--unary minus */
%left	NOT		/* boolean not */
%union {
  char *string;
  int num;
  int mode;
  Bexpr *expr;
  Node *node;
  Bterm *term;
}

/* Grammar follows */
%%
input:    /* empty string */
        | input statement { if ($<node>2) body_stack[body_stack_n]->addchild(body_stack[body_stack_n], $<node>2); }
	    | input comment {$<node>$=NULL;}
	    | input options comment {$<node>$=NULL;}
		| input filename lineno comment { update_lineno($<string>2, $<string>3); }
;
statement: 
/*	| DIM varname comment				 { $<node>$ = do_bdim($<string>2, DATATYPE_INT, 0, NULL); }*/
	| DIM varname AS datatype comment		 { $<node>$ = do_bdim($<string>2, $<num>4, 0, NULL); }
	| DIM varname AS varname comment		 { $<node>$ = do_bdim($<string>2, DATATYPE_TYPE, 0, $<string>4); }
	| DIM varname subscript AS datatype comment	 { $<node>$ = do_bdim($<string>2, $<num>5, (Node *) $<expr>3, NULL); }
	| DIM varname subscript AS varname comment	 { $<node>$ = do_bdim($<string>2, DATATYPE_TYPE, (Node *) $<expr>3, $<string>5); }
	| CALL sub_call comment				 { $<node>$ = do_bstatement($<node>2, yylineno); }
	| sub_call	comment				 { $<node>$ = do_bstatement($<node>1, yylineno); }
	| assignment	comment				 { $<node>$ = do_bstatement($<node>1, yylineno); }
	| FOR varname '=' exp TO exp comment		 { $<node>$ = do_bfor($<string>2, $<node>4, $<node>6, 0); push($<node>$); $<node>$=0;}
	| FOR varname '=' exp TO exp STEP exp comment	 { $<node>$ = do_bfor($<string>2, $<node>4, $<node>6, $<node>8); push($<node>$); $<node>$=0;}
	| NEXT comment					 { $<node>$ = pop(TYPE_FOR); }
	| EXIT FOR comment				 { $<node>$ = do_bexitfor(); }
    | IF exp THEN comment				 { $<node>$ = do_bif((Node *)$<expr>2); $<node>$=0;}
    | IF exp THEN statement				 { $<node>$ = do_bif2((Node *)$<expr>2, (Node *)$<expr>4); $<node>$ = do_bstatement($<node>$, yylineno);}
	| ELSE comment					 { pop2(TYPE_THEN, TYPE_ELSEIF); do_belse(); $<node>$=0;}
	| ELSEIF exp THEN comment			 { pop2(TYPE_THEN, TYPE_ELSEIF); $<node>$ = do_belseif((Node *)$<expr>2); $<node>$=0;}
	| END IF comment				 { pop3(TYPE_THEN, TYPE_ELSE, TYPE_ELSEIF); $<node>$ = pop(TYPE_IF);}
	| ENDIF comment				 { pop3(TYPE_THEN, TYPE_ELSE, TYPE_ELSEIF); $<node>$ = pop(TYPE_IF);}
	| TOKENIZE exp ',' exp ',' list comment				 { $<node>$ = do_btokenize($<node>2, $<node>4, $<node>6); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SPRINT scalar ',' list comment				 { $<node>$ = do_bsprint($<node>2, $<node>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PRINT list comment				 { $<node>$ = do_bprint($<node>2); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PRINT comment				 { $<node>$ = do_bprint(NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PRINT '#' term ',' list comment		 { $<node>$ = do_bprintno($<expr>3, $<node>5); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PRINTXY exp ',' exp ',' list comment		 { $<node>$ = do_bprintxy($<expr>2, $<expr>4, $<node>6); $<node>$ = do_bstatement($<node>$, yylineno); }
	| WHILE exp comment				 { $<node>$ = do_bwhile($<node>2); push($<node>$); $<node>$=0; }
	| WEND comment					 { $<node>$ = pop(TYPE_WHILE); }
	| EXIT WHILE comment				 { $<node>$ = do_bexitwhile(); }
/*	| FUNCTION varname '(' paramlist ')' comment	 { $<node>$ = do_bfunction($<string>2, $<node>4, DATATYPE_INT); push($<node>$); in_function = $<node>$; $<node>$=0; }*/
	| FUNCTION varname '(' paramlist ')' AS datatype comment { $<node>$ = do_bfunction($<string>2, $<node>4, $<num>7); push($<node>$); in_function = $<node>$; $<node>$=0; }
/*	| FUNCTION varname comment			 { $<node>$ = do_bfunction($<string>2, NULL, DATATYPE_INT); push($<node>$); in_function = $<node>$; $<node>$=0; }*/
	| FUNCTION varname AS datatype comment		 { $<node>$ = do_bfunction($<string>2, NULL, $<num>4); push($<node>$); in_function = $<node>$; $<node>$=0; }
	| EXIT FUNCTION comment				 { $<node>$ = do_bexitfunction(); }
	| END FUNCTION comment				 { $<node>$ = pop(TYPE_FUNCTION); in_function = NULL; }
	| SUB varname '(' paramlist ')' comment		 { $<node>$ = do_bfunction($<string>2, $<node>4, DATATYPE_VOID); push($<node>$); in_function = $<node>$; $<node>$=0; }
	| SUB varname comment				 { $<node>$ = do_bfunction($<string>2, NULL, DATATYPE_VOID); push($<node>$); in_function = $<node>$; $<node>$=0; }
	| EXIT SUB comment				 { $<node>$ = do_bexitfunction(); }
	| END SUB comment				 { $<node>$ = pop(TYPE_FUNCTION); in_function = NULL; }
	| WAIT exp comment				 { $<node>$ = do_bcommand("_wait", $<node>2, 0); $<node>$ = do_bstatement($<node>$, yylineno); }
	| LINE exp ',' exp ',' exp ',' exp comment	 { $<node>$ = do_bcommand("_line", $<expr>2, $<expr>4, $<expr>6, $<expr>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| POINT exp ',' exp comment			 { $<node>$ = do_bcommand("_point", $<expr>2, $<expr>4, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| CLS comment					 { $<node>$ = do_bcommand("_cls", NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| INK exp comment				 { $<node>$ = do_bcommand("_ink", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| BEEP exp comment				 { $<node>$ = do_bcommand("_beep", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PAPER exp comment				 { $<node>$ = do_bcommand("_paper", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| INPUT scalar comment				 { $<node>$ = do_input(NULL, $<term>2); $<node>$ = do_bstatement($<node>$, yylineno); }
	| INPUT exp ',' scalar comment			 { $<node>$ = do_input($<expr>2, $<term>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| INPUTXY exp ',' exp ',' exp ',' scalar comment { $<node>$ = do_inputxy($<expr>2, $<expr>4, $<expr>6, $<term>8); $<node>$ = do_bstatement($<node>$, yylineno); }
	| INPUTXY exp ',' exp ',' scalar comment { $<node>$ = do_inputxy($<expr>2, $<expr>4, NULL, $<term>6); $<node>$ = do_bstatement($<node>$, yylineno); }
	| OPEN exp FOR mode AS exp comment		 { $<node>$ = do_open($<expr>2, $<mode>4, $<expr>6); $<node>$ = do_bstatement($<node>$, yylineno); }
	| OPEN exp AS exp comment			 { $<node>$ = do_open($<expr>2, MODE_READ, $<expr>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| CLOSE exp comment				 { $<node>$ = do_bcommand("_close", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| CLOSE comment					 { $<node>$ = do_bcommand("_close", NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| FINDFILE exp comment		 { $<node>$ = do_bcommand("_findfile", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| RENAME exp ',' exp comment		 { $<node>$ = do_bcommand("File_rename", $<expr>2, $<expr>4, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| REMOVE exp comment		 { $<node>$ = do_bcommand("File_remove", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PUT exp ',' exp ',' scalar comment		 { $<node>$ = do_put($<expr>2, $<expr>4, $<term>6); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PUT exp ',' ',' scalar comment		 { $<node>$ = do_put($<expr>2, NULL, $<term>5); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PUT exp ',' exp comment			 { $<node>$ = do_put($<expr>2, $<expr>4, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| GET exp ',' exp ',' scalar comment		 { $<node>$ = do_get($<expr>2, $<expr>4, $<term>6); $<node>$ = do_bstatement($<node>$, yylineno); }
	| GET exp ',' ',' scalar comment		 { $<node>$ = do_get($<expr>2, NULL, $<term>5); $<node>$ = do_bstatement($<node>$, yylineno); }
	| GET exp ',' exp comment			 { $<node>$ = do_get($<expr>2, $<expr>4, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MID scalar ',' exp ',' exp comment		 { $<node>$ = do_mid($<term>2, $<expr>4, $<expr>6, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MID scalar ',' exp ',' exp ',' exp comment	 { $<node>$ = do_mid($<term>2, $<expr>4, $<expr>6, $<expr>8); $<node>$ = do_bstatement($<node>$, yylineno); }
	| RIGHT scalar ',' exp ',' exp comment		 { $<node>$ = do_bcommand("_right", $<term>2, $<expr>4, $<expr>6, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| inline 					{ $<node>$= do_binline($<string>1); }
	| outline 					{ $<node>$= do_boutline($<string>1); }
	| FONT exp comment				 { $<node>$ = do_bcommand("_font", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| GOTO varname comment				{ $<node>$ = do_bgoto($<string>2); $<node>$ = do_bstatement($<node>$, yylineno); }
	| varname ':' comment				{ $<node>$ = do_blabel($<string>1); }
	| TYPE varname comment		 { $<node>$ = do_btype($<string>2); push($<node>$); $<node>$=0;}
	| varname AS datatype comment { $<node>$ = do_btype2($<string>1, NULL, $<num>3, NULL); };
	| varname subscript AS datatype comment { $<node>$ = do_btype2($<string>1, $<node>2, $<num>4, NULL); };
	| varname AS varname comment { $<node>$ = do_btype2($<string>1, NULL, DATATYPE_TYPE, $<string>3); };
	| varname subscript AS varname comment { $<node>$ = do_btype2($<string>1, $<node>2, DATATYPE_TYPE, $<string>4); };
	| END TYPE comment		 { $<node>$ = pop(TYPE_TYPE); }
	| D3ROOM exp comment { $<node>$ = do_bcommand("_3d_room", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3SPRITE exp ',' exp comment { $<node>$ = do_bcommand("_3d_sprite", $<expr>2, $<expr>4, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3REDRAW comment { $<node>$ = do_bcommand("_3d_redraw", null_term, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3REDRAW exp comment { $<node>$ = do_bcommand("_3d_redraw", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3WALL  exp ',' exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_3d_wall", $<expr>2, $<expr>4, $<expr>6, $<expr>8, $<expr>10, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3MOVE exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_3d_move", $<expr>2, $<expr>4, $<expr>6, $<expr>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3RMOVE exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_3d_rmove", $<expr>2, $<expr>4, $<expr>6, $<expr>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| D3GET exp ',' varname ',' varname ',' varname comment { $<node>$ = do_bcommand("_3d_get", $<expr>2, $<string>4, $<string>6, $<string>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SPRITE exp comment { $<node>$ = do_bcommand("_sprite", $<expr>2, null_term, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SPRITE exp ',' exp comment { $<node>$ = do_bcommand("_sprite", $<expr>2, $<expr>4, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SPRITE_GET exp ',' scalar ',' scalar ',' scalar ',' scalar ',' scalar ',' scalar comment { $<node>$ = do_bsprite_get($<expr>2, $<node>4, $<node>6, $<node>8, $<node>10, $<node>12, $<node>14); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MOVE exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_move", $<expr>2, $<expr>4, $<expr>6, zero_term, zero_term, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MOVE exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_move", $<expr>2, $<expr>4, $<expr>6, $<expr>8, zero_term, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MOVE exp ',' exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_move", $<expr>2, $<expr>4, $<expr>6, $<expr>8, $<expr>10, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| REDRAW comment { $<node>$ = do_bredraw(NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| REDRAW exp comment { $<node>$ = do_bredraw($<expr>2); $<node>$ = do_bstatement($<node>$, yylineno); }
	| REDRAW ALL comment { $<node>$ = do_bredraw((Bexpr *)-1); $<node>$ = do_bstatement($<node>$, yylineno); }
	| REDRAW SHOW comment { $<node>$ = do_bredraw((Bexpr *)-2); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC BACKGROUND  comment { $<node>$ = do_bmusic(MUSIC_LOAD, MUSIC_BACKGROUND, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC FOREGROUND  comment { $<node>$ = do_bmusic(MUSIC_LOAD, MUSIC_FOREGROUND, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC BACKGROUND ',' exp comment { $<node>$ = do_bmusic(MUSIC_LOAD, MUSIC_BACKGROUND, $<expr>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC FOREGROUND ',' exp comment { $<node>$ = do_bmusic(MUSIC_LOAD, MUSIC_FOREGROUND, $<expr>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC BACKGROUND ',' STOP comment { $<node>$ = do_bmusic(MUSIC_STOP, MUSIC_BACKGROUND, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC FOREGROUND ',' STOP comment { $<node>$ = do_bmusic(MUSIC_STOP, MUSIC_FOREGROUND, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC BACKGROUND ',' PLAY comment { $<node>$ = do_bmusic(MUSIC_PLAY, MUSIC_BACKGROUND, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MUSIC FOREGROUND ',' PLAY comment { $<node>$ = do_bmusic(MUSIC_PLAY, MUSIC_FOREGROUND, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| VIBRATE exp comment { $<node>$ = do_bcommand("_vibrate", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| ON exp GOTO label_list comment		 { $<node>$ = do_bongoto($<expr>2, $<node>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| ON exp GOSUB list comment				 { $<node>$ = do_bongosub($<expr>2, $<node>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SCORE exp comment				 { $<node>$ = do_bscore($<expr>2); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SCORE comment					 { $<node>$ = do_bscore(NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MENU varname ',' list comment				 { $<node>$ = do_bmenu($<string>2, $<node>4); $<node>$ = do_bstatement($<node>$, yylineno); }
	| MENUXY exp ',' exp ',' varname ',' list comment	{ $<node>$ = do_bmenuxy($<expr>2, $<expr>4, $<string>6, $<node>8); $<node>$ = do_bstatement($<node>$, yylineno); }
	| KEYCLICK ON  				 { $<node>$ = do_bcommand("_keyclick", bterm_new("1"), NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| KEYCLICK OFF  				 { $<node>$ = do_bcommand("_keyclick", bterm_new("0"), NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| EXIT PROGRAM			  		 { $<node>$ = do_bexitprogram(); $<node>$ = do_bstatement($<node>$, yylineno); }
	| SENDMESSAGE exp ',' exp ',' exp ',' exp comment	 { $<node>$ = do_bcommand("_msg_send", $<expr>2, $<expr>4, $<expr>6, $<expr>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| RECT exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_rect", $<expr>2, $<expr>4, $<expr>6, $<expr>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| RECTFILL exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_rectfill", $<expr>2, $<expr>4, $<expr>6, $<expr>8, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| CIRCLE exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_circle", $<expr>2, $<expr>4, $<expr>6, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| CIRCFILL exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_circfill", $<expr>2, $<expr>4, $<expr>6, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PAGE exp comment { $<node>$ = do_bcommand("_page", $<expr>2, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| PAGECOPY exp ',' exp ',' exp ',' exp ',' exp ',' exp comment { $<node>$ = do_bcommand("_pagecopy", $<expr>2, $<expr>4, $<expr>6, $<expr>8, $<expr>10, $<expr>12, NULL); $<node>$ = do_bstatement($<node>$, yylineno); }
	| LOAD exp comment {$<node>$ = do_bcommand("_load", $<expr>2, NULL);  $<node>$ = do_bstatement($<node>$, yylineno); }
;
options : OPTION C_STRINGS {c_strings = 1;}
	| OPTION CYBASIC_STRINGS {c_strings = 0;}
	| OPTION C_COORDS {c_coords = 1;}
	| OPTION CYBASIC_COORDS {c_coords = 0;}
	| OPTION SPRITES LITERAL_INT {n_sprites = atoi(yacctext); }
	| OPTION D3SPRITES LITERAL_INT {n_3dsprites = atoi(yacctext); }
	| OPTION D3ROOMS LITERAL_INT {n_rooms = atoi(yacctext); }
	| OPTION SHOW ON {_show_ = 1;}
	| OPTION SHOW OFF {_show_ = 0;}
	| OPTION ESCAPE ON {_escape_ = 1;}
	| OPTION ESCAPE OFF {_escape_ = 0; }
	| OPTION HELP ON {_help_ = 1;}
	| OPTION HELP OFF {_help_ = 0; }
	| OPTION MULTITASK ON {_multitask_ = 1;}
	| OPTION MULTITASK OFF {_multitask_ = 0; }
	| OPTION MAIN OFF {_show_main_ = 0; }
	| OPTION MAIN ON {_show_main_ = 1; }

mode :    READ						 { $<mode>$ = MODE_READ; }
        | WRITE						 { $<mode>$ = MODE_WRITE; }
	| APPEND					 { $<mode>$ = MODE_APPEND; }
	| ARCHIVE					 { $<mode>$ = MODE_ARCHIVE; }
;
math_fn:  SIN   '(' exp ')'				 { $<node>$ = do_math("sin", $<expr>3, DATATYPE_DOUBLE); }
	| SINH  '(' exp ')'				 { $<node>$ = do_math("sinh", $<expr>3, DATATYPE_DOUBLE); }
	| ASIN  '(' exp ')'				 { $<node>$ = do_math("asin", $<expr>3, DATATYPE_DOUBLE); }
	| ASINH '(' exp ')'				 { $<node>$ = do_math("asinh", $<expr>3, DATATYPE_DOUBLE); }
	| ABS '(' exp ')'				 { $<node>$ = do_math("abs", $<expr>3, DATATYPE_INT); }
	| DABS '(' exp ')'				 { $<node>$ = do_math("abs", $<expr>3, DATATYPE_DOUBLE); }
	| INT '(' exp ')'				 { $<node>$ = do_math("int", $<expr>3, DATATYPE_INT); }
	| COS   '(' exp ')'				 { $<node>$ = do_math("cos", $<expr>3, DATATYPE_DOUBLE); }
	| COSH  '(' exp ')'				 { $<node>$ = do_math("cosh", $<expr>3, DATATYPE_DOUBLE); }
	| ACOS  '(' exp ')'				 { $<node>$ = do_math("acos", $<expr>3, DATATYPE_DOUBLE); }
	| ACOSH '(' exp ')'				 { $<node>$ = do_math("acosh", $<expr>3, DATATYPE_DOUBLE); }
	| TAN   '(' exp ')'				 { $<node>$ = do_math("tan", $<expr>3, DATATYPE_DOUBLE); }
	| ACTAN '(' exp ')'				 { $<node>$ = do_math("actan", $<expr>3, DATATYPE_DOUBLE); }
	| ACTANH '(' exp ')'				 { $<node>$ = do_math("actanh", $<expr>3, DATATYPE_DOUBLE); }
	| ATAN  '(' exp ')'				 { $<node>$ = do_math("atan", $<expr>3, DATATYPE_DOUBLE); }
	| ATANH '(' exp ')'				 { $<node>$ = do_math("atanh", $<expr>3, DATATYPE_DOUBLE); }
	| SQRT  '(' exp ')'				 { $<node>$ = do_math("sqrt", $<expr>3, DATATYPE_DOUBLE); }
	| INV  '(' exp ')'				 { $<node>$ = do_math("inv", $<expr>3, DATATYPE_DOUBLE); }
	| EXP   '(' exp ')'				 { $<node>$ = do_math("exp", $<expr>3, DATATYPE_DOUBLE); }
	| LOG   '(' exp ')'				 { $<node>$ = do_math("log", $<expr>3, DATATYPE_DOUBLE); }
	| LOG10 '(' exp ')'				 { $<node>$ = do_math("log10", $<expr>3, DATATYPE_DOUBLE); }
	| LOG2  '(' exp ')'				 { $<node>$ = do_math("log2", $<expr>3, DATATYPE_DOUBLE); }
	| POW2  '(' exp ')'				 { $<node>$ = do_math("pow2", $<expr>3, DATATYPE_DOUBLE); }
	| RND  '(' exp ')'				 { $<node>$ = do_math("rnd", $<expr>3, DATATYPE_INT); }
	| POW  '(' exp ',' exp ')'		 { $<node>$ = do_math2("pow", $<expr>3, $<expr>5, DATATYPE_DOUBLE); }
	| SQR_POW  '(' exp ',' exp ')'	 { $<node>$ = do_math2("sqr_pow", $<expr>3, $<expr>5, DATATYPE_DOUBLE); }
	| KEY                            { $<node>$ = do_bcommand("_key", zero_term, NULL); }
	| KEY   '(' exp ')'              { $<node>$ = do_bcommand("_key", $<expr>3, NULL); }
	| GETKEY                         { $<node>$ = do_bcommand("_getkey", NULL); }
	| CHAR   '(' exp ')'             { $<node>$ = do_char($<expr>3); }
	| GETCHAR                        { $<node>$ = do_bcommand("_getchar", NULL); }
	| BEOF  '(' exp ')'				 { $<node>$ = do_bcommand("_eof", $<expr>3, NULL); }
	| COLLISION '(' exp ',' exp ')'			 { $<node>$ = do_bcommand("_collision", $<expr>3, $<expr>5, NULL); }
	| D3COLLISION '(' exp ',' exp ',' exp ')'	{ $<node>$ = do_bcommand("_3d_collision", $<expr>3, $<expr>5, $<expr>7, NULL); }
	| USERMENU '(' exp ',' exp ')'			 { $<node>$ = do_bcommand("_usermenu", $<node>3, $<node>5, NULL); }
	| TOCYID '(' exp ')'			 { $<node>$ = do_bcommand("_tocyid", $<node>3, NULL); }
	| TOUSER '(' exp ')'			 { $<node>$ = do_bcommand("_touser", $<node>3, NULL); }
	| DIALOG '(' exp ',' exp ')'{ $<node>$ = do_bcommand("_dialog", $<node>3, $<node>5, null_term, zero_term, NULL); }
	| DIALOG '(' exp ',' exp ',' varterm ',' exp ')'{ $<node>$ = do_bcommand("_dialog", $<node>3, $<node>5, $<node>7, $<node>9, NULL); }
	| NEXTFILE '(' varterm  ')'{ $<node>$ = do_bcommand("_nextfile", $<node>3, NULL); }
	| FILELIST '(' exp ',' exp ',' varterm  ')'{ $<node>$ = do_bcommand("_filelist", $<node>3, $<node>5, $<node>7, bterm_new("_ptr_main_module"), NULL); }
	| EXISTS '(' exp ')'{ $<node>$ = do_bcommand("_exists", $<expr>3, NULL); }
	| LEN '(' exp ')'{ $<node>$ = do_bcommand("strlen", $<expr>3, NULL); }
	| STRINGWIDTH  '(' exp ')'				 { $<node>$ = do_math("stringwidth", $<expr>3, DATATYPE_INT); }
	| STRINGHEIGHT  '(' exp ')'				 { $<node>$ = do_math("stringheight", $<expr>3, DATATYPE_INT); }
	| WRAP  '(' exp ',' exp ',' exp ',' exp ',' exp ',' exp ',' exp ')' { $<node>$ = do_bcommand("_wrap", $<expr>3, $<expr>5, $<expr>7, $<expr>9, $<expr>11, $<expr>13, $<expr>15); }
;
list:	   exp			{ $<expr>$ = $<expr>1; }
	|  list ',' exp		{ $<node>$ = do_list($<node>1, $<node>3); }
;
label_list:	   varterm			{ $<node>$ = $<node>1; }
	|  label_list ',' varterm		{ $<node>$ = do_list($<node>1, $<node>3); }
;
param: varname AS datatype	{ $<node>$ = do_param($<string>1, $<num>3, 0, BDIM_BY_VAL, NULL); }
	|  varname '[' ']' AS datatype	{ $<node>$ = do_param($<string>1, $<num>5, 1, BDIM_BY_VAL, NULL); }
	|  BY_REF varname AS datatype	   { $<node>$ = do_param($<string>2, $<num>4, 0, BDIM_BY_REF, NULL); }
	|  BY_VAL varname AS datatype    { $<node>$ = do_param($<string>2, $<num>4, 0, BDIM_BY_VAL, NULL); }
/*  |  varname              { $<node>$ = do_param($<string>1, DATATYPE_INT, 0, BDIM_BY_VAL, NULL); }
	|  varname '[' ']'     { $<node>$ = do_param($<string>1, DATATYPE_INT, 1, BDIM_BY_VAL, NULL); }
	|  BY_REF varname       { $<node>$ = do_param($<string>2, DATATYPE_INT, 0, BDIM_BY_REF, NULL); }
	|  BY_VAL varname     { $<node>$ = do_param($<string>2, DATATYPE_INT, 0, BDIM_BY_VAL, NULL); };*/
;
paramlist: /* nothing */       { $<node>$ = NULL; }
	|  param	       { $<node>$ = $<node>1; }
	|  paramlist ',' param { $<node>$ = do_paramlist($<node>1, $<node>3); }
;
comment:   '\n'    {$<node>$=NULL;}
	|  COMMENT {$<node>$=NULL;}
;
assignment:
	term '=' exp 	{ $<expr>$ = do_bop($<expr>1, OP_EQ, $<expr>3); }
;
subscript:  '[' exp ']'		{ $<expr>$ = $<expr>2; }
	|		'[' exp ',' exp ']'  { $<node>$ = do_list($<node>2, $<node>4); }
;
function_call:  varname '(' explist ')' { $<expr>$ = do_funccall($<string>1, (Blist *)$<expr>3); }
;
sub_call:  varname '(' explist ')' { $<expr>$ = do_funccall($<string>1, (Blist *)$<expr>3); }
	|  varname		   { $<expr>$ = do_funccall($<string>1, NULL); }
;
explist : /* nothing */		{ $<node>$ = NULL; }
        | exp			{ $<node>$ = $<node>1; }
        | explist ',' exp	{ $<node>$ = do_funclist($<node>1, $<node>3); }
;
exp:      term			{ $<node>$ = do_bexpr($<term>1); }
	| function_call		{ $<node>$ = $<node>1; }
	| exp '+' exp		{ $<expr>$ = do_bop($<expr>1, OP_ADD, $<expr>3);}
	| exp '-' exp		{ $<expr>$ = do_bop($<expr>1, OP_SUB, $<expr>3);}
	| exp '*' exp		{ $<expr>$ = do_bop($<expr>1, OP_MUL, $<expr>3);}
	| exp '/' exp		{ $<expr>$ = do_bop($<expr>1, OP_DIV, $<expr>3);}
	| exp MOD exp		{ $<expr>$ = do_bop($<expr>1, OP_MOD, $<expr>3);}
	| exp '<' exp		{ $<expr>$ = do_bop($<expr>1, OP_LESSER, $<expr>3);}
	| exp '>' exp		{ $<expr>$ = do_bop($<expr>1, OP_GREATER, $<expr>3);}
	| exp GE exp		{ $<expr>$ = do_bop($<expr>1, OP_GEQ, $<expr>3);}
	| exp LE exp		{ $<expr>$ = do_bop($<expr>1, OP_LEQ, $<expr>3);}
	| exp NEQ exp		{ $<expr>$ = do_bop($<expr>1, OP_NEQ, $<expr>3);}
	| exp AND exp		{ $<expr>$ = do_bop($<expr>1, OP_AND, $<expr>3);}
	| exp OR exp		{ $<expr>$ = do_bop($<expr>1, OP_OR, $<expr>3);}
	| exp '=' exp		{ $<expr>$ = do_bop($<expr>1, OP_EQEQ, $<expr>3);}
	| NOT exp %prec	NEG	{ $<expr>$ = do_bop(NULL, OP_NOT, $<expr>2);}
	| '-' exp %prec	NEG	{ $<expr>$ = do_bop(NULL, OP_UNARY_MINUS, $<expr>2);}
	| '+' exp %prec	NEG	{ $<expr>$ = do_bop(NULL, OP_UNARY_PLUS, $<expr>2);}
	| '(' exp ')'           { $<expr>$ = do_bop(NULL, OP_LPAREN, $<expr>2); }
;
varterm :  /** nothing **/ {$<node>$ = do_varterm(""); }
	|	VAR			{ $<node>$ = do_varterm(lowercase(yacctext)); }
;
varname:  VAR			{ $<string>$=strdup(lowercase(yacctext)); }
;
filename:  FILENAME { $<string>$=strdup(yacctext);}
;
lineno:  LITERAL_INT { $<string>$=strdup(yacctext);}
;
defname:  VAR			{ $<string>$=strdup(uppercase(yacctext)); }
;
inline:   INLINE		{ $<string>$=strdup(yacctext); }
;
outline:   OUTLINE		{ $<string>$=strdup(yacctext); }
;
scalar:	   varname		{ $<node>$ = do_variable((Bterm *)do_bterm($<string>1, 0, 0, 0), 0); }
	|  varname subscript	{ $<node>$ = do_variable((Bterm *)do_bterm($<string>1, 0, 0, 0), $<node>2); }
;
tscalar:	   varname		{ $<node>$ = do_bterm($<string>1, 0, 0, 0); }
	|  varname subscript	{ $<node>$ = do_bterm($<string>1, 0, 0, 0); $<expr>$->addchild($<expr>$, $<expr>2); }
;
type_scalar_var : tscalar
	| tscalar '.' type_scalar_var	{ $<node>$ = $<node>1; $<node>1->addchild($<node>1, $<node>3); }
;
term:	  LITERAL_INT		{ $<node>$ = do_bterm(yacctext, DATATYPE_INT, 1, 0); }
	| LITERAL_LONG		{ $<node>$ = do_bterm(yacctext, DATATYPE_LONG, 1, 0); }
	| LITERAL_DOUBLE	{ $<node>$ = do_bterm(yacctext, DATATYPE_DOUBLE, 1, 0); }
	| LITERAL_STRING	{ $<node>$ = do_bterm(fix_string(yacctext), DATATYPE_CHAR, 1, 1); }
	| LITERAL_CHAR		{ $<node>$ = do_bterm(yacctext, DATATYPE_CHAR, 1, 0); }
	| '#' defname		{ $<node>$ = do_bterm($<string>2, DATATYPE_INT, 1, 0); }
	| math_fn			{ $<node>$ = $<node>1; }
	| type_scalar_var	{ $<node>$ = do_variable((Bterm *)$<node>1, NULL); }
	| scalar			{ $<node>$ = $<node>1; }
	| WHITE				{ $<node>$ = do_bterm("0", DATATYPE_INT, 1, 0); }
	| LTGREY			{ $<node>$ = do_bterm("1", DATATYPE_INT, 1, 0); }
	| DKGREY			{ $<node>$ = do_bterm("2", DATATYPE_INT, 1, 0); }
	| BLACK				{ $<node>$ = do_bterm("3", DATATYPE_INT, 1, 0); }
	| FLIP_X            { $<node>$ = do_bterm("1", DATATYPE_INT, 1, 0); }
	| FLIP_Y            { $<node>$ = do_bterm("2", DATATYPE_INT, 1, 0); }
	| CAMERA            { $<node>$ = do_bterm("0", DATATYPE_INT, 1, 0); }
	| B2C_TRUE				{ $<node>$ = do_bterm("_true_", DATATYPE_INT, 1, 0); }
	| B2C_FALSE				{ $<node>$ = do_bterm("_false_", DATATYPE_INT, 1, 0); }
	| ERROR				{ $<node>$ = do_bterm("error", DATATYPE_INT, 1, 0); }
	| LEFT				{ $<node>$ = do_bterm("ALIGN_LEFT", DATATYPE_INT, 1, 0); }
	| CENTER			{ $<node>$ = do_bterm("ALIGN_CENTER", DATATYPE_INT, 1, 0); }
	| RIGHT				{ $<node>$ = do_bterm("ALIGN_RIGHT", DATATYPE_INT, 1, 0); }
	| CHAR				{ $<node>$ = do_bterm("WRAP_CHAR", DATATYPE_INT, 1, 0); }
	| WORD				{ $<node>$ = do_bterm("WRAP_WORD", DATATYPE_INT, 1, 0); }
;
datatype:   CHAR		{$<num>$=DATATYPE_CHAR;}
	  | INT			{$<num>$=DATATYPE_INT;}
	  | DOUBLE		{$<num>$=DATATYPE_DOUBLE;}
	  | LONG		{$<num>$=DATATYPE_LONG;}
;
%%
void yyerror(s)
     char *s;
{
  printf("%s(%d): (level=%d) ERROR - %s\n", g_infname, yylineno, body_stack_n, s );
  exit(1);
}

char *fix_string(char *s)
{
  char buf[256];
  char *x;
  char *y;
  if (c_strings) return s;
  for(x=s, y=buf; *x; x++, y++)
  {
	if (*x=='\\') {*y='\\'; y++;}
	*y=*x;
  }
  *y = 0;
  return strdup(buf);
}

Bdim *find_function_name(name)
     char *name;
{
	Bfunction *bfunction;
	Node *n = NULL;

	DBG0(">find_function_name\n");

	for(bfunction=(Bfunction *)bprogram->child; 
		bfunction; 
		bfunction=(Bfunction *)bfunction->next)
	{
		if (bfunction->type != TYPE_FUNCTION) continue;
		if (SAME(bfunction->name, name)) break;
	}

	if (bfunction == NULL)
	{
		int i;
		for(i=0; i<=body_stack_n; i++)
		{
			bfunction = (Bfunction *)body_stack[i];
			if (bfunction->type != TYPE_FUNCTION) continue;
			if (SAME(bfunction->name, name)) break;
		}
		if (i > body_stack_n) bfunction = NULL;
	}

	DBG0("<find_function_name\n");
	return (Bdim *)bfunction;
}

Bdim *find_function_dim(name)
     char *name;
{
  Bfunction *bfunction;
  int i;
  Node *n = NULL;
  Bdim *bdim;

  DBG0(">find_function_dim\n");
  for(i=body_stack_n; i>=0; i--)
    {
		if (body_stack[i]->type == TYPE_FUNCTION)
		break;
    }
  if (i != -1)
    {
		bfunction = (Bfunction *)body_stack[i];
		for(n=bfunction->child; n; n=n->next)
		{
			if (n->type == TYPE_DIM)
			{
			  bdim = (Bdim *)n;
			  if (SAME(bdim->name, name)) break;
			}
		}
    }
  DBG0("<find_function_dim\n");
  return (Bdim *) n;
}

Bdim *find_function_return(name)
     char *name;
{
  Bfunction *bfunction = NULL;
  Bdim *bdim = NULL;
  int i;

  DBG0(">find_function_return\n");
  for(i=body_stack_n; i>=0; i--)
    {
      if (body_stack[i]->type == TYPE_FUNCTION)
      {
		bfunction = (Bfunction *) body_stack[i];
		if (SAME(bfunction->name, name)) 
		{
			bdim = (Bdim *) bfunction;
			break;
		}
      }
    }
  DBG0("<find_function_return\n");
  return bdim;
}

Bdim *find_function_param(name)
     char *name;
{
  Bfunction *bfunction;
  int i;
  Node *n=NULL;
  Bdim *bdim;

  DBG0(">find_function_param\n");
  for(i=body_stack_n; i>=0; i--)
    {
      if (body_stack[i]->type == TYPE_FUNCTION)
	break;
    }
  if (i != -1) 
    {
      bfunction = (Bfunction *) body_stack[i];
      if (bfunction->child->type == TYPE_LIST) 
	bfunction = (Bfunction *)bfunction->child;
      for(n=bfunction->child; n; n=n->next)
	{	
	  bdim = (Bdim *) n;
	  if (n->type == TYPE_PARAM)
	    {
	      if (SAME(bdim->name, name)) break;
	    }
	}
    }
  DBG0("<find_function_param\n");
  return (Bdim *) n;
}

Bdim *find_program_dim(name)
     char *name;
{
  Node *n;
  Bdim *bdim;

  DBG0(">find_program_dim\n");
  for(n=bprogram->child; n; n=n->next)
    {
      if (n->type == TYPE_DIM)
		{
		  bdim = (Bdim *) n;
		  if (SAME(bdim->name, name)) break;
		}
    }
  DBG0("<find_program_dim\n");
  return (Bdim *) n;
}

Node *do_bterm(name, datatype, literal, dimension)
     char *name;
     int datatype;
     int literal;
	 int dimension;
{
   Bterm *bterm= bterm_new(name); 

   DBG0(">do_bterm\n");

   bterm->datatype=datatype; 
   bterm->literal = literal;
   bterm->dimension = dimension;

   DBG0("<do_bterm\n");
   return (Node *) bterm;
}

Node *do_variable(Bterm *bterm, Node *subscript)
{
	Bdim *bdim;

	DBG0(">do_variable name=%s\n", bterm->name);

	bdim = find_function_return(bterm->name);
	if (bdim) // found a function return value, use _name
	{
		Bfunction *bfunction = (Bfunction *) bdim;
		bterm->datatype = bfunction->datatype;
		bterm->dim = (Bdim *) bfunction;
		if (bterm->name) free(bterm->name);
		bterm->name = malloc(strlen(bfunction->name)+2);
		sprintf(bterm->name, "_%s", bfunction->name);
		goto EARLY_EXIT;
	}
	if (bdim == NULL) bdim = find_function_dim(bterm->name);
	if (bdim == NULL) bdim = find_function_param(bterm->name);
	if (bdim == NULL) bdim = find_program_dim(bterm->name);
	if (bdim == NULL) bdim = find_function_name(bterm->name);
	if (bdim == NULL) doerr2("%s(%d) ERROR - Variable %s undefined in line %d", g_infname, yylineno, bterm->name, yylineno);
	if (bdim->type == TYPE_DIM || bdim->type == TYPE_PARAM)
	{
		DBG0("...Its a DIM or PARAM\n");
		bterm->datatype = bdim->datatype;
		bterm->dim = bdim;
		bterm->dimension = bdim->dimension;
		if (subscript)
		{
			bterm->addchild(bterm, subscript);
			if (subscript->type == TYPE_LIST) 
				bterm->dimension = bterm->dimension - 2;
			else 
				bterm->dimension = bterm->dimension - 1;
		}
		if (bdim->datatype == DATATYPE_TYPE)
		{
			Bterm *member=(Bterm *)bterm->last;
			Bdim  *found=(Bdim *)find_member_name(bdim->btype, member->name);
			if (found==NULL)
				doerr2("could not find member %s", member->name);
			else
			{
				bterm->datatype = found->datatype;
				if (found->child)
				{
					if (found->child->type == TYPE_EXPR)
					{
						bterm->dimension = 1;
					}
					else if (found->child->type == TYPE_LIST)
					{
						bterm->dimension = 2;
					}
				}
			}
		}
	}
	else if (bdim->type == TYPE_FUNCTION)  // found a function call use name()
	{
		Bfunccall *bfunccall = bfunccall_new();
		Bfunction *bfunction = (Bfunction *) bdim;
		bfunccall->bfunction = bfunction;
		bterm = (Bterm *) do_bexpr((Bterm *)bfunccall);
	}
	else
	{
		doerr2("%d(%s) ERROR - Variable %s is not defined (line %d) type=%d\n", g_infname, yylineno, bterm->name, yylineno, bdim->type);
	}
EARLY_EXIT:
	DBG0("<do_variable name=%s\n", bterm->name);
	return (Node *)bterm;
}

Node *do_bstatement(expr, lineno)
  Node *expr;
  int lineno;
{
  Bstatement *bstatement = bstatement_new();

  DBG0(">do_bstatement\n");

  bstatement->addchild(bstatement, expr); 
  bstatement->lineno = lineno-1;

  DBG0("<do_bstatement\n");

  return (Node *) bstatement;
}

Node *find_type_name(char *name)
{
	Btype *n;

	for(n=(Btype *)bprogram->child; n; n=(Btype *)n->next)
	{
		if (n->type == TYPE_TYPE && SAME(name, n->name))
		{
			return (Node *)n;
		}
	}
	return NULL;
}

Bdim *find_member_name(Btype *btype, char *name)
{
	Bdim *n;

	for(n=(Bdim *)btype->child; n; n=(Bdim *)n->next)
	{
		if (SAME(name, n->name))
		{
			return (Bdim *)n;
		}
	}
	return NULL;
}

Node *do_bdim(var, datatype, expr, typename)
	char *var;
	int datatype;
	Node *expr;
	char *typename;
{
  Bdim *bdim = bdim_new();
  int i;
  Bfunction *bfunction;

DBG0(">do_bdim\n");
  strcpy(bdim->name, var);
  bdim->datatype = datatype;
  bdim->dimension = 0;
  if (expr) 
  {
	bdim->addchild(bdim, expr);
	if (expr->type == TYPE_EXPR)
		bdim->dimension=1;
	else if (expr->type == TYPE_LIST)
		bdim->dimension=2;
  }

  for(i=body_stack_n; i>=0; i--)
    {
      if (body_stack[i]->type == TYPE_FUNCTION ||
		  body_stack[i]->type == TYPE_PROGRAM)
      {
		bfunction = (Bfunction *) body_stack[i];
		bfunction->addchild(bfunction, bdim);
		break;
      }
    }
  if (typename)
  {
	  bdim->btype = (Btype *)find_type_name(typename);
	  if (bdim->btype == NULL)
	  {
	      doerr2("%s(%d) ERROR - user defined type '%s' is unknown", g_infname, yylineno, typename );
	  }
  }
DBG0("<do_bdim\n");

  return (Node *)NULL;
}

Node *do_bexpr(term)
	Bterm *term;
{
  Bexpr *bexpr = bexpr_new();

  DBG0(">do_bexpr\n");

  bexpr->addchild(bexpr, term);

  /** pass the literal flag up **/
  bexpr->datatype = term->datatype;
  bexpr->literal = term->literal;
  bexpr->dimension = term->dimension;

  DBG0("<do_bexpr\n");

  return (Node *)bexpr;
}

Bexpr *do_bop(left, op, right)
     Bexpr *left;
     int op;
     Bexpr *right;
{
  Bop *bop = bop_new(op);

  DBG0(">do_bop\n");

  if (left) bop->addchild(bop, left);
  if (right) bop->addchild(bop, right);

	switch(bop->op) {
	  case OP_NOT:
	  case OP_UNARY_MINUS:
	  case OP_UNARY_PLUS:
	  case OP_LPAREN: 
		  bop->datatype = right->datatype;
		  break;
	  case OP_AND:
	  case OP_OR: 
	  case OP_NEQ:
	  case OP_LEQ:
	  case OP_GEQ:
	  case OP_GREATER:
	  case OP_EQEQ:
	  case OP_LESSER:
	      bop->datatype = DATATYPE_INT;
		  break;
	  case OP_ADD:
	  case OP_SUB:
	  case OP_MUL:
	  case OP_DIV:
	  case OP_MOD:
		if (left->datatype == right->datatype)
		{
			bop->datatype = left->datatype;
		}
		else if (left->datatype > right->datatype)
	    {
	      bop->datatype = left->datatype;
	    }
		else 
	    {
	      bop->datatype = right->datatype;
	    }
		break;
  	  case OP_EQ: 
		bop->datatype = left->datatype;
		break;
	  case OP_LBRACKET: 
		bop->datatype = left->datatype;
		break;
	  default:
		doerr2("%s(%d) ERROR - Internal Error - bad Op", g_infname, yylineno );
	}

  DBG0("<do_bop\n");

  return (Bexpr *) bop;
}

Node *do_bfor(name, from, to, step)
     char *name;
     Node *from;
     Node *to;
     Node *step;
{
  Bfor *bfor;
  Bdim *bdim;
  Bterm *counter= bterm_new(name); 
  int i;

  DBG0(">do_bfor\n");

  bfor = bfor_new();

  bdim = find_function_dim(name);
  if (!bdim) bdim = find_program_dim(name);
  if (!bdim)
  {
     for(i=body_stack_n; i>=0; i--)
     {
		if (body_stack[i]->type == TYPE_FUNCTION || 
			body_stack[i]->type == TYPE_PROGRAM)
		{
			do_bdim(name, DATATYPE_INT, NULL, NULL);
			break;
		}
     }
  }
  bfor->addchild(bfor, counter);
  bfor->addchild(bfor, from);
  bfor->addchild(bfor, to);
  if (step) bfor->addchild(bfor, step);

  DBG0(">do_bfor\n");

  return (Node *) bfor;
}

Node *do_bwhile(expr)
     Node *expr;
{
  Bwhile *bwhile;

  DBG0(">do_bwhile\n");

  if (expr == NULL)
  {
	doerr2("%s(%d) ERROR - Function WHILE has missing expression.\n", 
		g_infname, yylineno);
  }

  bwhile = bwhile_new();
  bwhile->addchild(bwhile, expr);

  DBG0("<do_bwhile\n");
  return (Node *) bwhile;
}

Node *do_bfunction(name, parameters, datatype)
     char *name;
     Node *parameters;
     int datatype;
{
	Bfunction *bfunction;

	DBG0(">do_bfunction\n");

	bfunction = (Bfunction *) find_function_name(name);
	// if the function was previously defined...
	if (bfunction && bfunction->child)
	{
		doerr2("%s(%d) ERROR - Function %s previously defined.\n", 
			g_infname, yylineno, name);
	}
	// if the function was called but not defined
	else if (bfunction)
	{
		bfunction->remchild(bfunction);
	}
	// if the function was never called nor defined
	else if (bfunction == NULL)
	{
		bfunction = bfunction_new();
	}

	strcpy(bfunction->name, name);
	if (SAME(name, "onmessage"))
	{
		_onmessage_defined_ = 1;
	}
	bfunction->datatype = datatype;
	if (!parameters)
	  parameters = (Node *) blist_new();
	bfunction->addchild(bfunction, parameters);
	DBG0("<do_bfunction\n");
	return (Node *) bfunction;
}

Node *do_bif(exp)
     Node *exp;
{
  Bif *bif;
  Bthen *bthen;
  DBG0(">do_bif\n");
  bif = bif_new();
  bthen = bthen_new();
  bif->addchild(bif, exp);
  bif->addchild(bif, bthen);
  push((Node *) bif);
  push((Node *) bthen);
  DBG0("<do_bif\n");
  return (Node *) bif;
}

Node *do_bif2(exp, stmt)
     Node *exp;
	 Node *stmt;
{
  Bif *bif;
  Bthen *bthen;
  DBG0(">do_bif2\n");
  bif = bif_new();
  bthen = bthen_new();
  bif->addchild(bif, exp);
  bif->addchild(bif, bthen);
  bthen->addchild(bthen, stmt);
  DBG0("<do_bif2\n");
  return (Node *) bif;
}

Node *do_belseif(exp)
     Node *exp;
{
  Belseif *belseif;
  Bif *bif = (Bif *) body_stack[body_stack_n];

  DBG0(">do_belseif\n");

  belseif = belseif_new();
  belseif->addchild(belseif, exp);
  bif->addchild(bif, belseif);
  push((Node *) belseif);
  DBG0("<do_belseif\n");
  return (Node *)belseif;
}

Node *do_belse()
{
  Belse *belse;
  Bif *bif = (Bif *)body_stack[body_stack_n];
  DBG0(">do_belse\n");
  belse = belse_new();
  bif->addchild(bif, belse);
  push((Node *) belse);
  DBG0("<do_belse\n");
  return (Node *) belse;
}

Node *do_bexitfor()
{
	int i;
    Bexit *bexit = bexit_new();
    DBG0(">do_bexitfor\n");
	for(i=body_stack_n; i>=0; i--)
	{
		if (body_stack[i]->type == TYPE_FOR) break;
		if (body_stack[i]->type == TYPE_PROGRAM ||
			body_stack[i]->type == TYPE_FUNCTION ||
			body_stack[i]->type == TYPE_WHILE)
			{
				doerr2("%s(%d) ERROR - Misplaced Exit For (line %d)\n", g_infname, yylineno, yylineno);
			}
	}
    DBG0("<do_bexitfor\n");
    return (Node *) bexit;
}

Node *do_bexitwhile()
{
	int i;
    Bexit *bexit = bexit_new();
    DBG0(">do_bexitwhile\n");
	for(i=body_stack_n; i>=0; i--)
	{
		if (body_stack[i]->type == TYPE_WHILE) break;
		if (body_stack[i]->type == TYPE_PROGRAM ||
			body_stack[i]->type == TYPE_FUNCTION ||
			body_stack[i]->type == TYPE_FOR)
		{
			doerr2("%s(%d) ERROR - Misplaced Exit While (line %d)\n", g_infname, yylineno, yylineno);
		}
	}
    DBG0("<do_bexitwhile\n");
    return (Node *) bexit;
}

Node *do_bexitfunction()
{
    Bexitfunction *bexitfunction = bexitfunction_new();
    DBG0(">do_bexitfunction\n");
//    if (body_stack[body_stack_n]->type != TYPE_FUNCTION)
//       doerr2("%s(%d) ERROR - Misplaced Exit Function (line %d)\n", g_infname, yylineno, yylineno);
    DBG0(">do_bexitfunction\n");
    return (Node *) bexitfunction;
}

void push(node)
	Node *node;
{
	body_stack[++body_stack_n] = node;
}

Node *pop(type)
     int type;
{
	Node *node;

	node = body_stack[body_stack_n--];
	if (body_stack_n < 0)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Too many END/NEXT statements \n", g_infname, yylineno);
		exit(1);
	}
	if (node->type != type)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Mismatched END/NEXT statements \n", g_infname, yylineno);
		printf("                Found statement %s\n", node_types[node->type]);
		exit(1);
	}
	return node;
}

Node *pop2(type1, type2)
     int type1;
     int type2;
{
	Node *node;

	node = body_stack[body_stack_n--];
	if (body_stack_n < 0)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Too many END/NEXT statements \n", g_infname, yylineno);
		exit(1);
	}
	if (node->type != type1 && node->type != type2)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Mismatched END/NEXT statements \n", g_infname, yylineno);
		printf("                Found statement %s\n", node_types[node->type]);
		exit(1);
	}
	return node;
}

Node *pop3(type1, type2, type3)
     int type1;
     int type2;
     int type3;
{
	Node *node;

	node = body_stack[body_stack_n--];
	if (body_stack_n < 0)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Too many END/NEXT statements \n", g_infname, yylineno);
		exit(1);
	}
	if (node->type != type1 && node->type != type2 && node->type != type3)
	{
		//bprogram->dump(bprogram);
		printf("%s(%d): ERROR - Mismatched END/NEXT statements \n", g_infname, yylineno);
		printf("                Found statement %s\n", node_types[node->type]);
		exit(1);
	}
	return node;
}

Node *do_bprintno(fileno, list)
     Bexpr *fileno;
     Node *list;
{
    Bprintno *bprintno = bprintno_new();
    DBG0(">do_bprintno\n");
    bprintno->addchild(bprintno, fileno);
    if (list) bprintno->addchild(bprintno, list);
    DBG0("<do_bprintno\n");
    return (Node *) bprintno;
}

Node *do_bprint(list)
     Node *list;
{
    Bprint *bprint = bprint_new();
DBG0(">do_bprint\n");
    if (list) bprint->addchild(bprint, list);
DBG0("<do_bprint\n");
    return (Node *) bprint;
}

Node *do_bsprint(Node *var, Node *list)
{
    Bsprint *bsprint = bsprint_new();
	DBG0(">do_bsprint\n");
	bsprint->addchild(bsprint, var);
    bsprint->addchild(bsprint, list);
	DBG0("<do_bsprint\n");
    return (Node *) bsprint;
}

Node *do_btokenize(Node *var, Node *tokens, Node *list)
{
    Btokenize *btokenize = btokenize_new();
	DBG0(">do_btokenize\n");
	btokenize->addchild(btokenize, var);
	btokenize->addchild(btokenize, tokens);
    btokenize->addchild(btokenize, list);
	DBG0("<do_btokenize\n");
    return (Node *) btokenize;
}

Node *do_bprintxy(x,y,list)
     Bexpr *x;
     Bexpr *y;
     Node *list;
{
    Bprintxy *bprintxy = bprintxy_new();
    DBG0(">do_bprintxy\n");
    bprintxy->addchild(bprintxy, x);
    bprintxy->addchild(bprintxy, y);
    bprintxy->addchild(bprintxy, list);
    DBG0("<do_bprintxy\n");
    return (Node *) bprintxy;
}

Node *do_list(expr1, expr2)
     Node *expr1;
     Node *expr2;
{
	if (expr1->type == TYPE_LIST)
	{
		expr1->addchild(expr1, expr2);
		return expr1;
	}
	else
	{
		Blist *blist = blist_new();
		blist->addchild(blist, expr1);
		blist->addchild(blist, expr2);
		return (Node *) blist;
	}
}


Node *do_paramlist(expr1, expr2)
     Node *expr1;
     Node *expr2;
{
	if (expr1->type == TYPE_LIST)
	{
		expr1->addchild(expr1, expr2);
		return expr1;
	}
	else
	{
		Blist *blist = blist_new();
		blist->addchild(blist, expr1);
		blist->addchild(blist, expr2);
		return (Node *) blist;
	}
}

Node *do_param(name, datatype, dimension, passed_by, initial_value)
     char *name;
     int datatype;
     int dimension;
     int passed_by;
     Bexpr *initial_value;
{
  Bparam *bparam = bparam_new();
  strcpy(bparam->name, name);
  bparam->datatype = datatype;
  bparam->dimension = dimension;
  bparam->passed_by = passed_by;
  if (initial_value)
    bparam->addchild(bparam, initial_value);
  return (Node *) bparam;
}

Bexpr *do_funccall(name, paramlist)
     char *name;
     Blist *paramlist;
{
    Bfunccall *bfunccall = bfunccall_new();
    Bfunction *bfunction = (Bfunction *) find_function_name(name);
    DBG0(">do_bfunccall\n");
    if (bfunction == NULL)
    {
		bfunction = bfunction_new();
		strcpy(bfunction->name, name);
		bprogram->addchild(bprogram, bfunction);
		bfunction->datatype = DATATYPE_INT;
	}

    bfunccall->bfunction = bfunction;
	bfunccall->datatype = bfunction->datatype;
    if (paramlist) bfunccall->addchild(bfunccall, paramlist);
    DBG0("<do_bfunccall\n");
    return (Bexpr *) do_bexpr((Bterm *)bfunccall);
}

Node *do_funclist(expr1, expr2)
     Node *expr1;
     Node *expr2;
{
	if (expr1->type == TYPE_LIST)
	{
		expr1->addchild(expr1, expr2);
		return expr1;
	}
	else
	{
		Blist *blist = blist_new();
		blist->addchild(blist, expr1);
		blist->addchild(blist, expr2);
		return (Node *) blist;
	}
}

Node *do_input(prompt, term)
     Bexpr *prompt;
     Bterm *term;
{
    Binput *binput;
    DBG0(">do_input\n");

    if (term->literal) 
	doerr2("%s(%d) ERROR -lineno %d : Cannot use literal for INPUT statement", g_infname, yylineno, yylineno);
    if (prompt && prompt->datatype != DATATYPE_CHAR) 
    {
       doerr2("%s(%d) ERROR - lineno %d : Cannot use non-string for INPUT prompt (datatype=%s)", 
		      g_infname, yylineno, yylineno, data_type[prompt->datatype]);
    }
    binput = binput_new();
    binput->addchild(binput, term);
    if (prompt)
       binput->addchild(binput, prompt);
    DBG0("<do_input\n");
    return (Node *)binput;
}

Node *do_inputxy(x, y, prompt, term)
	 Bexpr *x;
	 Bexpr *y;
     Bexpr *prompt;
     Bterm *term;
{
    Binputxy *binputxy;
    DBG0(">do_input\n");

    if (term->literal) 
	doerr2("%s(%d) ERROR -lineno %d : Cannot use literal for INPUTXY statement", g_infname, yylineno, yylineno);
    if (prompt && prompt->datatype != DATATYPE_CHAR) 
    {
       doerr2("%s(%d) ERROR - lineno %d : Cannot use non-string for INPUTXY prompt (datatype=%s)", 
		      g_infname, yylineno, yylineno, data_type[prompt->datatype]);
    }
    binputxy = binputxy_new();
    binputxy->addchild(binputxy, x);
    binputxy->addchild(binputxy, y);
    binputxy->addchild(binputxy, term);
    if (prompt)
       binputxy->addchild(binputxy, prompt);
    DBG0("<do_input\n");
    return (Node *)binputxy;
}

Node *do_char(exp)
    Bexpr *exp;
{
    Bchar *bchar = bchar_new();
    DBG0(">do_char\n");
    if (exp) bchar->addchild(bchar, exp);
    DBG0("<do_char\n");
    return (Node *) bchar;
}

Node *do_math(name, exp, type)
     char *name;
     Bexpr *exp;
	 int type;
{
    Bmath *bmath = bmath_new(name);
    DBG0(">do_math\n");
    bmath->addchild(bmath, exp);
    bmath->datatype = type;
    DBG0("<do_math\n");
    return (Node *) bmath;
}

Node *do_math2(name, exp1, exp2, type)
     char *name;
     Bexpr *exp1;
     Bexpr *exp2;
	 int type;
{
    Bmath *bmath = bmath_new(name);
    DBG0(">do_math2\n");
    bmath->addchild(bmath, exp1);
    bmath->addchild(bmath, exp2);
    bmath->datatype = type;
    DBG0("<do_math2\n");
    return (Node *) bmath;
}

Node *do_open(exp1, mode, exp2)
     Bexpr *exp1; /* filename */
     int mode;
     Bexpr *exp2; /* filenumber */
{
    Bopen *bopen = bopen_new();
    DBG0(">do_open\n");
    bopen->addchild(bopen, exp1);
    bopen->addchild(bopen, exp2);
    bopen->mode = mode;
    DBG0("<do_open\n");
    return (Node *) bopen;
}

Node *do_bscore(exp)
     Bexpr *exp;
{
    Bscore *bscore = bscore_new();
    DBG0(">do_bscore\n");

    if (exp)
       bscore->addchild(bscore, exp);
    DBG0("<do_score\n");
    return (Node *) bscore;
}

Node *do_put(exp1,exp2, name)
     Bexpr *exp1; /* filenumber */
     Bexpr *exp2; /* filepos - optional */
     Bterm *name; /* variable name */
{
    Bput *bput = bput_new();
    DBG0(">do_put\n");
    bput->addchild(bput, exp1);

    if (exp2)
    {
        bput->addchild(bput, exp2);
    }
    else /* empty file pos - replace with empty expression */
    {
	exp2 = bexpr_new();
        bput->addchild(bput, exp2);
    }

    if (name)
    {
       bput->addchild(bput, name);
    }
    else /* empty variable name - replace with emptye expression */
    {
       name = (Bterm *) bexpr_new();
       bput->addchild(bput, name);
    }

    DBG0("<do_put\n");
    return (Node *) bput;
}

Node *do_get(exp1,exp2, name)
     Bexpr *exp1; /* filenumber */
     Bexpr *exp2; /* filepos - optional */
     Bterm *name; /* variable name */
{
    Bget *bget = bget_new();
    DBG0(">do_get\n");
    bget->addchild(bget, exp1);

    if (exp2)
    {
        bget->addchild(bget, exp2);
    }
    else /* empty file pos - replace with empty expression */
    {
	exp2 = bexpr_new();
        bget->addchild(bget, exp2);
    }

    if (name)
    {
       bget->addchild(bget, name);
    }
    else /* empty variable name - replace with emptye expression */
    {
       name = (Bterm *) bexpr_new();
       bget->addchild(bget, name);
    }

    DBG0("<do_get\n");
    return (Node *) bget;
}

Node *do_mid(dest, src, start, len)
     Bterm *dest;
     Bexpr *src;
     Bexpr *start;
     Bexpr *len;
{
    Bmid *bmid = bmid_new();

    DBG0(">do_mid\n");
    bmid->addchild(bmid, dest);
    bmid->addchild(bmid, src);
    bmid->addchild(bmid, start);
    if (len) bmid->addchild(bmid, len);
    DBG0("<do_mid\n");
    return (Node *) bmid;
}

Node *do_binline(code)
     char *code;
{
	Binline *binline = binline_new();
    DBG0(">do_inline\n");
	binline->line = strdup(&code[7]);
    DBG0("<do_inline\n");
	return (Node *) binline;
}

Node *do_boutline(code)
     char *code;
{
	Boutline *boutline = boutline_new();
    DBG0(">do_outline\n");
	boutline->line = strdup(&code[8]);
    DBG0("<do_outline\n");
	return (Node *) boutline;
}

Node *do_bgoto(label)
     char *label;
{
	Bgoto *bgoto = bgoto_new(label);
    DBG0(">do_bgoto\n");
    DBG0("<do_bgoto\n");
	return (Node *) bgoto;
}

Node *do_blabel(label)
     char *label;
{
	Blabel *blabel = blabel_new(label);
    DBG0(">do_blabel\n");
    DBG0("<do_blabel\n");
	return (Node *) blabel;
}

Node *do_btype(name)
	char *name;
{
	Btype *btype = btype_new(name);
	DBG0(">do_btype\n");
	DBG0("<do_btype\n");
	return (Node *) btype;
}

Node *do_btype2(var, expr, datatype, typename)
	char *var;
	Node *expr;
	int datatype;
	char *typename;
{
  Bdim *bdim = bdim_new();
  Btype *btype;

  DBG0(">do_btype2\n");

  strcpy(bdim->name, var);
  bdim->datatype = datatype;
  bdim->dimension = 0;
  if (expr) bdim->addchild(bdim, expr);
  if (typename)
  {
	  bdim->btype = (Btype *)find_type_name(typename);
	  if (bdim->btype == NULL)
	  {
	      doerr2("%s(%d) ERROR - user defined type '%s' is unknown", g_infname, yylineno, typename );
	  }
  }

  btype = (Btype *)body_stack[body_stack_n];
  btype->addchild(btype, bdim);
//btype->dump(btype);  
  DBG0("<do_btype2\n");

  return (Node *)NULL;
}

Node *do_bsprite_get(Bexpr *n, Node *x, Node *y, Node *z, Node *mode, Node *w, Node *h)
{
	Bsprite_get *bsprite_get = bsprite_get_new();
	DBG0(">do_bsprite_get\n");
	bsprite_get->addchild(bsprite_get, n);
	bsprite_get->addchild(bsprite_get, x);
	bsprite_get->addchild(bsprite_get, y);
	bsprite_get->addchild(bsprite_get, z);
	bsprite_get->addchild(bsprite_get, mode);
	bsprite_get->addchild(bsprite_get, w);
	bsprite_get->addchild(bsprite_get, h);
	DBG0("<do_bsprite_get\n");
	return (Node *) bsprite_get;
}

Node *do_bredraw(Bexpr *exp)
{
    Bterm *bterm;
	Bredraw *bredraw = bredraw_new();
	DBG0(">do_bredraw\n");
	if (exp == (Bexpr *) -2)
	{
		bterm = (Bterm *)do_bterm("-2", DATATYPE_INT, 1, 0);
		bredraw->addchild(bredraw, bterm);
	}
	else if (exp == (Bexpr *)-1 || exp == NULL)
	{
		// null child //
	}
	else if (exp)
	{
		bredraw->addchild(bredraw, exp);
	}
	DBG0("<do_bredraw\n");
	return (Node *) bredraw;
}

Node *do_bcommand(char *command_name, ...)
{
    Bcommand *bcommand = bcommand_new(command_name);
	Node *node = NULL;
	va_list marker;

    DBG0(">do_bcommand(%s)\n", command_name);
	va_start( marker, command_name );     /* Initialize variable arguments. */
	node = va_arg( marker, Node *);
	while( node )
	{
		bcommand->addchild(bcommand, node);
		node = va_arg( marker, Node *);
	}
	va_end(marker);
	return (Node *)bcommand;
}

Node *do_bmusic(int opn, int channel, Bexpr *bexp)
{
	Bmusic *bmusic = bmusic_new();
	DBG0(">do_bmusic\n");
	bmusic->opn = opn;
	bmusic->channel = channel;
	if (bexp) bmusic->addchild(bmusic, bexp);
	DBG0("<do_bmusic\n");
	return (Node *) bmusic;
}

Node *do_bongosub(exp, list)
	Bexpr *exp;
     Node *list;
{
    Bongosub *bongosub = bongosub_new();
	DBG0(">do_bongosub\n");
	bongosub->addchild(bongosub, exp);
    bongosub->addchild(bongosub, list);
	DBG0("<do_bongosub\n");
    return (Node *) bongosub;
}


Node *do_bongoto(exp, list)
	Bexpr *exp;
     Node *list;
{
    Bongoto *bongoto = bongoto_new();
	DBG0(">do_bongoto\n");
	bongoto->addchild(bongoto, exp);
    bongoto->addchild(bongoto, list);
	DBG0("<do_bongoto\n");
    return (Node *) bongoto;
}


Node *do_varterm(char *name)
{
	Bterm *bterm = bterm_new(name);
	return (Node *)bterm;
}

Node *do_bmenu(varname, list)
     char *varname;
     Node *list;
{
    Bmenu *bmenu = bmenu_new(varname);
    DBG0(">do_bmenu\n");
    if (list) bmenu->addchild(bmenu, list);
    DBG0("<do_bmenu\n");
    return (Node *) bmenu;
}

Node *do_bmenuxy(x, y, varname, list)
	 Bexpr *x;
	 Bexpr *y;
     char *varname;
     Node *list;
{
    Bmenuxy *bmenuxy = bmenuxy_new(varname);
    DBG0(">do_bmenuxy\n");
	bmenuxy->addchild(bmenuxy, x);
	bmenuxy->addchild(bmenuxy, y);
    if (list) bmenuxy->addchild(bmenuxy, list);
    DBG0("<do_bmenuxy\n");
    return (Node *) bmenuxy;
}

Node *do_bexitprogram()
{
    Bexitprogram *bexitprogram = bexitprogram_new();
    DBG0(">do_bexitprogram\n");
    DBG0("<do_bexitprogram\n");
    return (Node *) bexitprogram;
}

char *uppercase(char *s)
{
	char *x = s;
	while(*s)
	{
		if (islower(*s)) *s=toupper(*s);
		s++;
	}
	return x;
}

char *lowercase(char *s)
{
	char *x = s;
	while(*s)
	{
		if (isupper(*s)) *s=tolower(*s);
		s++;
	}
	return x;
}

void update_lineno(char *filename, char *lineno)
{
	strcpy(g_infname, &filename[1]);
	yylineno = atoi(lineno);
}
