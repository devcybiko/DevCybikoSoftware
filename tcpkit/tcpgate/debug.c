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
#define DEBG printf

void debug_output(char *format, ...)
{
	char buf[1024];

	va_list marker;
	va_start( marker, format );     /* Initialize variable arguments. */
	vsprintf(buf, format, marker);
	if (buf[0] == '>') 
	{
		fprintf(outfile, "%s", buf);
		fflush(outfile);
	}
	else if (buf[0] == '.') 
	{
		fprintf(stdout, "%s", buf);
		fflush(stdout);
	}
	else
	{
		fprintf(stdout, "%s", buf);
		fflush(stdout);
		fprintf(outfile, "%s", buf);
		fflush(outfile);
	}
	va_end(marker);
}

void debug_dump_hdr(struct tcpclient_header *hdr)
{
	DEBG(">  hdr.msgid=%d\n", hdr->msgid);
	DEBG(">  hdr.serialno=%d\n", hdr->serialno);
	DEBG(">  hdr.sockid=%d\n", hdr->sockid);
}


void print_error(int rc)
{
	switch(rc) 
	{
		case WSAEADDRINUSE:		DEBG("WSAEADDRINUSE\n"); break;
		case WSAEADDRNOTAVAIL:	DEBG("WSAEADDRNOTAVAIL\n"); break;
		case WSAEAFNOSUPPORT:	DEBG("WSAEAFNOSUPPORT\n"); break;
		case WSAECONNREFUSED:	DEBG("WSAECONNREFUSED\n"); break;
		case WSAEFAULT:			DEBG("WSAEFAULT\n"); break;
		case WSAEINPROGRESS:	DEBG("WSAEINPROGRESS\n"); break;
		case WSAEINTR:			DEBG("WSAEINTR\n"); break;
		case WSAEINVAL:			DEBG("WSAEINVAL\n"); break;
		case WSAEISCONN:		DEBG("WSAEISCONN\n"); break;
		case WSAEMFILE:			DEBG("WSAEMFILE\n"); break;
		case WSAENETDOWN:		DEBG("WSAENETDOWN\n"); break;
		case WSAENETUNREACH:	DEBG("WSAENETUNREACH\n"); break;
		case WSAENOBUFS:		DEBG("WSAENOBUFS\n"); break;
		case WSAENOTSOCK:		DEBG("WSAENOTSOCK\n"); break;
		case WSAEPROTONOSUPPORT: DEBG("WSAEPROTONOSUPPORT\n"); break;
		case WSAEPROTOTYPE:		DEBG("WSAEPROTOTYPE\n"); break;
		case WSAESOCKTNOSUPPORT:DEBG("WSAESOCKTNOSUPPORT\n"); break;
		case WSAETIMEDOUT:		DEBG("WSAETIMEDOUT\n"); break;
		case WSAEWOULDBLOCK:	DEBG("WSAEWOULDBLOCK\n"); break;
		case WSANOTINITIALISED:	DEBG("WSANOTINITIALISED\n"); break;
		case WSAHOST_NOT_FOUND: DEBG("WSAHOST_NOT_FOUND\n"); break;
		case WSATRY_AGAIN: DEBG("WSATRY_AGAIN\n"); break;
		case WSANO_RECOVERY: DEBG("WSANO_RECOVERY\n"); break;
		case WSANO_DATA: DEBG("WSANO_DATA\n"); break;
		default:				DEBG("WSA-ERROR: %d\n", rc);
	}
}

errexit(char *s)
{
	DEBG("%s", s);
	exit(0);
}

dump(char *s, int len)
{
	int i=0;

	printf("-----------------------------------\n");
	printf("LEN=%d\n", len);
	printf("%4d: ", i);
	for(i=0; i< len; i++)
	{
		if (i && i%8==0) printf("\n%4d: ", i);
		printf("%02x=", (unsigned char) s[i]);
		if (s[i] >= 32) printf("%c ", s[i]);
		else printf(". ");
	}
	printf("\n");
	printf("-----------------------------------\n");
}

