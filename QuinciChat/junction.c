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
#include "quincichat.h"

// logging messages handed us by icq
static void my_Log(icq_Link *icqlink, time_t log_time, unsigned char level, const char *str)
{
	DBG("\nLOG: %s", str);
}

static void my_RecvMessage(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, const char *msg)
{
	HANDLE tty;
	char tmp[1024];

	DBG(">my_RecvMessage\n");
	DBG("...%ld: %s\n", uin, msg);
	sprintf(tmp, "recv_msg|%ld|%d|%d|%d|%d|%d|%s",
		uin, hour, minute, day, month, year, msg);
	tty = icqlink->icq_UserData;
	serial_send(tty, tmp);
	DBG("<my_RecvMessage\n");
}

//
static void my_Logged(icq_Link *icqlink)
{
	HANDLE tty = icqlink->icq_UserData;
	DBG(">my_>Logged\n");
	serial_send(tty, "logged");
	DBG("<my_>Logged\n");
}

//
// a whole bunch of stubs for callbacks
//
static void my_Disconnected(icq_Link *icqlink)
{
	HANDLE tty = icqlink->icq_UserData;
	DBG(">my_Disconnected\n");
	serial_send(tty, "disconnected");
	DBG("<my_Disconnected\n");
}

static void my_RecvURL(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, const char *url,
       const char *descr)
{printf("my_RecvURL\n");}

static void my_RecvContactList(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, int nr,
       const char **contact_uin, const char **contact_nick)
{printf("my_RecvContactList\n");}

static void my_RecvWebPager(icq_Link *icqlink,unsigned char hour,
       unsigned char minute, unsigned char day, unsigned char month,
       unsigned short year, const char *nick, const char *email,
       const char *msg)
{printf("my_RecvWebPager\n");}

static void my_RecvMailExpress(icq_Link *icqlink,unsigned char hour,
       unsigned char minute, unsigned char day, unsigned char month,
       unsigned short year, const char *nick, const char *email,
       const char *msg)
{printf("my_RecvMailExpress\n");}

static void my_RecvChatReq(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, const char *descr,
       unsigned long seq)
{printf("my_RecvChatReq\n");}

static void my_RecvFileReq(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, const char *descr,
       const char *filename, unsigned long filesize, unsigned long seq)
{printf("my_RecvFileReq\n");}

static void my_RecvAdded(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, const char *nick,
       const char *first, const char *last, const char *email)
{printf("my_RecvAdded\n");}

static void my_RecvAuthReq(icq_Link *icqlink, unsigned long uin,
       unsigned char hour, unsigned char minute, unsigned char day,
       unsigned char month, unsigned short year, const char *nick,
       const char *first, const char *last, const char *email,
       const char *reason)
{printf("my_RecvAuthReq\n");}

static void my_UserFound(icq_Link *icqlink, unsigned long uin,
       const char *nick, const char *first, const char *last,
       const char *email, char auth)
{printf("my_UserFound\n");}

static void my_SearchDone(icq_Link *icqlink)
{printf("my_SearchDone\n");}

static void my_UpdateSuccess(icq_Link *icqlink)
{printf("my_UpdateSuccess\n");}

static void my_UpdateFailure(icq_Link *icqlink)
{printf("my_UpdateFailure\n");}

static void my_UserOnline(icq_Link *icqlink, unsigned long uin,
       unsigned long status, unsigned long ip, unsigned short port,
       unsigned long real_ip, unsigned char tcp_flag )
{
	char tmp[256];
	HANDLE tty = icqlink->icq_UserData;
	DBG("my_UserOnline\n");
	sprintf(tmp, "user_online|%ld|%ld|%08x|%d|%08x|%d",
		uin, status, ip, port, real_ip, tcp_flag);
	serial_send(tty, tmp);
}

static void my_UserOffline(icq_Link *icqlink, unsigned long uin)
{
	HANDLE tty = icqlink->icq_UserData;
	char tmp[256];
	DBG("my_UserOffline\n");
	sprintf(tmp, "user_offline|%ld", uin);
	serial_send(tty, tmp);
}

static void my_UserStatusUpdate(icq_Link *icqlink, unsigned long uin,
       unsigned long status)
{printf("my_UserStatusUpdate\n");}

static void my_RecvAwayMsg(icq_Link *icqlink, unsigned long id,
       const char *msg)
{printf("my_RecvAwayMsg\n");}

static void my_InfoReply(icq_Link *icqlink, unsigned long uin,
       const char *nick, const char *first, const char *last,
       const char *email, char auth)
{
	char tmp[256];
	HANDLE tty;
	printf("my_InfoReply\n");
	sprintf(tmp, "info_reply|%ld|%s|%s|%s|%s|%d", uin, nick, first, last, email, auth);
	tty = icqlink->icq_UserData;
	serial_send(tty, tmp);
}

static void my_ExtInfoReply(icq_Link *icqlink, unsigned long uin,
       const char *city, unsigned short country_code, char country_stat,
       const char *state, unsigned short age, char gender,
       const char *phone, const char *hp, const char *about)
{printf("my_ExtInfoReply\n");}

