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
#define NSECS 5
//#define DBG0 TRACE
#define DBG0 stub

static void stub(char *s, ...){}

void _msg_send2(long cyid, int msgno, char *appname, char *buffer)
{
	send_remote_msg(cyid, appname, msgno+MSG_USER, 
		0, 0, buffer, strlen(buffer)+1);
}

void _msg_send(long cyid, int msgno, char *appname, char *buffer)
{
	send_remote_msg(cyid, appname, msgno+MSG_USER, 0, 0, buffer, strlen(buffer)+1);
}

static void _msg_send_old(long cyid, int msgno, char *appname, char *buffer)
{
    delivery_t delivery;
    int i, j;
	int len = strlen(buffer)+1;
    struct Message *message;
    struct Buffer *message_buffer;
    int rc = 0;
	int _true_ = 1;

	DBG0("Cyid=%ld Msgno=%d Appname=%s", cyid, msgno, appname);

    message = Message_new(sizeof(struct Message));
    message->msgid = MSG_USER+msgno;

    message_buffer = (struct Buffer *)malloc(sizeof(struct Buffer));
    Buffer_ctor(message_buffer, len, len);
    Buffer_store(message_buffer, buffer, 0, len);
    Message_attach_buffer(message, message_buffer);

    Message_deliver(message, appname, cyid, NSECS*1000);

    j=0;
    for(delivery = Message_check_delivery(message);
        _true_; // loop forever
        delivery = Message_check_delivery(message))
    {
        j++;
        switch(delivery)
        {
        //  Message was not delivered to the chat partner.
            case DL_ABORT: DBG0("DL_ABORT"); i=0; break;
            case DL_TIMEOUT: DBG0("DL_TIMEOUT"); i=0; break;
            case DL_INQUEUE: DBG0("DL_INQUEUE"); i=1; break; // keep waiting
            case DL_WAIT: DBG0("DL_WAIT"); i=1; break; //keep waiting
            case DL_SUCCESS: DBG0("DL_SUCCESS"); i=0; break;
            default: i=1; break; //keep waiting
        }
        if (i==0) break;
        else cWinApp_pause(b2c->main_module.m_process, 125 );
        if (j > (NSECS)*8)
        {
            DBG0("ARTIFICIAL TIMEOUT\n");
            break;
        }
    }
    Message_delete(message);

    DBG0("<cybiko_send_message\n");
}

long _user_menu(char *caption, long *skip)
{
	long cyid;
	long tmp[1];
	char nickname[64];

	tmp[0] = 0;
	
	if (skip)
	{
		cyid = select_partner_Ex(
			b2c->main_module.m_process,
			SGP_NONE,
			nickname,
			caption,
			skip);
	}
	else
	{
		cyid = select_partner_Ex(
			b2c->main_module.m_process,
			SGP_NONE,
			nickname,
			caption,
			tmp);
	}
	return cyid;
}

long _tocyid(char *name)
{
	int i;

	for(i=0; i<finder.howmany_around; i++)
	{
		if (SAME(finder.cf[i].cf_fk.f_nick, name))
			return finder.cf[i].cf_id;
	}
	return 0;
}

char *_touser(long cyid)
{
	int i;

	for(i=0; i<finder.howmany_around; i++)
	{
		if (finder.cf[i].cf_id == cyid)
			return finder.cf[i].cf_fk.f_nick;
	}
	return 0;
}