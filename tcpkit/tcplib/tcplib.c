/**
  * The TCPKIT framework is a set of programs and libraries
  * that allow a set of Cybiko computers to communicate on
  * the internet.
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
#include <cybiko.h>
#include "tcplib.h"
#include "../tcpmsgs.h"
#include "tcperror.h"
#include "..\..\dongle\dongle_c.c"

/***
 *** IMPORTANT NOTE:
 *** the name "tcpqueue" in the client code refers to an index
 *** into the struct tcpqueues[] array.  This is a number from
 *** 0 - TCP_MAX_TCPQUEUES-1
 ***
 *** This is different than on the TCPGate side.  On that side
 *** "tcpqueue" is the Cybiko Message queue number which is
 *** MSG_TCP - MSG_TCP+63 (8448 - 8481)
 ***
 ***/
static struct module_t *tcp_main_module=0;
static long tcp_junction=0;
static struct tcpqueue_t {
	long sockid;
	TCP_Msg_Handler handler;
	char *user_data;
} tcpqueues[TCP_MAX_TCPQUEUES];

long tcp_errno;
long tcp_timeout=1000;
long tcp_serialno=0;

//extern void printf(char *s);
//#define DBG printf
#define DBG NULL_PRINTF

void NULL_PRINTF(char *s) {}

#define TCPJUNCTION_NAME "tcpjunction"

long tcp_init(struct module_t *main_module)
{
    long tmp[1];
    char nickname[32];

	DBG("tcp_init");

	pw_check(main_module, 0);
	tcp_errno = 0;
	tcp_serialno = 0;
	tcp_main_module = main_module;
	memset(tcpqueues, 0, sizeof(tcpqueues));
                                                 
    tmp[0] = 0;
    tcp_junction = select_partner_Ex(
        tcp_main_module->m_process,
        SGP_NONE,
        nickname,
        "SELECT TCP JUNCTION",
        tmp);
	return tcp_junction;
}

static int alloc_tcpqueue()
{
	int i;

	for(i=1; i<TCP_MAX_TCPQUEUES; i++)
	{
		if (tcpqueues[i].sockid == 0)
			return i;
	}
	return 0;
}

static int free_tcpqueue(long tcpqueue)
{
	tcpqueues[tcpqueue].sockid = 0;
}

long tcp_connect(char *addr, long port, long size, TCP_Cybiko_Handler handler, char *user_data)
{
	int connect_len = sizeof(struct tcpcg_connect_request)+strlen(addr)+1;
	struct tcpcg_connect_request *connect = malloc(connect_len);
	bool rc;
	int return_tcpqueue=0;
	long buflen;

	tcp_errno = 0;

	DBG("tcp_connect");

	if (tcp_main_module == 0) 
	{
		tcp_errno = TCP_ERROR_UNINITIALIZED;
		goto EARLY_EXIT;
	}

	connect->hdr.serialno = ++tcp_serialno;
	connect->hdr.sockid = 0;
    connect->hdr.msgid = TCPMSG_CONNECT_REQUEST;

	connect->cyid=get_own_id();
	return_tcpqueue = alloc_tcpqueue(handler, user_data);
	if (return_tcpqueue == 0) 
	{
		tcp_errno = TCP_ERROR_NO_MORE_CLIENT_MSGQUEUES;
		goto EARLY_EXIT;
	}

	tcpqueues[return_tcpqueue].handler = handler;
	tcpqueues[return_tcpqueue].user_data = user_data;

    connect->tcpqueue = MSG_TCP + return_tcpqueue;
	strcpy(connect->appname, Process_get_name( tcp_main_module->m_process ));
	strcpy(connect->addr, addr);
	connect->port = port;
	connect->size = size;

	//DBG("Sending message");

	rc = send_remote_msg(tcp_junction, TCPJUNCTION_NAME, MSG_USER, 0, 0, connect, connect_len);

	//DBG("Sent Message");

	if (!rc)
	{
		return_tcpqueue = 0;
		tcp_errno = TCP_ERROR_MESSAGE_SEND;
		goto EARLY_EXIT;
	}

EARLY_EXIT:
	free(connect);
	return return_tcpqueue;
}

long tcp_write(long tcpqueue, char *data, int len)
{
	int write_len = sizeof(struct tcpcg_write_request)+len;
	struct tcpcg_write_request *msg = malloc(write_len);
	bool rc;
	long return_len;
	long buflen;
	char s[32];

	tcp_errno = 0;
	DBG("tcp_write");

	if (tcp_main_module == 0) 
	{
		tcp_errno = TCP_ERROR_UNINITIALIZED;
		goto EARLY_EXIT;
	}

	msg->hdr.serialno = ++tcp_serialno;
	msg->hdr.sockid = tcpqueues[tcpqueue].sockid;
    msg->hdr.msgid = TCPMSG_WRITE_REQUEST;
sprintf(s, "Sending to Sockid=%d", tcpqueues[tcpqueue].sockid);
DBG(s);
	memcpy(msg->data, data, len);
	rc = send_remote_msg(tcp_junction, TCPJUNCTION_NAME, MSG_USER, 0, 0, msg, write_len);
	if (!rc)
	{
		tcp_errno = TCP_ERROR_MESSAGE_SEND;
		return_len = 0;
		goto EARLY_EXIT;
	}
	return_len = len;

EARLY_EXIT:
	free(msg);
	return return_len;
}