static void my_WrongPassword(icq_Link *icqlink)
{
	HANDLE tty = icqlink->icq_UserData;
	DBG("my_WrongPassword\n");
	serial_send(tty, "wrong_passwd");
}

static void my_InvalidUIN(icq_Link *icqlink)
{
	HANDLE tty = icqlink->icq_UserData;
	DBG("my_InvalidUIN\n");
	serial_send(tty, "invalid_uin");
}

static void my_SrvAck(icq_Link *icqlink, unsigned short seq)
{printf("my_SrvAck\n");}

static void my_RequestNotify(icq_Link *icqlink, unsigned long id, 
       int type, int arg, void *data)
{DBG("my_RequestNotify id=%d type=%d arg=%d data=%s\n", id, type, arg, data);}

static void my_FileNotify(icq_FileSession *session, int type, int arg,
     void *data)
{printf("my_FileNotify\n");}

static void my_ChatNotify(icq_ChatSession *session, int type, int arg,
     void *data)
{printf("my_ChatNotify\n");}

static void my_NewUIN(icq_Link *icqlink, unsigned long uin)
{printf("my_NewUIN uin=%ld\n", uin);}

static void my_MetaUserFound(icq_Link *icqlink, unsigned short seq2,
       unsigned long uin, const char *nick, const char *first,
       const char *last, const char *email, char auth)
{printf("my_MetaUserFound\n");}

static void my_MetaUserInfo(icq_Link *icqlink, unsigned short seq2,
       const char *nick, const char *first, const char *last,
       const char *pri_eml, const char *sec_eml, const char *old_eml,
       const char *city, const char *state, const char *phone, const char *fax,
       const char *street, const char *cellular, unsigned long zip,
       unsigned short country, unsigned char timezone, unsigned char auth,
       unsigned char webaware, unsigned char hideip)
{printf("my_MetaUserInfo\n");}

static void my_MetaUserWork(icq_Link *icqlink, unsigned short seq2,
       const char *wcity, const char *wstate, const char *wphone,
       const char *wfax, const char *waddress, unsigned long wzip,
       unsigned short wcountry, const char *company, const char *department,
       const char *job, unsigned short occupation, const char *whomepage)
{printf("my_MetaUserWork\n");}

static void my_MetaUserMore(icq_Link *icqlink, unsigned short seq2,
       unsigned short age, unsigned char gender, const char *homepage,
       unsigned char byear, unsigned char bmonth, unsigned char bday,
       unsigned char lang1, unsigned char lang2, unsigned char lang3)
{printf("my_MetaUserMore\n");}

static void my_MetaUserAbout(icq_Link *icqlink, unsigned short seq2,
       const char *about)
{printf("my_MetaUserAbout\n");}

static void my_MetaUserInterests(icq_Link *icqlink, unsigned short seq2,
       unsigned char num, unsigned short icat1, const char *int1,
       unsigned short icat2, const char *int2, unsigned short icat3,
       const char *int3, unsigned short icat4, const char *int4)
{printf("my_MetaUserInterests\n");}

static void my_MetaUserAffiliations(icq_Link *icqlink, unsigned short seq2,
       unsigned char anum, unsigned short acat1, const char *aff1,
       unsigned short acat2, const char *aff2, unsigned short acat3,
       const char *aff3, unsigned short acat4, const char *aff4,
       unsigned char bnum, unsigned short bcat1, const char *back1,
       unsigned short bcat2, const char *back2, unsigned short bcat3,
       const char *back3, unsigned short bcat4, const char *back4)
{printf("my_MetaUserAffiliations\n");}

static void my_MetaUserHomePageCategory(icq_Link *icqlink,
       unsigned short seq2, unsigned char num, unsigned short hcat1,
       const char *htext1)
{printf("my_MetaUserHomePageCategory\n");}

