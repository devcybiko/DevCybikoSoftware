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
#include "tcpgate.h"
#include "sockid.h"
#include "debug.h"
#include "raw.h"
#include "wml.h"
#include "html.h"

#define DEBG printf

void swap_hdr(struct tcpclient_header *hdr)
{
	hdr->msgid = serial_swaplong(hdr->msgid);
	hdr->serialno = serial_swaplong(hdr->serialno);
	hdr->sockid = serial_swaplong(hdr->sockid);
}

void tcpmsg_connect_request(struct tcpcg_connect_request *cr)
{
	long sockid;
	long status;
	int rc;
	SOCKADDR_IN sin;
	SOCKET s;

	DEBG("tcpmsg_connect_request\n");

	swap_hdr(&cr->hdr);
	cr->cyid = serial_swaplong(cr->cyid);
	cr->port = serial_swaplong(cr->port);
	cr->tcpqueue = serial_swaplong(cr->tcpqueue);
	cr->size = serial_swaplong(cr->size);

	debug_dump_hdr(&cr->hdr);
	DEBG(">  cr->addr=%s\n", cr->addr);
	DEBG(">  cr->appname=%s\n", cr->appname);
	DEBG(">  cr->cyid=%d\n", cr->cyid);
	DEBG(">  cr->port=%d\n", cr->port);
	DEBG(">  cr->tcpqueue=%d\n", cr->tcpqueue);
	DEBG(">  cr->size=%d\n", cr->size);

	status = 0;
	sockid = alloc_sockid();
	if (sockid == 0)
	{
		status = TCP_ERROR_NO_MORE_GATE_SOCKIDS;
		DEBG("ERROR: Could not allocate more sockids\n");
		goto EARLY_EXIT;
	}

	DEBG("Sockid allocated=%d\n", sockid);
	strcpy(sockids[sockid].appname, cr->appname);
	sockids[sockid].cyid = cr->cyid;
	sockids[sockid].tcpqueue = cr->tcpqueue;
	DEBG("msg_queue=%d\n", sockids[sockid].tcpqueue);
	DEBG("cr->port=%ld\n", cr->port);
	sockids[sockid].port = cr->port;
	DEBG("sockids[sockid].port=%ld\n", sockids[sockid].port);
	sockids[sockid].socket = 0; /* socket, bind, connect */
	sockids[sockid].read_enabled = 0; // enable reading while read_enabled = 0

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;

	if (isdigit(cr->addr[0]))
	{
		sin.sin_addr.s_addr = inet_addr(cr->addr);
		DEBG("ADDR=%s\n", cr->addr);
		DEBG("ADDR=%08x\n", sin.sin_addr.s_addr);
	}
	else
	{
		struct hostent *host = gethostbyname(cr->addr);
		if (host == NULL) 
		{
			int rc = WSAGetLastError();
			DEBG("ERROR - gethostbyname failed\n");
			print_error(rc);

			status = TCP_ERROR_SOCKET_FAILED;
			goto EARLY_EXIT;
		}
		DEBG("h_length=%d\n", host->h_length);
		memcpy(&sin.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
		DEBG("ADDR=%s\n", cr->addr);
		DEBG("ADDR=%08x\n", sin.sin_addr.s_addr);
	}
	sin.sin_port = htons((short)sockids[sockid].port);
	DEBG("PORT=%d\n", sin.sin_port);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DEBG("Error opening socket\n");
		status = TCP_ERROR_SOCKET_FAILED;
		goto EARLY_EXIT;
	}
	
	rc = connect(s, (struct sockaddr *) &sin, sizeof(sin));
	if (rc == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DEBG("Error connecting to socket\n");
		status = TCP_ERROR_CONNECT_FAILED;
		goto EARLY_EXIT;
	}

	sockids[sockid].socket = s;

	DEBG("connect: sockid=%d socket=%d msgid=%d cyid=%d msg_queue=%d addr=%s port=%d\n",
		sockid,
		s, 
		cr->hdr.msgid,
		cr->cyid,
		cr->tcpqueue,
		cr->addr,
		cr->port);

	if (sockids[sockid].socket == 0) /* error code */
	{
		DEBG("ERROR - Socket() failed\n");
		status = TCP_ERROR_SOCKET_FAILED;
		goto EARLY_EXIT;
	}

	{
		u_long arg=1;
		ioctlsocket (s, FIONBIO, &arg);
	}
	{
		BOOL out_of_band_in_normal_stream = 1;
		setsockopt (s, SOL_SOCKET, SO_OOBINLINE, (char *)&out_of_band_in_normal_stream, sizeof(BOOL));
	}
	sockids[sockid].filter_recv = filter_recv_raw;
	sockids[sockid].filter_send = filter_send_raw;
	sockids[sockid].filter_data = 0;
	sockids[sockid].msg_data = malloc(cr->size+1); // added one for null byte, http
	sockids[sockid].msg_size = cr->size;


EARLY_EXIT:
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	tcpmsg_connect_response(sockid, status, cr->hdr.serialno);
	if (status) free_sockid(sockid);
	return;
}