long tcp_get_message(int delay, TCP_Cybiko_Handler handler)
{
	struct Message *msg;
	tcp_errno = 0;

	DBG("tcp_get_message");

	msg = cWinApp_get_message( tcp_main_module->m_process, delay, 1, MSG_USER );
	if (msg == 0) return 0;
	if (msg->msgid < MSG_TCP)
	{
		if (handler) tcp_errno = handler(msg);
		cWinApp_defproc(tcp_main_module->m_process, msg);
	}

	return tcp_process_message(msg);
}

long tcp_process_message(struct Message *msg)
{
	if (msg->msgid == MSG_TCP)
	{
		if(Message_has_buffer(msg))
		{
			int len = Buffer_get_size(Message_get_buffer(msg));
			char *msgbuf=malloc(len);
			char *user_data = tcpqueues[msg->msgid-MSG_TCP].user_data;
			Buffer_load(Message_get_buffer(msg), msgbuf, 0, len);
			tcp_errno = tcp_dispatch(msgbuf);
			free(msgbuf);
		}
	}
	else //socket data
	{
		if(Message_has_buffer(msg))
		{
			int len = Buffer_get_size(Message_get_buffer(msg));
			char *msgbuf=malloc(len);
			char *user_data = tcpqueues[msg->msgid-MSG_TCP].user_data;
			char s[32];
			TCP_Msg_Handler msg_handler = tcpqueues[msg->msgid-MSG_TCP].handler;
			Buffer_load(Message_get_buffer(msg), msgbuf, 0, len);
			//
			// we dont do acks anymore
			// tcp_ack(msg->msgid-MSG_TCP);
			if (msg_handler) tcp_errno = msg_handler(msg->msgid-MSG_TCP, msgbuf, user_data);
			free(msgbuf);
		}
	}

	Message_delete(msg);

EARLY_EXIT:
	return tcp_errno;
}

long tcp_close(long tcpqueue)
{
	int close_len = sizeof(struct tcpcg_close_request);
	struct tcpcg_close_request *msg = malloc(close_len);
	bool rc;

	tcp_errno = 0;

	DBG("tcp_close");

	if (tcp_main_module == 0) 
	{
		tcp_errno = TCP_ERROR_UNINITIALIZED;
		goto EARLY_EXIT;
	}

	msg->hdr.serialno = ++tcp_serialno;
	msg->hdr.sockid = tcpqueues[tcpqueue].sockid;
    msg->hdr.msgid = TCPMSG_CLOSE_REQUEST;

	rc = send_remote_msg(tcp_junction, TCPJUNCTION_NAME, MSG_USER, 0, 0, msg, close_len);
	if (!rc)
	{
		tcp_errno = TCP_ERROR_MESSAGE_SEND;
		goto EARLY_EXIT;
	}

EARLY_EXIT:
	free(msg);
	return tcp_errno;
}

long tcp_filter(long tcpqueue, long filter_type)
{
	int filter_len = sizeof(struct tcpcg_filter_request);
	struct tcpcg_filter_request *msg = malloc(filter_len);
	bool rc;

	tcp_errno = 0;
	DBG("tcp_filter");

	if (tcp_main_module == 0) 
	{
		tcp_errno = TCP_ERROR_UNINITIALIZED;
		goto EARLY_EXIT;
	}

	msg->hdr.serialno = ++tcp_serialno;
	msg->hdr.sockid = tcpqueues[tcpqueue].sockid;
    msg->hdr.msgid = TCPMSG_FILTER_REQUEST;
	msg->filter_type = filter_type;

	rc = send_remote_msg(tcp_junction, TCPJUNCTION_NAME, MSG_USER, 0, 0, msg, filter_len);
	if (!rc)
	{
		tcp_errno = TCP_ERROR_MESSAGE_SEND;
		goto EARLY_EXIT;
	}

EARLY_EXIT:
	free(msg);
	return tcp_errno;
}

long tcp_ack(long tcpqueue)
{
	int ack_len = sizeof(struct tcpcg_acknowledge);
	struct tcpcg_acknowledge *msg = malloc(ack_len);
	bool rc;
	char s[64];

	tcp_errno = 0;
	DBG("tcp_ack");

	if (tcp_main_module == 0) 
	{
		tcp_errno = TCP_ERROR_UNINITIALIZED;
		goto EARLY_EXIT;
	}

	msg->hdr.serialno = ++tcp_serialno;
	msg->hdr.sockid = tcpqueues[tcpqueue].sockid;
    msg->hdr.msgid = TCPMSG_ACKNOWLEDGE;

//sprintf(s, "tcpqueue=%d sockid=%d", tcpqueue, tcpqueues[tcpqueue].sockid);
//printf(s);

	rc = send_remote_msg(tcp_junction, TCPJUNCTION_NAME, MSG_USER, 0, 0, msg, ack_len);
	if (!rc)
	{
		tcp_errno = TCP_ERROR_MESSAGE_SEND;
		goto EARLY_EXIT;
	}

EARLY_EXIT:
	free(msg);
	return tcp_errno;
}

