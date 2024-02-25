/***************************************************
/* Program translated by b2c Version 3d
/* b2c (C) Copyright 2001 The Alcor Group, Inc
/* Written by Greg Smith
/*
/* Program mc.tmp converted Sat Nov 10 23:29:24 2001
/****************************************************/
#include "b2cuser.h"
int _true=1;
int _true_=1;
int _false_=0;
int _c_coords=1;
int _n_sprites=32;
int error=0;
int _show_=0;
double  msg_player_add_player;
double  msg_player_buzzed_in;
double  msg_mc_player_added;
double  msg_mc_player_refused;
double  msg_mc_lockout;
double  msg_mc_recognized;
double  msg_mc_rejoined;
double  msg_mc_reset;
double  msg_mc_timer;
double  msg_mc_high_score;
double  msg_mc_score;
double  msg_mc_gameover;
double  msg_mc_winner;
double  msg_mc_standby;
double  msg_mc_right;
double  msg_mc_wrong;
long  player;
int  nplayers;
long players[8];
short __players=8;
long points[8];
short __points=8;
int locked_out[8];
short __locked_out=8;
char names[8][20];
char tmp[64];
short __tmp=64;
char status[64];
short __status=64;
int  winner;
long  my_cyid;
char my_name[20];
short __my_name=20;
long  nsecs;
long  last_secs;
int  state;
int  countdown_reset;
int  question_reset;
int  question_timer;
long  question_points;
int  getpoints;
int  gameover;
int  waiting;
int  buzzing;
int  correct;
int  incorrect;
int  reset;
int  joining;
extern void msg_init();
extern int sort(int who);
extern void timer();
extern void add_player(long cyid, char *buf);
extern int lookup_player(long cyid, char *name);
extern void player_buzzed_in(long cyid, char *buf);
extern void onmessage(long cyid, int msgno, char *buf);
extern void high_score();
extern void add_points(int x, long amount);
extern void init();
extern void repaint();
extern void do_nothing();
extern void do_reset();
extern void do_getpoints();
extern void do_waiting();
extern void do_buzzing();
extern void do_correct();
extern void do_incorrect();
extern void do_joining();
extern void mainsub();
void msg_init()
{
msg_player_add_player=101;
msg_player_buzzed_in=102;
msg_mc_player_added=201;
msg_mc_player_refused=202;
msg_mc_lockout=203;
msg_mc_recognized=204;
msg_mc_rejoined=205;
msg_mc_reset=206;
msg_mc_timer=207;
msg_mc_high_score=208;
msg_mc_score=209;
msg_mc_gameover=210;
msg_mc_winner=211;
msg_mc_standby=212;
msg_mc_right=213;
msg_mc_wrong=214;
return;
}
int sort(int who)
{
int _sort=0;
int  swap;
long  ptmp;
swap=_true_;
while(swap) {
swap=_false_;
if (who>0)
{
if (points[who]>points[who-1])
{
ptmp=points[who-1];
points[who-1]=points[who];
points[who]=ptmp;
strcpy(tmp,names[who-1]);
strcpy(names[who-1],names[who]);
strcpy(names[who],tmp);
ptmp=players[who-1];
players[who-1]=players[who];
players[who]=ptmp;
swap=_true_;
who=who-1;
}
}
if (who<nplayers-1)
{
if (points[who]<points[who+1])
{
ptmp=points[who];
points[who]=points[who+1];
points[who+1]=ptmp;
strcpy(tmp,names[who]);
strcpy(names[who],names[who+1]);
strcpy(names[who+1],tmp);
ptmp=players[who];
players[who]=players[who+1];
players[who+1]=ptmp;
swap=_true_;
who=who+1;
}
}
}
_sort=who;
return _sort;
}
void timer()
{
long  now;
/**/now=clock();
if (now-last_secs<5000)
{
return;
}
;
last_secs=now;
nsecs=nsecs-5;
_sprint(tmp, "%ld",nsecs);
_msg_send(-1,msg_mc_timer,"player",tmp);
repaint();
if (nsecs==0)
{
_msg_send(-1,msg_mc_gameover,"player","");
_msg_send(players[0],msg_mc_winner,"player","");
}
return;
}
void add_player(long cyid, char *buf)
{
int  x;
long  time_value;
int  i;
i=0;
while(_true) {
int _incr01 = 1;
if (_incr01<0 && i<nplayers-1) break;
if (_incr01>0 && i>nplayers-1) break;
if (players[i]==cyid)
{
_sprint(tmp, "%ld",points[i]);
_msg_send(cyid,msg_mc_rejoined,"player",tmp);
return;
}
_incr01=1;
i+=_incr01;
}
if (nplayers==8)
{
_msg_send(cyid,msg_mc_player_refused,"player","Sorry, there are too many players");
return;
}
strcpy(names[nplayers],buf);
_sprint(tmp, "%s%s",names[nplayers]," Would like to play");
x=_dialog("MC",tmp,NULL,0);
if (x==_false_)
{
_msg_send(cyid,msg_mc_player_refused,"player","Sorry, you were refused");
return;
}
players[nplayers]=cyid;
points[nplayers]=0;
locked_out[nplayers]=_false_;
_msg_send(cyid,msg_mc_player_added,"player","");
nplayers=nplayers+1;
strcpy(status,buf);
sort(nplayers-1);
return;
}
int lookup_player(long cyid, char *name)
{
int _lookup_player=0;
int  i;
i=0;
while(_true) {
int _incr01 = 1;
if (_incr01<0 && i<nplayers-1) break;
if (_incr01>0 && i>nplayers-1) break;
if (cyid==players[i])
{
_lookup_player=i;
strcpy(name,names[i]);
return _lookup_player;
}
_incr01=1;
i+=_incr01;
}
_lookup_player=10;
return _lookup_player;
}
void player_buzzed_in(long cyid, char *buf)
{
int  x;
char name[20];
short __name=20;
strcpy(status,buf);
x=lookup_player(cyid,name);
if (x==10)
{
_beep(10);
_wait(5);
_beep(-1);
}
else {
if (locked_out[x]==_false_)
{
winner=x;
_msg_send(cyid,msg_mc_recognized,"player","");
_msg_send(-1,msg_mc_lockout,"player",names[winner]);
state=buzzing;
}
}
return;
}
void onmessage(long cyid, int msgno, char *buf)
{
if (msgno==msg_player_add_player)
{
add_player(cyid,buf);
}
;
if (msgno==msg_player_buzzed_in)
{
player_buzzed_in(cyid,buf);
}
;
return;
}
void high_score()
{
_sprint(tmp, "%s%s%ld",names[0],"|",points[0]);
_msg_send(-1,msg_mc_high_score,"player",tmp);
return;
}
void add_points(int x, long amount)
{
points[x]=points[x]+amount;
_sprint(tmp, "%ld",points[x]);
_msg_send(players[x],msg_mc_score,"player",tmp);
winner=sort(x);
high_score();
return;
}
void init()
{
double  a;
char secs[10];
short __secs=10;
getpoints=0;
gameover=1;
waiting=2;
buzzing=3;
correct=4;
incorrect=5;
reset=6;
joining=7;
nplayers=0;
players[nplayers]=0;
/**/my_cyid = get_own_id();
/**/strcpy(my_name,finder.mf.f_nick);
strcpy(secs,"10");
a=_dialog("MC","How many minutes?",secs,10);
/**/countdown_reset=atoul(secs)*60;
strcpy(secs,"10");
a=_dialog("MC","Question Timeout (secs)?",secs,10);
/**/question_reset=atoul(secs);
a=_dialog("MC","PRESS ENTER TO BEGIN!",NULL,0);
state=joining;
return;
}
void repaint()
{
int  y;
int  i;
_ink(3);
_paper(1);
_cls();
if (state==waiting)
{
_font("cool_bold_font");
_printxy(1,1,"%ld\n",nsecs);
_font("mini_normal_font");
i=0;
while(_true) {
int _incr01 = 1;
if (_incr01<0 && i<nplayers-1) break;
if (_incr01>0 && i>nplayers-1) break;
y=i*10;
_printxy(80,y,"%s\n",names[i]);
_printxy(120,y,"%ld\n",points[i]);
_incr01=1;
i+=_incr01;
}
}
if (state==joining)
{
_font("cool_bold_font");
_printxy(1,1,"%s\n","JOINING...");
_font("mini_normal_font");
i=0;
while(_true) {
int _incr01 = 1;
if (_incr01<0 && i<nplayers-1) break;
if (_incr01>0 && i>nplayers-1) break;
y=i*10;
_printxy(80,y,"%s\n",names[i]);
_printxy(120,y,"%ld\n",points[i]);
_incr01=1;
i+=_incr01;
}
}
if (state==buzzing)
{
_font("cool_bold_font");
_printxy(80,50,"%s%s\n",names[winner],"!");
_printxy(1,1,"%d\n",question_timer);
}
if (state==correct)
{
_font("cool_bold_font");
_printxy(80,50,"%s%s%ld\n",names[winner]," : ",points[i]);
}
if (state==incorrect)
{
_font("cool_bold_font");
_printxy(80,50,"%s%s%ld\n",names[winner]," : ",points[i]);
}
if (state==reset)
{
_font("cool_bold_font");
_printxy(80,50,"%s\n","Next Question");
}
if (state==gameover)
{
_font("cool_bold_font");
_printxy(80,50,"%s\n","GAME OVER");
}
if (state==getpoints)
{
_font("cool_bold_font");
_printxy(80,50,"%s\n","GET POINTS");
}
_redraw(-2);
return;
}
void do_nothing()
{
state=state;
return;
}
void do_reset()
{
int  i;
_msg_send(-1,msg_mc_reset,"player","");
i=0;
while(_true) {
int _incr01 = 1;
if (_incr01<0 && i<nplayers-1) break;
if (_incr01>0 && i>nplayers-1) break;
locked_out[i]=_false_;
_incr01=1;
i+=_incr01;
}
state=getpoints;
return;
}
void do_getpoints()
{
int  a;
char pts[10];
short __pts=10;
_msg_send(-1,msg_mc_standby,"player","");
strcpy(pts,"100");
a=_dialog("MC","Points",pts,10);
/**/question_points=atoul(pts);
do_reset();
state=waiting;
repaint();
return;
}
void do_waiting()
{
if (_key(KEY_SPACE))
{
state=reset;
}
return;
}
void do_buzzing()
{
double  a;
_sprint(tmp, "%s%s",names[winner]," Buzzed In - OK=Right Cancel=Wrong");
a=_dialog("MC",tmp,NULL,0);
if (a==0)
{
state=incorrect;
}
else {
state=correct;
}
return;
}
void do_correct()
{
add_points(winner,question_points);
_msg_send(players[winner],msg_mc_right,"player","");
state=getpoints;
return;
}
void do_incorrect()
{
int  i;
add_points(winner,-question_points);
locked_out[winner]=_true_;
i=0;
while(_true) {
int _incr01 = 1;
if (_incr01<0 && i<nplayers-1) break;
if (_incr01>0 && i>nplayers-1) break;
if (locked_out[i]&&i!=winner)
{
_msg_send(players[i],msg_mc_lockout,"player","");
}
else {
_msg_send(players[i],msg_mc_reset,"player","");
}
_incr01=1;
i+=_incr01;
}
_msg_send(players[winner],msg_mc_wrong,"player","");
state=waiting;
return;
}
void do_joining()
{
while(!_key(KEY_ENTER)) {
/**/_escape(0);
repaint();
_wait(5);
}
state=getpoints;
return;
}
void mainsub()
{
init();
nsecs=countdown_reset;
repaint();
while(_true_) {
/**/_escape(0);
timer();
if (state==joining)
{
do_joining();
}
;
if (state==getpoints)
{
do_getpoints();
}
;
if (state==waiting)
{
do_waiting();
}
;
if (state==buzzing)
{
do_buzzing();
}
;
if (state==correct)
{
do_correct();
}
;
if (state==incorrect)
{
do_incorrect();
}
;
if (state==reset)
{
do_reset();
}
;
}
return;
}
main() {
TRACE("Created by B2C Version 3d");
_init_b2c();
msg_init();
last_secs=0;
mainsub();
_destroy_b2c();
return 0;
}