void tcpmsg_write_request(struct tcpcg_write_request *msg, int len)
{
	long sockid;
	int rc;
	long status;
	static int socsnd_ctr=0;

	DEBG("tcpmsg_write_request\n");
	swap_hdr(&msg->hdr);

	debug_dump_hdr(&msg->hdr);
	DEBG(">  len=%d  msg->data='%s'\n", len-sizeof(msg->hdr), msg->data);

	status = 0;

	sockid = msg->hdr.sockid;
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);

	if (sockid < 0 || sockid >= MAX_SOCKIDS) 
	{
		DEBG("Error - invalid SOCKID = %d\n", sockid);
		status = TCP_ERROR_WRITE_FAILED;
		goto EARLY_EXIT;
	}

	DEBG("  sockid=%d filter=%08x\n", sockid, sockids[sockid].filter_send);
	if (sockids[sockid].filter_send)
	{
		printf("{%d ", socsnd_ctr);
		DEBG(" {%d\n", socsnd_ctr);
		socsnd_ctr++;
		rc = sockids[sockid].filter_send(sockid, msg->data, len-sizeof(msg->hdr));
	}

	if (rc != (int)(len-sizeof(msg->hdr))) 
	{
		DEBG("Error sending data\n");
		print_error(WSAGetLastError());
		status = TCP_ERROR_WRITE_FAILED;
		goto EARLY_EXIT;
	}
	
	DEBG("Wrote %s\n", msg->data);

EARLY_EXIT:
	//tcpmsg_write_response(sockid,status,msg->hdr.serialno);
	;
}

void tcpmsg_close_request(struct tcpcg_close_request *msg)
{
	long sockid;
	long status;

	DEBG("tcpmsg_close_request\n");
	swap_hdr(&msg->hdr);

	debug_dump_hdr(&msg->hdr);

	status = 0;
	sockid = msg->hdr.sockid;
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);

	if (sockids[sockid].socket) 
	{
		DEBG("Closing Socket %d\n", sockid);
		closesocket(sockids[sockid].socket);
		sockids[sockid].socket = 0;
	}
	tcpmsg_close_response(sockid, status, msg->hdr.serialno);
	free_sockid(sockid);
}

void tcpmsg_filter_request(struct tcpcg_filter_request *msg)
{
	long sockid;
	long status;

	DEBG("tcpmsg_filter_request\n");
	swap_hdr(&msg->hdr);
	msg->filter_type = serial_swaplong(msg->filter_type);

	debug_dump_hdr(&msg->hdr);
	DEBG(">  msg->filter_type=%d\n", msg->filter_type);

	status = 0;
	sockid = msg->hdr.sockid;
	DEBG("  sockid=%d socket=%d filter_recv\n", 
		sockid, sockids[sockid].socket, sockids[sockid].filter_recv );

	if (sockids[sockid].socket) 
	{
		if (sockids[sockid].filter_data) free(sockids[sockid].filter_data);
		switch(msg->filter_type)
		{
		case TCP_FILTER_RAW:
			DEBG("TCP_FILTER_RAW\n");
			sockids[sockid].filter_recv = filter_recv_raw;
			sockids[sockid].filter_send = filter_send_raw;
			sockids[sockid].filter_data = 0;
			break;
		case TCP_FILTER_WML:
			DEBG("TCP_FILTER_WML\n");
			sockids[sockid].filter_recv = filter_recv_wml;
			sockids[sockid].filter_send = filter_send_wml;
			sockids[sockid].filter_data = calloc(1, sizeof(struct filter_wml_t));
			break;
		case TCP_FILTER_HTML:
		{
			struct filter_html_t *data;
			DEBG("TCP_FILTER_HTML\n");
			sockids[sockid].filter_recv = filter_recv_html;
			sockids[sockid].filter_send = filter_send_html;
			sockids[sockid].filter_data = (char *) data = calloc(1, sizeof(struct filter_html_t));
			data->inside = 1;
			break;
		}
		default:
			status = TCP_ERROR_UNKNOWN_FILTER;
			DEBG("ERROR-Unknown Filter Type\n");
		}
	}
	tcpmsg_filter_response(sockid, status, msg->hdr.serialno);
}

void tcpmsg_acknowledge(struct tcpcg_acknowledge *msg)
{
	long sockid;
	long status;

	DEBG("tcpmsg_acknowledge\n");
	swap_hdr(&msg->hdr);

	debug_dump_hdr(&msg->hdr);

	status = 0;
	sockid = msg->hdr.sockid;
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);

	if (sockids[sockid].socket) 
	{
		sockids[sockid].read_enabled--; //enabled = 0
		if (sockids[sockid].read_enabled < 0) sockids[sockid].read_enabled = 0;
	}
	DEBG("  read enabled = %d\n", sockids[sockid].read_enabled);
}