long tcp_connect_accept(void *xx)
{
	struct tcpgc_connect_response *cr=xx;
	char s[32];

	DBG("tcp_connect_accept");

	if (cr->hdr.status != TCP_SUCCESS)
	{
		DBG("ERROR - connect failed");
		tcp_errno = cr->hdr.status;
		goto EARLY_EXIT;
	}
	tcpqueues[cr->tcpqueue-MSG_TCP].sockid = cr->sockid;
	sprintf(s, "sockid=%d", cr->sockid);
	DBG(s);

EARLY_EXIT:
	return tcp_errno;
}

long tcp_write_accept(void *xx)
{
	struct tcpgc_write_response *wr = xx;
	tcp_errno = wr->hdr.status;

	DBG("tcp_write_accept");
	if (wr->hdr.status != TCP_SUCCESS)
	{
		DBG("ERROR - write failed");
		tcp_errno = wr->hdr.status;
		goto EARLY_EXIT;
	}

EARLY_EXIT:
	return tcp_errno;
}

long tcp_filter_accept(void *xx)
{
	struct tcpgc_filter_response *fr = xx;
	tcp_errno = fr->hdr.status;

	DBG("tcp_filter_accept");

	if (fr->hdr.status != TCP_SUCCESS)
	{
		DBG("ERROR - filter failed");
		tcp_errno = fr->hdr.status;
		goto EARLY_EXIT;
	}
EARLY_EXIT:
	return tcp_errno;
}

long tcp_close_accept(void *xx)
{
	struct tcpgc_close_response *cr=xx;

	DBG("tcp_close_accept");

	if (cr->hdr.status == TCP_SUCCESS)
	{
		free_tcpqueue(cr->tcpqueue-MSG_TCP);
	}
	if (cr->hdr.status != TCP_SUCCESS)
	{
		DBG("ERROR - close failed");
		tcp_errno = cr->hdr.status;
		goto EARLY_EXIT;
	}
	tcp_errno = cr->hdr.status;

EARLY_EXIT:
	return tcp_errno;
}

char *tcp_read_accept(void *xx)
{
	struct tcpgc_read_response *rr=xx;

	tcp_errno = 0;

	DBG("tcp_read_accept");

	if (rr->hdr.msgid != TCPMSG_READ_RESPONSE)
	{
		tcp_errno = TCP_ERROR_UNKNOWN_MESSAGE;
		return 0;
	}
	if (rr->hdr.status != TCP_SUCCESS)
	{
		DBG("ERROR - read failed");
		tcp_errno = rr->hdr.status;
		return 0;
	}
	return &(rr->data[0]);
}

long tcp_dispatch(void *xx)
{
	struct tcpgc_hdr *hdr = xx;
	tcp_errno = 0;
	DBG("tcp_dispatch");

	switch(hdr->msgid) {
		case TCPMSG_CONNECT_RESPONSE: tcp_connect_accept(xx); break;
		case TCPMSG_WRITE_RESPONSE: tcp_write_accept(xx); break;
		case TCPMSG_CLOSE_RESPONSE: tcp_close_accept(xx); break;
		case TCPMSG_READ_RESPONSE: tcp_read_accept(xx); break;
		case TCPMSG_FILTER_RESPONSE: tcp_filter_accept(xx); break;
		default: 
		{
			char tmp[32];
			tcp_errno = TCP_ERROR_UNKNOWN_MESSAGE;
			sprintf(tmp, "Unknown msgid=%d", hdr->msgid);
			DBG(tmp);
			break;
		}
	}
    return tcp_errno;
}

long tcp_swaplong(long x)
{
	char *y = (char *)&x;
	char tmp;

	tmp = y[0];
	y[0] = y[3];
	y[3] = tmp;
	tmp = y[1];
	y[1] = y[2];
	y[2] = tmp;
	return x;
}

short tcp_swapshort(short x)
{
	char *y = (char *)&x;
	char tmp;

	tmp = y[0];
	y[0] = y[1];
	y[1] = tmp;
	return x;
}

long tcp_msgid(void *xx)
{
	struct tcpgc_hdr *hdr = xx;
	tcp_errno = 0;
	return hdr->msgid;
}

long tcp_tcpqueue(void *xx)
{
	struct tcpgc_connect_response *hdr = xx;
	tcp_errno = 0;
	return hdr->tcpqueue-MSG_TCP; /** See Important Note Above **/
}

char *tcp_getdata(void *xx, long *len)
{
	struct tcpgc_read_response *rr = xx;
	tcp_errno = 0;
	*len = rr->len;
	return rr->data;
}