//
// setup the callbacks
//
static void setup_callbacks(icq_Link *icqlink)
{
	icqlink->icq_Log=my_Log;
	icqlink->icq_RecvMessage=my_RecvMessage;
	icqlink->icq_Logged=my_Logged;
	icqlink->icq_Disconnected=my_Disconnected;
	icqlink->icq_RecvMessage=my_RecvMessage;
	icqlink->icq_RecvURL=my_RecvURL;
	icqlink->icq_RecvContactList=my_RecvContactList;
	icqlink->icq_RecvWebPager=my_RecvWebPager;
	icqlink->icq_RecvMailExpress=my_RecvMailExpress;
	icqlink->icq_RecvChatReq=my_RecvChatReq;
	icqlink->icq_RecvFileReq=my_RecvFileReq;
	icqlink->icq_RecvAdded=my_RecvAdded;
	icqlink->icq_RecvAuthReq=my_RecvAuthReq;
	icqlink->icq_UserFound=my_UserFound;
	icqlink->icq_SearchDone=my_SearchDone;
	icqlink->icq_UpdateSuccess=my_UpdateSuccess;
	icqlink->icq_UpdateFailure=my_UpdateFailure;
	icqlink->icq_UserOnline=my_UserOnline;
	icqlink->icq_UserOffline=my_UserOffline;
	icqlink->icq_UserStatusUpdate=my_UserStatusUpdate;
	icqlink->icq_RecvAwayMsg=my_RecvAwayMsg;
	icqlink->icq_InfoReply=my_InfoReply;
	icqlink->icq_ExtInfoReply=my_ExtInfoReply;
	icqlink->icq_WrongPassword=my_WrongPassword;
	icqlink->icq_InvalidUIN=my_InvalidUIN;
	icqlink->icq_SrvAck=my_SrvAck;
	icqlink->icq_RequestNotify=my_RequestNotify;
	icqlink->icq_FileNotify=my_FileNotify;
	icqlink->icq_ChatNotify=my_ChatNotify;
	icqlink->icq_NewUIN=my_NewUIN;
	icqlink->icq_MetaUserFound=my_MetaUserFound;
	icqlink->icq_MetaUserInfo=my_MetaUserInfo;
	icqlink->icq_MetaUserWork=my_MetaUserWork;
	icqlink->icq_MetaUserMore=my_MetaUserMore;
	icqlink->icq_MetaUserAbout=my_MetaUserAbout;
	icqlink->icq_MetaUserInterests=my_MetaUserInterests;
	icqlink->icq_MetaUserAffiliations=my_MetaUserAffiliations;
	icqlink->icq_MetaUserHomePageCategory=my_MetaUserHomePageCategory;
}

//
// windows socket stuff
//
void my_socket_init()
{
	WSADATA wsaData;
	int rc;

	if((rc=WSAStartup( MAKEWORD(2,0), &wsaData )))
	{
		perror("Sorry, can't initialize Windows Sockets...");
		printf("Error code=%d", rc);
		exit(1);
	}
}

#define SEPARATOR "|"

void junction_dispatch(HANDLE tty, icq_Link **picqlink, char *buf)
{
	char *cmd;
	char *tmp;
	icq_Link *icqlink=*picqlink;
	int rc;
	long uin;

	DBG(">junction_dispatch\n");
	DBG("...recv %s\n", buf);

	cmd = strtok(buf, SEPARATOR);
	DBG("...cmd=%s\n", cmd);
	if (cmd == 0) goto EARLY_EXIT;

	if (SAME(cmd, "connect"))
	{
		char *passwd;
		char *nick;
		char *server;
		int port;

		//serial_send(tty, "ack|connect");
		tmp = strtok(NULL, SEPARATOR);
		uin=atol(tmp);
		passwd = strtok(NULL, SEPARATOR);
		nick=strtok(NULL, SEPARATOR);
		server=strtok(NULL, SEPARATOR);
		tmp = strtok(NULL, SEPARATOR);
		port = atoi(tmp);

		my_socket_init(); // init the windows sockets
		icqlink = icq_LinkNew(uin,  passwd, nick, TRUE); //create a link with TCP sockets
DBG("uin=%ld, passwd=%s, nick=%s\n", uin, passwd, nick);

		setup_callbacks(icqlink); //setup callbacks
	
		rc = icq_Connect(icqlink, server, port);  // conect to icq
DBG("server=%s port=%d\n", server, port);

		DBG("...rc=%d (udp port)\n", rc);
		serial_send(tty, "connected");
		icqlink->icq_UserData = tty;
		*picqlink = icqlink;
		goto EARLY_EXIT;
	}
	else if (SAME(cmd, "login"))
	{
		//serial_send(tty, "ack|login");
DBG("Logging In...\n");
		icq_Login(icqlink, STATUS_ONLINE); // login online status
	}
	else if (SAME(cmd, "logout"))
	{
		//serial_send(tty, "ack|login");
DBG("Logging Out...\n");
		icq_Logout(icqlink); // login online status
	}
	else if (SAME(cmd, "contact_add"))
	{
		//serial_send(tty, "ack|contact_add");
		tmp = strtok(NULL, SEPARATOR);
		uin=atoi(tmp);
		icq_ContactAdd(icqlink, uin);
	}
	else if (SAME(cmd, "send_list"))
	{
		//serial_send(tty, "ack|send_list");
		icq_SendContactList(icqlink);
	}
	else if (SAME(cmd, "send_msg"))
	{
		//serial_send(tty, "ack|send_msg");
		tmp=strtok(NULL, SEPARATOR);
		uin=atoi(tmp);
		tmp=strtok(NULL, SEPARATOR);
//		rc=icq_TCPSendMessage(icqlink, uin, tmp);
		rc=icq_SendMessage(icqlink, uin, tmp, ICQ_SEND_BESTWAY);
//		rc=icq_SendMessage(icqlink, uin, tmp, ICQ_SEND_THRUSERVER);
//		rc=icq_SendMessage(icqlink, uin, tmp, ICQ_SEND_DIRECT);
	}
	else if (SAME(cmd, "send_info"))
	{
printf("send_info\n");
		tmp=strtok(NULL, SEPARATOR);
		uin=atoi(tmp);
		rc=icq_SendInfoReq(icqlink, uin);
	}

EARLY_EXIT:
	return;
}
