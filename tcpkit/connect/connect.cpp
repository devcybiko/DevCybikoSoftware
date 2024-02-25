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
// connect.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>

#include <windows.h>
#include <io.h>

void print_error(int rc)
{
	switch(rc) 
	{
		case WSAEADDRINUSE:		printf("WSAEADDRINUSE\n"); break;
		case WSAEADDRNOTAVAIL:	printf("WSAEADDRNOTAVAIL\n"); break;
		case WSAEAFNOSUPPORT:	printf("WSAEAFNOSUPPORT\n"); break;
		case WSAECONNREFUSED:	printf("WSAECONNREFUSED\n"); break;
		case WSAEFAULT:			printf("WSAEFAULT\n"); break;
		case WSAEINPROGRESS:	printf("WSAEINPROGRESS\n"); break;
		case WSAEINTR:			printf("WSAEINTR\n"); break;
		case WSAEINVAL:			printf("WSAEINVAL\n"); break;
		case WSAEISCONN:		printf("WSAEISCONN\n"); break;
		case WSAEMFILE:			printf("WSAEMFILE\n"); break;
		case WSAENETDOWN:		printf("WSAENETDOWN\n"); break;
		case WSAENETUNREACH:	printf("WSAENETUNREACH\n"); break;
		case WSAENOBUFS:		printf("WSAENOBUFS\n"); break;
		case WSAENOTSOCK:		printf("WSAENOTSOCK\n"); break;
		case WSAEPROTONOSUPPORT: printf("WSAEPROTONOSUPPORT\n"); break;
		case WSAEPROTOTYPE:		printf("WSAEPROTOTYPE\n"); break;
		case WSAESOCKTNOSUPPORT:printf("WSAESOCKTNOSUPPORT\n"); break;
		case WSAETIMEDOUT:		printf("WSAETIMEDOUT\n"); break;
		case WSAEWOULDBLOCK:	printf("WSAEWOULDBLOCK\n"); break;
		case WSANOTINITIALISED:	printf("WSANOTINITIALISED\n"); break;
		case WSAHOST_NOT_FOUND: printf("WSAHOST_NOT_FOUND\n"); break;
		case WSATRY_AGAIN: printf("WSATRY_AGAIN\n"); break;
		case WSANO_RECOVERY: printf("WSANO_RECOVERY\n"); break;
		case WSANO_DATA: printf("WSANO_DATA\n"); break;
		default:				printf("WSA-ERROR: %d\n", rc);
	}
}

SOCKET myconnect(char *hostname, int port) {
	int rc;
	SOCKADDR_IN sin;
	SOCKET s;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;

	if (isdigit(hostname[0]))
	{
		sin.sin_addr.s_addr = inet_addr(hostname);
	}
	else
	{
		struct hostent *host = gethostbyname(hostname);
		if (host == NULL) 
		{
			int rc = WSAGetLastError();
			printf("ERROR - gethostbyname failed\n");
			print_error(rc);
			exit(0);
		}
		memcpy(&sin.sin_addr.s_addr, host->h_addr_list[0], host->h_length);
		printf("ADDR=%s\n", hostname);
		printf("ADDR=%08x\n", sin.sin_addr.s_addr);
	}
	sin.sin_port = htons((short)port);
	printf("PORT=%d\n", sin.sin_port);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		printf("Error opening socket\n");
		exit(0);
	}
	
	rc = connect(s, (struct sockaddr *) &sin, sizeof(sin));
	if (rc == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		printf("Error connecting to socket\n");
		exit(0);
	}

	{
		u_long arg=1;
		ioctlsocket (s, FIONBIO, &arg);
	}
	{
		BOOL out_of_band_in_normal_stream = 1;
		setsockopt (s, SOL_SOCKET, SO_OOBINLINE, (char *)&out_of_band_in_normal_stream, sizeof(BOOL));
	}

	return s;
}
#define SE (signed char)240
#define NOP (signed char)241
#define DM (signed char)242
#define IAC (signed char)0xff
#define DONT (signed char)0xfe
#define DO (signed char)0xfd
#define WONT (signed char)0xfc
#define WILL (signed char)0xfb
#define SB (signed char)0xfa
#define GA (signed char)0xf9
char telnet_options[] = {
	IAC, DO, 3, //suppress go ahead
	IAC, WONT, 24, //terminal type
	IAC, WONT, 31, // naws (window size)
	IAC, WONT, 32, // terminal speed
	IAC, WONT, 33, // remote flow control
	IAC, WONT, 34, // line mode
	IAC, WONT, 36, // new-environment
};

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	int rc;
	SOCKET s;
	struct timeval tv;
	int len;
	signed char buf[1024];
	char msgbuf[1024];

	printf("Hello World!\n");

	if((rc=WSAStartup( MAKEWORD(2,0), &wsaData )))
	{
		perror("Sorry, can't initialize Windows Sockets...");
		printf("Error code=%d", rc);
		exit(1);
	}
	s = myconnect("devcybiko.com", 23);
	send(s, telnet_options, sizeof(telnet_options),0);
	strcpy(msgbuf, "gsmith\npicard\n");
	send(s, msgbuf, strlen(msgbuf), 0);

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	while(true)
	{
		int i;
		len = recv(s, (char *)buf, 1024, 0);
		if (len < 0) continue;
		if (len == 0) break;
		for(i=0; i<len; i++) {
			if (buf[i] == IAC) {
				if (buf[i+1] == DO) {
					char will[4];
					printf("GOT DO\n");
					will[0] = IAC;
					will[1] = WONT;
					will[2] = buf[i+2];
					send(s, will, 3, 0);
					i+=2;
				} else if (buf[i+1] == SB) {
					i+=3;
					printf("GOT SB\n");
				}
				else if (buf[i+1] == SE) {
					i+=1;
					printf("GOT SE");
				}
				else if (buf[i+1] == WILL) {
					char will[4];
					printf("GOT WILL\n");
					will[0] = IAC;
					will[1] = WONT;
					will[2] = buf[i+2];
					send(s, will, 3, 0);
					i+=2;
				}
				else {
					printf("GOT OTHER %d", buf[i]);
					i+=1;
				}
			} else {
				printf("^%c %d\n", buf[i], buf[i]);
			}
		}
	}
	return 0;
}

