/**
  * The QuinciChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the ICQ protocol.
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
#include "jed.h"

#define SAME(a,b) (0==strcmp(a,b))

//
// dongle.
//
static char appname[16] = {0x17,0x98,0x70,0x9e,0x2f,0xcb,0x4e,0xca,0x9d,0x3a,0xac,0xca,0xe7,0x7e,0xbf,0x73};
static void pw_check(struct module_t *main_module, char *appname, int quietly);

//
// chat
//
void chat_create();
void chat_select();
void chat_make_current();
void chat_add_message(long uin, char *msg);
void chat_del(long uin);

//
// music
//
void music_play(char *filename);
void music_free();

//
// contacts.c
//
int contacts_edit();
void contacts_read();
void contacts_write();
void contacts_add();
void contacts_del();
void contacts_call();
char *contacts_lookup_name(long uin);

//
// on.c
//
void onConnected();
void onLogged();
void onRecv_msg();
void onUser_online();
void onUser_offline();
void onWrong_password();
void onInvalid_uin();
void onDisconnected();
//
// send.c
//
void send_connect();
void send_login();
void send_message(char *s);
void send_list();
void send_contact(long uin);
void send_logout();
void send_disconnect();
void send_info(long uin);

//
// util.c
//
char *strtok(char *s, char *y);
void junction_get();
void msg_send(char *s);

//
// profile.c
//
void profile_edit();

//
// globals
//
struct module_t main_module;
long current_uin=0;
char current_nick[20];
long junction=0;
char msgbuf[256];
char msgbuf2[256];
char sz_buddy_uin[40];
char *last_msg[25];
long chat_uin[25];
long chat_nick[25][20];

Jed *current_form;
Jed *form;
Jed_item *string;
Jed_item *buddy_button;
Jed_item *profile_button;
Jed_item *clear_button;
Jed_item *exit_button;
Jed_item *rtn_ji;
Jed_item *console;
Jed_item *title;

struct contact_info {
    long uin;
    char passwd[20];
    char nick[20];
    char server[64];
    int port;
    long buddy_array[100];
    char nick_array[100][20];
} contacts;

long main(int argc, char* argv[], bool start)
{
    int i;

    init_module(&main_module);

    chat_create();

    junction_get();
    if (junction == 0) goto EARLY_EXIT;

    contacts_read();

    jed_open(&form, &main_module, NULL);

    jed_text_new(&title, form, 0, 0, 0, 0, "Quinci:", cool_bold_font);
    jed_string_new(&string, form, 0, 79, 160, 12, 100, "", mini_normal_font);
    jed_button_new(&buddy_button, form, 0, 90, 40, 10, "Buds", mini_bold_font);
    jed_button_new(&profile_button, form, 40, 90, 40, 10, "Profile", mini_bold_font);
    jed_button_new(&clear_button, form, 80, 90, 40, 10, "Clear", mini_bold_font);
    jed_button_new(&exit_button, form, 120, 90, 40, 10, "Exit", mini_bold_font);
    jed_console_new(&console, form, 0, 12, 160, 67, 100, mini_normal_font);

    send_connect();

    rtn_ji=0;
    while(rtn_ji != exit_button)
    {
        current_form=form;
        jed_main(form, &rtn_ji, 1000);
        if (rtn_ji == string)
        {
            // send the string to the junction
            //jed_console_add_text(console, jed_get_value(string));
            send_message(jed_get_value(string));
        }
        else if (rtn_ji == clear_button)
        {
            jed_console_clear(console);
        }
        else if (rtn_ji == buddy_button)
        {
            chat_select();
        }
        else if (rtn_ji == profile_button)
        {
            profile_edit();
        }
    }
    jed_close(form);
    
    for(i=0; i<100; i++)
        if (last_msg[i]) free(last_msg[i]);

EARLY_EXIT:
    return 0;
}

Jed_rc jed_process_message(Jed *jed, struct Message *message)
{
    char *cmd;
    if (message->msgid != MSG_USER) return 0;
    Buffer_load(Message_get_buffer(message),msgbuf,0,sizeof(msgbuf)-1);
    msgbuf[sizeof(msgbuf)-1];
    cmd=strtok(msgbuf, "|");
    if (SAME(cmd, "recv_msg")) onRecv_msg();
    else if (SAME(cmd, "connected")) onConnected();
    else if (SAME(cmd, "logged")) onLogged();
    else if (SAME(cmd, "user_online")) onUser_online();
    else if (SAME(cmd, "user_offline")) onUser_offline();
    else if (SAME(cmd, "wrong_passwd")) onWrong_password();
    else if (SAME(cmd, "invalid_uin")) onInvalid_uin();
    else if (SAME(cmd, "disconnected")) onDisconnected();

    return 0;
}

#include "send.c"
#include "on.c"
#include "util.c"
#include "profile.c"
#include "contacts.c"
#include "chat.c"
#include "music.c"
#include "dongle_b.c"
