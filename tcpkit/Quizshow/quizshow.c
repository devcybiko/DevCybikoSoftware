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
#include <winsock.h>
#include <stdio.h>
#include <time.h>

#define DBG printf

#define VERSION "1.0"
#define MAX_PLAYERS 64
#define QUIZSHOW_PORT 6000
#define MAX_BACKLOG 2048

char msgbuf[1024];

struct player {
	int socket;
} players[MAX_PLAYERS] = {0};

void print_error(int rc)
{
	switch(rc) 
	{
		case WSAEADDRINUSE:		DBG("WSAEADDRINUSE\n"); break;
		case WSAEADDRNOTAVAIL:	DBG("WSAEADDRNOTAVAIL\n"); break;
		case WSAEAFNOSUPPORT:	DBG("WSAEAFNOSUPPORT\n"); break;
		case WSAECONNREFUSED:	DBG("WSAECONNREFUSED\n"); break;
		case WSAEFAULT:			DBG("WSAEFAULT\n"); break;
		case WSAEINPROGRESS:	DBG("WSAEINPROGRESS\n"); break;
		case WSAEINTR:			DBG("WSAEINTR\n"); break;
		case WSAEINVAL:			DBG("WSAEINVAL\n"); break;
		case WSAEISCONN:		DBG("WSAEISCONN\n"); break;
		case WSAEMFILE:			DBG("WSAEMFILE\n"); break;
		case WSAENETDOWN:		DBG("WSAENETDOWN\n"); break;
		case WSAENETUNREACH:	DBG("WSAENETUNREACH\n"); break;
		case WSAENOBUFS:		DBG("WSAENOBUFS\n"); break;
		case WSAENOTSOCK:		DBG("WSAENOTSOCK\n"); break;
		case WSAEPROTONOSUPPORT: DBG("WSAEPROTONOSUPPORT\n"); break;
		case WSAEPROTOTYPE:		DBG("WSAEPROTOTYPE\n"); break;
		case WSAESOCKTNOSUPPORT:DBG("WSAESOCKTNOSUPPORT\n"); break;
		case WSAETIMEDOUT:		DBG("WSAETIMEDOUT\n"); break;
		case WSAEWOULDBLOCK:	DBG("WSAEWOULDBLOCK\n"); break;
		case WSANOTINITIALISED:	DBG("WSANOTINITIALISED\n"); break;
		default:				DBG("ERROR: %d\n", rc);
	}
}

errexit(char *s)
{
	printf("%s\n", s);
	exit(0);
}

/*void socket_connect(struct tcpcg_connect_request *cr)
{
	long sockid;
	long status;
	int rc;
	SOCKADDR_IN sin;
	SOCKET s;

	DBG("tcpmsg_connect_request\n");
	status = 0;
	sockid = alloc_sockid();
	if (sockid == 0)
	{
		status = TCP_ERROR_NO_MORE_GATE_SOCKIDS;
		DBG("ERROR: Could not allocate more sockids\n");
		goto EARLY_EXIT;
	}

	DBG("Sockid allocated=%d\n", sockid);
	strcpy(sockids[sockid].appname, cr->appname);
	sockids[sockid].cyid = serial_swaplong(cr->cyid);
	sockids[sockid].tcpqueue = serial_swaplong(cr->tcpqueue);
	DBG("msg_queue=%d\n", sockids[sockid].tcpqueue);
	DBG("cr->port=%ld\n", cr->port);
	sockids[sockid].port = serial_swaplong(cr->port);
	DBG("sockids[sockid].port=%ld\n", sockids[sockid].port);
	sockids[sockid].socket = 0; /* socket, bind, connect */
