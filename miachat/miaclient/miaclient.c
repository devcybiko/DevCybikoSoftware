/**
  * The MiaChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the AIM protocol.
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
#include "FileListForm.h"

#define SAME(a,b) (0==stricmp(a,b))

//
// dongle.c
//
static char appname[16] = {0x17,0x98,0x70,0x9e,0x2f,0xcb,0x4e,0xca,0x9d,0x3a,0xac,0xca,0xe7,0x7e,0xbf,0x73};
static void pw_check(struct module_t *main_module, char *appname, int quietly);

//
// chat.c
//
void chat_create();
void chat_select();
void chat_make_current();
void chat_add_message(char *sn, char *msg);
void append_chat(int i, char *msg);
void append_user(char *sn, char *msg);

//
// music
//
void music_play(char *filename);
void music_free();

//
// contacts.c
//
int contacts_edit();
void contacts_call();
void contacts_add();
void contacts_del();
int contacts_read(char *fname);
void contacts_write();
void contacts_write2(char *fname);
void contacts_create();
void contacts_add_one(char *sn); // used when adding from main screen
int dialog_ok(char *title, char *text);
int dialog_show(char *title, char *text, char *rtn_s, int len);

//
// on.c
//
void onConnected();
void onRecv_msg();
void onUser_online();
void onUser_offline();
void remove_buddy_from_list(char *sn);
void onBad_password();

//
// send.c
//
void send_contact(char *sn);
void send_message(char *s);
void send_connect();
void send_logout();
void send_font();

//
// util.c
//
char *strtok(char *s, char *y);
void junction_get();
void msg_send(char *s);
int stricmp(char *s, char *t);

//
// profile.c
//
void profile_edit();

//
// fonts.c
//
int fonts_edit();

//
// miaclient.c
//
void refresh_buddy_list();
void cleanup();
void update_window(int i);
//
// globals
//
#define MAX_CHAT_NICKS 25
#define MAX_NICK_LEN 20
#define MAX_SERVER_LEN 64
#define MAX_BUDDIES 100
#define MAX_CHAT_BUFFER 1000

struct module_t main_module;
char current_buddy[MAX_NICK_LEN];
long junction=0;
char msgbuf[256];
char msgbuf2[256];

char *last_msg[MAX_CHAT_NICKS];
char chat_nick[MAX_CHAT_NICKS][MAX_NICK_LEN];
char awaiting_chat[MAX_CHAT_NICKS];

Jed *current_form;
Jed *form;
Jed_item *string;
Jed_item *buddy_list;
Jed_item *rtn_ji;
Jed_item *console;
Jed_item *title;

Jed *menu_form;
Jed_item *menu_list;

struct contact_info_1_2 {
    char sn[MAX_NICK_LEN];
    char passwd[MAX_NICK_LEN];
    char server[MAX_SERVER_LEN];
    int port;
    char nick_array[MAX_BUDDIES][MAX_NICK_LEN];
};

struct contact_info_2_0 {
    char sn[20];
    char passwd[20];
    char server[64];
    int port;
    char nick_array[MAX_BUDDIES][20];
    char prefix[10]; // used to prefix output so people know its cybiko
    char suffix[10]; // used to suffix output so people know its cybiko
    int fontname; // 1=times 2=arial 0=default
    int fontsize; // point size 0=default
    int bgcolor; //tbd
    int fgcolor;
} contacts;

long main(int argc, char* argv[], bool start)
{
    int i;
    char filename[32];

    current_buddy[0]=0;

    init_module(&main_module);

    chat_create();
    contacts_create();

    junction_get();
    if (junction == 0) goto EARLY_EXIT;

    jed_open(&form, &main_module, NULL);

    jed_text_new(&title, form, 0, 0, 0, 0, "MIA:", mini_bold_font);
    jed_string_new(&string, form, 0, 87, 160, 12, 100, "", mini_normal_font);
    jed_list_new(&buddy_list, form, 120, 10, 40, 78, MAX_BUDDIES, mini_normal_font);
    jed_console_new(&console, form, 0, 10, 120, 78, 100, mini_normal_font);

    jed_open(&menu_form, &main_module, mini_normal_font);
    jed_list_new(&menu_list, menu_form, 60,16,40,60,10, NULL);
    jed_list_add_item(menu_list, "Add");
    jed_list_add_item(menu_list, "Buds");
    jed_list_add_item(menu_list, "Profile");
    jed_list_add_item(menu_list, "Fonts");
    jed_list_add_item(menu_list, "Switch");
    jed_list_add_item(menu_list, "Exit");

    if (contacts_read("miaclient.dat"))
    {
        profile_edit();
    }
    contacts_write();
    if (filelist("Select Profile", "*.mia", filename, main_module.m_process))
    {
        int i;
        contacts_read(filename);
        contacts_write();
        send_connect();
        send_font();
    }
    else
    {
        goto EARLY_EXIT;
    }

    rtn_ji=0;
    while(rtn_ji == 0)
    {
        current_form=form;
        jed_main(form, &rtn_ji, 1000);
        if (rtn_ji == string)
        {
            // send the string to the junction
            //jed_console_add_text(console, jed_get_value(string));
            send_message(jed_get_value(string));
            rtn_ji = 0;
        }
        else if (rtn_ji == buddy_list)
        {
            int i;
            char *sn = jed_get_value(buddy_list);
            strcpy(current_buddy, sn);
            if (current_buddy[0] == '*') strcpy(current_buddy, current_buddy+1);
            sprintf(msgbuf2, "MIA: %s", current_buddy);
            jed_set_value(title, msgbuf2);
            jed_console_clear(console);
            for(i=0; last_msg[i]; i++)
            {
                if (0==stricmp(chat_nick[i],current_buddy))
                {
                    update_window(i);
                    awaiting_chat[i]=0;
                    refresh_buddy_list();
                    jed_repaint(current_form);
                    break;
                }
            }
            rtn_ji = 0;
        }
        else if (rtn_ji == console)
        {
            rtn_ji = 0;
        }
        else if (rtn_ji == 0)
        {
            jed_select(menu_list);
            jed_repaint_item(menu_list, TRUE);
            jed_main_ex(menu_form, &rtn_ji, 1000, 0); //dont repaint
            if (rtn_ji == menu_list)
            {
                char *option=jed_get_value(menu_list);

                rtn_ji = 0; // stay in the loop

                if (SAME(option, "Add"))
                {
                    if (current_buddy[0] == 0)
                    {
                        dialog_ok("Add Buddy", "You are not talking to anyone");
                    }
                    else
                    {
                        if (dialog_ok("Add Buddy", "Add the current buddy to your buddy list?"))
                        {
                            contacts_add_one(current_buddy);
                        }
                    }
                }
                else if (SAME(option, "Fonts"))
                {
                    fonts_edit();
                }
                else if (SAME(option, "Buds"))
                {
                    contacts_edit();
                }
                else if (SAME(option, "Profile"))
                {
                    profile_edit();
                }
                else if (SAME(option, "Switch"))
                {
					char filename[32];
                    if (filelist("Select Profile", "*.mia", filename, main_module.m_process))
                    {
                        int i;
                        send_logout();
                        contacts_read(filename);
                        contacts_write();
                        
                        jed_list_clear(buddy_list);
                        current_buddy[0]=0;
                        for(i=0; last_msg[i]; i++)
                        {
                            chat_nick[i][0] = 0;
                            awaiting_chat[i]=0;
                            free(last_msg[i]);
                            last_msg[i]=0;
                        }
                        send_connect();
                        send_font();
                    }
                }
                else if (SAME(option, "Exit"))
                {
                    break; //exit program
                }
            }
        }
    }

EARLY_EXIT:
    cleanup();
    send_logout();
    return 0;
}

Jed_rc jed_process_message(Jed *jed, struct Message *message)
{
    char *cmd;
    if (message->msgid != MSG_USER) return 0;
    Buffer_load(Message_get_buffer(message),msgbuf,0,sizeof(msgbuf)-1);
    msgbuf[sizeof(msgbuf)-1]=0;
    cmd=strtok(msgbuf, "|");
    if (SAME(cmd, "recv_msg")) onRecv_msg();
    else if (SAME(cmd, "connected")) onConnected();
    else if (SAME(cmd, "user_online")) onUser_online();
    else if (SAME(cmd, "user_offline")) onUser_offline();
    else if (SAME(cmd, "bad_password")) onBad_password();
    return 0;
}

void refresh_buddy_list()
{
    int i;
    jed_list_clear(buddy_list);
    for(i=0; chat_nick[i][0]; i++)
    {
        char tmp[32];
        if (awaiting_chat[i])
        {
            strcpy(tmp, "*");
        }
        else
        {
            strcpy(tmp, "");
        }
        strcat(tmp, chat_nick[i]);
        jed_list_add_item(buddy_list, tmp);
    }
    jed_set_value(buddy_list, current_buddy);
}

void update_window(int i)
{
    char *s;
    jed_console_clear(console);

    for(s=last_msg[i]; *s; s=s+strlen(s)+1)
    {
        jed_console_add_text(console, s);
    }
}

#include "send.c"
#include "on.c"
#include "util.c"
#include "profile.c"
#include "contacts.c"
#include "chat.c"
#include "music.c"
#include "dongle_b.c"
#include "fonts.c"

void cleanup()
{
    int i;

    if (form) jed_close(form);
    if (menu_form) jed_close(menu_form);
    if (contact_form) jed_close(contact_form);
    if (chat_form) jed_close(chat_form);
    if (profile_form) jed_close(profile_form);
    if (fonts_form) jed_close(fonts_form);
    
    for(i=0; i<MAX_BUDDIES; i++)
        if (last_msg[i]) free(last_msg[i]);
}
