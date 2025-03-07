/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

/*
 * $Id: tcplink.h,v 1.4 2001/06/17 05:42:53 cyreve Exp $
 *
 * Copyright (C) 1998-2001, Denis V. Dmitrienko <denis@null.net> and
 *                          Bill Soudan <soudan@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef _TCP_LINK_H_
#define _TCP_LINK_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef _WIN32
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "icq.h"
#include "icqpacket.h"
#include "timeout.h"

/* link mode bitfield values */
#define TCP_LINK_MODE_RAW             1
#define TCP_LINK_MODE_HELLOWAIT       2
#define TCP_LINK_MODE_LISTEN          4
#define TCP_LINK_MODE_CONNECTING      8
#define TCP_LINK_SOCKS_CONNECTING     16
#define TCP_LINK_SOCKS_AUTHORIZATION  32
#define TCP_LINK_SOCKS_AUTHSTATUS     64
#define TCP_LINK_SOCKS_NOAUTHSTATUS   128
#define TCP_LINK_SOCKS_CROSSCONNECT   256
#define TCP_LINK_SOCKS_CONNSTATUS     512

/* link types */
#define TCP_LINK_MESSAGE              1
#define TCP_LINK_CHAT                 2
#define TCP_LINK_FILE                 3

#define icq_TCPLinkBufferSize 4096
#define TCP_LINK_CONNECT_TIMEOUT 30

struct icq_TCPLink_s {

   /* icq_TCPLink ICQLINK, type, mode, and session */
   icq_Link *icqlink;
   int type;
   int mode;
   int proxy_status;
   void *session;
	 
   /* socket parameters */
   int socket;
   struct sockaddr_in socket_address;
   struct sockaddr_in remote_address;

   /* data buffer for receive calls */
   char buffer[icq_TCPLinkBufferSize];
   int buffer_count;

   /* packet queues */
   icq_List *received_queue;
   icq_List *send_queue;

   /* icq specific data, initialized by hello packet */
   unsigned long id;
   unsigned long remote_version;
   unsigned long remote_uin;
   char flags;

   /* timeout for connect operation */
   icq_Timeout *connect_timeout;

};

icq_TCPLink *icq_TCPLinkNew(icq_Link *icqlink);
void icq_TCPLinkDelete(void *p);
void icq_TCPLinkClose(icq_TCPLink *p);
void icq_TCPLinkNodeDelete(icq_ListNode *p);

int icq_TCPLinkConnect(icq_TCPLink *plink, DWORD uin, int port);
icq_TCPLink *icq_TCPLinkAccept(icq_TCPLink *plink);
int icq_TCPLinkListen(icq_TCPLink *plink);

void icq_TCPLinkOnDataReceived(icq_TCPLink *plink);
void icq_TCPLinkOnPacketReceived(icq_TCPLink *plink, icq_Packet *p);
void icq_TCPLinkOnConnect(icq_TCPLink *plink);
void icq_TCPLinkOnConnectTimeout(icq_TCPLink *plink);

unsigned long icq_TCPLinkSendSeq(icq_TCPLink *plink, icq_Packet *p,
  unsigned long sequence);
int icq_TCPLinkSend(icq_TCPLink *plink, icq_Packet *p);

void icq_TCPLinkProcessReceived(icq_TCPLink *plink);

icq_TCPLink *icq_FindTCPLink(icq_Link *icqlink, unsigned long uin, int type);

void icq_ChatRusConv_n(const char to[4], char *t_in, int t_len);

#endif /* _TCP_LINK_H_ */