/*	sockids[sockid].read_enabled = 1;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;

	if (isdigit(cr->addr[0]))
	{
		sin.sin_addr.s_addr = inet_addr(cr->addr);
		DBG("ADDR=%s\n", cr->addr);
		DBG("ADDR=%08x\n", sin.sin_addr.s_addr);
	}
	else
	{
		struct hostent *host = gethostbyname(cr->addr);
		memcpy(&sin.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
		DBG("ADDR=%s\n", cr->addr);
		DBG("ADDR=%08x\n", sin.sin_addr.s_addr);
	}
	sin.sin_port = htons((short)sockids[sockid].port);
	DBG("PORT=%d\n", sin.sin_port);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error opening socket\n");
		status = TCP_ERROR_SOCKET_FAILED;
		goto EARLY_EXIT;
	}
	
	rc = connect(s, (struct sockaddr *) &sin, sizeof(sin));
	if (rc == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error connecting to socket\n");
		status = TCP_ERROR_CONNECT_FAILED;
		goto EARLY_EXIT;
	}

	sockids[sockid].socket = s;

	DBG("connect: sockid=%d msgid=%d cyid=%d msg_queue=%d addr=%s port=%d\n",
		serial_swaplong(cr->hdr.sockid),
		serial_swaplong(cr->hdr.msgid),
		serial_swaplong(cr->cyid),
		serial_swaplong(cr->tcpqueue),
		cr->addr,
		serial_swaplong(cr->port));

	if (sockids[sockid].socket == 0) /* error code */
/*	{
		status = TCP_ERROR_SOCKET_FAILED;
		goto EARLY_EXIT;
	}

	{
		u_long arg=1;
		ioctlsocket (s, FIONBIO, &arg);
	}


EARLY_EXIT:
	tcpmsg_connect_response(sockid, status, cr->hdr.serialno);
	if (status) free_sockid(sockid);
	return;
}
*/

SOCKET socket_listen()
{
	int rc;
	SOCKADDR_IN sin;
	SOCKET s=0;
	u_long arg=1;

	DBG("socket_listen\n");

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(QUIZSHOW_PORT);
	sin.sin_addr.s_addr = 0; /* this machine */

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error opening socket\n");
		s=0;
		goto EARLY_EXIT;
	}


	rc = bind(s, (struct sockaddr *) &sin, sizeof(sin));
	if (rc == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error binding to socket\n");
		s=0;
		goto EARLY_EXIT;
	}

	rc = listen (s, MAX_BACKLOG);
	if (rc == SOCKET_ERROR)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error binding to socket\n");
		s=0;
		goto EARLY_EXIT;
	}

	ioctlsocket (s, FIONBIO, &arg);

EARLY_EXIT:
	return s;
}

main(int argc, char **argv)
{
	WSADATA wsaData;
	int rc;
	int i;
	SOCKET well_known_socket;
	int lastnop=0;
	int len;

	//outfile = fopen("test.dat", "w");

	if((rc=WSAStartup( MAKEWORD(2,0), &wsaData )))
	{
		perror("Sorry, can't initialize Windows Sockets...");
		DBG("Error code=%d", rc);
		exit(1);
	}

	DBG(">main\n");
	printf("Quizshow Version %s\n", VERSION);
	printf("By Gregory Smith\n");
	printf("Copyright 2002 by The Alcor Group, Inc.\n");

	well_known_socket = socket_listen();
	DBG("well_known_socket=%d\n", well_known_socket);

	while(1)
	{
		SOCKET new_socket = accept(well_known_socket, 0, 0);
		if (new_socket != INVALID_SOCKET)
		{
			DBG("Got a new player = %d\n", new_socket);
			//player_new(new_socket);
		}
		for(i=0; i<MAX_PLAYERS; i++)
		{
			if (players[i].socket)
			{
				struct timeval tv;

				tv.tv_sec = 0;
				tv.tv_usec = 0;
				DBG("Reading...");
				len = recv(players[i].socket, msgbuf, sizeof(msgbuf), 0);
				if (len <= 0) continue;
			}
		}

		if (time(NULL)-lastnop > 30) 
		{
			lastnop = time(NULL);
		}

		Sleep(10);
	}
	DBG("<main\n");
}
