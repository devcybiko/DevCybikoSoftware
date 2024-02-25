%option yylineno
%{

#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "node.h"
#include "bexpr.h"
#include "bterm.h"
#include "b2cy.h"

extern char yacctext[1024];
%}
D	[0-9]
A	[a-zA-Z]
AN	[a-zA-Z0-9_]
%%

"dim"	{return DIM;}
"char"	{return CHAR;}
"int"	{return INT;}
"long"	{return LONG;}
"double" {return DOUBLE;}
"as"	 {return AS;}
"for"	 {return FOR;}
"to"	 {return TO;}
"step"   {return STEP;}
"next"   {return NEXT;}
"exit"	 {return EXIT;}
"if"	 {return IF;}
"then"	 {return THEN;}
"end"	 {return END;}
"else"	 {return ELSE;}
"elseif" {return ELSEIF;}
"print"	 {return PRINT;}
"while"	 {return WHILE;}
"wend"	 {return WEND;}
"sub"	 {return SUB;}
"function" {return FUNCTION;}
"byval"  {return BY_VAL;}
"byref"  {return BY_REF;}
"call"	 {return CALL;}
"wait"	 {return WAIT;}
"input"  {return INPUT;}
"inputxy"  {return INPUTXY;}
"line"	 {return LINE;}
"point"  {return POINT;}
"ink"    {return INK;}
"paper"  {return PAPER;}
"cls"    {return CLS;}
"printxy"	{return PRINTXY;}
"sin"	{return SIN;}
"sinh"	{return SINH;}
"asin"	{return ASIN;}
"asinh"	{return ASINH;}
"cos"	{return COS;}
"cosh"	{return COSH;}
"acos"  {return ACOS;}
"acosh"	{return ACOSH;}
"tan"	{return TAN;}
"actan"	{return ACTAN;}
"actanh" {return ACTANH;}
"atan"	{return ATAN;}
"atanh"	{return ATANH;}
"sqrt"	{return SQRT;}
"exp"	{return EXP;}
"log"	{return LOG;}
"log10"	{return LOG10;}
"log2"	{return LOG2;}
"pow2"	{return POW2;}
"rnd"	{return RND;}
"pow"   {return POW;}
"inv"	{return INV;}
"sqr_pow" {return SQR_POW;}
"key"   {return KEY;}
"eof"   {return BEOF;}
"open"  {return OPEN;}
"read"  {return READ;}
"write" {return WRITE;}
"append" {return APPEND;}
"close" {return CLOSE;}
"put"   {return PUT;}
"get"   {return GET;}
"and"	{return AND;}
"or"	{return OR;}
"<>"	{return NEQ;}
"beep"	{return BEEP;}
"mid"	{return MID;}
"right" {return RIGHT;}
"inline ".*"\n"	{strcpy(yacctext, yytext); return INLINE;}
"outline ".*"\n"	{strcpy(yacctext, yytext); return OUTLINE;}
"font"	{return FONT;}
"goto"	{return GOTO;}
"type"	{return TYPE;}
"sprite" {return SPRITE;}
"move" {return MOVE;}
"redraw" {return REDRAW;}
"collision" {return COLLISION;}
"music" {return MUSIC;}
"foreground" {return FOREGROUND;}
"background" {return BACKGROUND;}
"stop" {return STOP;}
"play" {return PLAY;}
"flip_x" {return FLIP_X;}
"flip_y" {return FLIP_Y;}
"vibrate" {return VIBRATE;}
"option" {return OPTION;}
"c_strings" {return C_STRINGS;}
"cybasic_strings" {return CYBASIC_STRINGS;}
"on" {return ON;}
"gosub" {return GOSUB;}
"show" {return SHOW;}
"all" {return ALL;}
"c_coords" {return C_COORDS;}
"cybasic_coords" {return CYBASIC_COORDS;}
"sprites" {return SPRITES;}
"score" {return SCORE;}
"white" {return WHITE;}
"ltgrey" {return LTGREY;}
"dkgrey" {return DKGREY;}
"black" {return BLACK;}
"menu"	{return MENU;}
"menuxy" {return MENUXY;}
"endif" {return ENDIF;}
"keyclick" {return KEYCLICK;}
"off" {return OFF;}
"program" {return PROGRAM;}
"not" {return NOT;}
"mod" {return MOD;}
"abs" {return ABS;}
"dabs" {return DABS;}
"int" {return INT;}
"escape" {return ESCAPE;}
"help" {return HELP;}
"multitask" {return MULTITASK;}
"getchar" {return GETCHAR;}
"getkey" {return GETKEY;}
"sendmessage" {return SENDMESSAGE;}
"sprint"	{return SPRINT;}
"tokenize"  {return TOKENIZE;}
"tocyid" {return TOCYID;}
"touser" {return TOUSER;}
"usermenu" {return USERMENU;}
"dialog" {return DIALOG;}
"3droom" {return D3ROOM;}
"3dsprite" {return D3SPRITE;}
"3dredraw" {return D3REDRAW;}
"3dwall" {return D3WALL;}
"3dcollision" {return D3COLLISION;}
"3dmove" {return D3MOVE;}
"3drmove" {return D3RMOVE;}
"3dget" {return D3GET;}
"camera" {return CAMERA;}
"true" {return B2C_TRUE;}
"false" {return B2C_FALSE;}
"error" {return ERROR;}
"sprite_get" {return SPRITE_GET;}
"findfile" {return FINDFILE;}
"nextfile" {return NEXTFILE;}
"filelist" {return FILELIST;}
"rect" {return RECT;}
"rectfill" {return RECTFILL;}
"page" {return PAGE;}
"pagecopy" {return PAGECOPY;}
"remove"	{return REMOVE;}
"rename"	{return RENAME;}
"exists"	{return EXISTS;}
"load"		{return LOAD;}
"len"		{return LEN;}
"stringwidth"	{return STRINGWIDTH;}
"stringheight"	{return STRINGHEIGHT;}
"wrap"			{return WRAP;}
"left"			{return LEFT;}
"center"		{return CENTER;}
"word"			{return WORD;}
"archive"		{return ARCHIVE;}
"3dsprites"		{return D3SPRITES;}
"3drooms"		{return D3ROOMS;}
"circle"		{return CIRCLE;}
"circfill"		{return CIRCFILL;}

"'".*"\n"	{return COMMENT;}
"." return '.';
\\[^\\\n]\\  {yacctext[0]=yytext[1]; yacctext[1]=0; return LITERAL_CHAR; }
{D}+	{strcpy(yacctext, yytext); return LITERAL_INT;}
{D}*\.{D}+		  {strcpy(yacctext, yytext); return LITERAL_DOUBLE;}
\"[^"\n]*\"	{strcpy(yacctext, yytext); return LITERAL_STRING;}
{A}{AN}* {strcpy(yacctext, yytext); return VAR;}
^"@"{AN}*\.{AN}* {strcpy(yacctext, yytext); return FILENAME;}
"+"	return '+';
"-"	return '-';
"*"	return '*';
"/"	return '/';
">"	return '>';
"<"	return '<';
">="	return GE;
"<="	return LE;
"("	return '(';
")"	return ')';
"["	return '[';
"]"	return ']';
"="	return '=';
","	return ',';
"@" return '@';
"\n"	return '\n';
"#"     return '#';
":"	return ':';
" "*"\n" {return '\n';}
.       {}
%%
