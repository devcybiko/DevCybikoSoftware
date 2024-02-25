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
#include "html.h"
#include "wml.h"

FILE *outfile;

void null_func() {}

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
		case WSAHOST_NOT_FOUND: DBG("WSAHOST_NOT_FOUND\n"); break;
		case WSATRY_AGAIN: DBG("WSATRY_AGAIN\n"); break;
		case WSANO_RECOVERY: DBG("WSANO_RECOVERY\n"); break;
		case WSANO_DATA: DBG("WSANO_DATA\n"); break;
		default:				DBG("WSA-ERROR: %d\n", rc);
	}
}

errexit(char *s)
{
	DBG("%s", s);
	exit(0);
}

/* 
void tcpmsg_send_data(long sockid, long tcpqueue, char *data, long len)
{
	struct tcpgj_header *msg;
	int acklen=0;
	static to_cybiko_ctr=0;

	DBG("tcpmsg_send_data(sockid=%d, tcpqueue=%d data=%s len=%d)\n",
		sockid, tcpqueue,data,len);
	DBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);

	msg = malloc(sizeof(struct tcpgj_header)+len);
	strcpy(msg->appname, sockids[sockid].appname);
	msg->cyid = sockids[sockid].cyid;
	if (tcpqueue == 0)
		msg->msg_queue = sockids[sockid].tcpqueue;
	else
		msg->msg_queue = tcpqueue;
	DBG("  Sockid=%d\n", sockid);
	DBG("  Sending to queue %d\n", msg->msg_queue);
	memcpy(msg->data, data, len);

	sockids[sockid].read_enabled++;  // disable reading from the socket until cybiko ACKs

	msg->cyid = serial_swaplong(msg->cyid);
	msg->msg_queue = serial_swaplong(msg->msg_queue);
	printf("<%d ", to_cybiko_ctr);
	DBG(" <%d\n", to_cybiko_ctr);
	to_cybiko_ctr++;
	serial_send(tty, (char *)msg, sizeof(struct tcpgj_header)+len);
	free(msg);
}
*/
SOCKET myconnect()
{
	long status;
	int rc;
	SOCKADDR_IN sin;
	SOCKET s;

	DBG(">myconnect\n");

	status = 0;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("62.146.78.211");
	sin.sin_port = htons((short)7171);
	DBG("PORT=%d\n", sin.sin_port);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error opening socket\n");
		goto EARLY_EXIT;
	}
	
	rc = connect(s, (struct sockaddr *) &sin, sizeof(sin));
	if (rc == INVALID_SOCKET)
	{
		int rc = WSAGetLastError();
		print_error(rc);
		DBG("Error connecting to socket\n");
		goto EARLY_EXIT;
	}

EARLY_EXIT:
	DBG("<myconnect");
	return s;
}

main(int argc, char **argv)
{
	WSADATA wsaData;
	int rc;
	SOCKET s;

	outfile = stdout;

	if((rc=WSAStartup( MAKEWORD(2,0), &wsaData )))
	{
		perror("Sorry, can't initialize Windows Sockets...");
		DBG("Error code=%d", rc);
		exit(1);
	}


	DBG(">main\n");

	s = myconnect();

	DBG("<main\n");
}
