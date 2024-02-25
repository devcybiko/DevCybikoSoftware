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
#include "responses.h"
#include "requests.h"
#include "sockid.h"
#include "debug.h"

HANDLE tty;
FILE *outfile;

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

struct sockid_t *sockids;

void null_func() {}

main(int argc, char **argv)
{
	char *buf;
	int len;
	int lastnop=0;
	char comport[32];
	int msgid;
	int i;
	int j=0;
	int socrcv_ctr=0;
	int from_cybiko_ctr=0;

	WSADATA wsaData;
	int rc;

	outfile = fopen("test.log", "w");
	sockids = calloc(MAX_SOCKIDS, sizeof(struct sockid_t));

	if((rc=WSAStartup( MAKEWORD(2,0), &wsaData )))
	{
		perror("Sorry, can't initialize Windows Sockets...");
		DEBG("Error code=%d", rc);
		exit(1);
	}

	strcpy(comport, "com1");

	DEBG(">main\n");
	printf("TcpGate Version %s\n", VERSION);
	printf("By Gregory Smith\n");
	printf("Copyright 2002 by The Alcor Group, Inc.\n");
	printf("}### = messages from socket\n");
	printf("{### = messages to socket\n");
	printf(">### = messages received from cybiko\n");
	printf("<### = messages sent to cybiko\n");

	if (argv[1])
		sprintf(comport, "com%s", argv[1]);
	
	tty = serial_new(comport);

	while(1)
	{
		long readfd=0;
		buf = serial_read(tty, &len);
		if (buf)
		{
			struct tcpclient_header *hdr;
			hdr = (struct tcpclient_header *) buf;
			DEBG("Buf Received: (%d)\n", len, buf);
			msgid = serial_swaplong(hdr->msgid);
			printf("FROM CYBIKO:%d\n", from_cybiko_ctr); 
			dump(buf, len);
			DEBG(" >%d\n", from_cybiko_ctr);
			from_cybiko_ctr++;
			switch(msgid) {
			case TCPMSG_CONNECT_REQUEST:
				DEBG("TCPMSG_CONNECT_REQUEST\n");
				if (len >= sizeof(struct tcpcg_connect_request))
					tcpmsg_connect_request((struct tcpcg_connect_request *) hdr);
				else
					printf("ERROR: Invalid Size Buffer %d (CONNECT)\n", len);
				break;
			case TCPMSG_WRITE_REQUEST:
				DEBG("TCPMSG_WRITE_REQUEST\n");
				if (len > sizeof(struct tcpcg_write_request))
					tcpmsg_write_request((struct tcpcg_write_request *) hdr, len);
				else
					printf("ERROR: Invalid Size Buffer %d (WRITE)\n", len);
				break;
			case TCPMSG_CLOSE_REQUEST:
				DEBG("TCPMSG_CLOSE_REQUEST\n");
				if (len == sizeof(struct tcpcg_close_request))
					tcpmsg_close_request((struct tcpcg_close_request *) hdr);
				else
					printf("ERROR: Invalid Size Buffer %d (CLOSE)\n", len);
				break;
			case TCPMSG_FILTER_REQUEST:
				DEBG("TCPMSG_FILTER_REQUEST\n");
				if (len == sizeof(struct tcpcg_filter_request))
					tcpmsg_filter_request((struct tcpcg_filter_request *) hdr);
				else
					printf("ERROR: Invalid Size Buffer %d (FILTER)\n", len);
				break;
			case TCPMSG_ACKNOWLEDGE:
				DEBG("TCPMSG_ACKNOWLEDGE\n");
				if (len == sizeof(struct tcpcg_acknowledge))
					tcpmsg_acknowledge((struct tcpcg_acknowledge *) hdr);
				else
					printf("ERROR: Invalid Size Buffer %d (ACKNOWLEDGE)\n", len);
				break;
			default:
			{
				int i;
				printf("FROM CYBIKO: UNKNOWN MSGID=%d\n", msgid);
				dump((char *)hdr, len);
				// if the message was a ACK then we need to decrement it here
				// if it was something else no serious damage is done by decrementing now
				// in the worst case it will result in decrementing too often
				// which means we'll read the socket a little more frequently
				// for a second or two. it will work itself out as long as we dont
				// get too many UNKNOWNS
				// the only real challenge is that we dont know which cybiko goofed up
				// so we have to decrement ALL the read_enabled counters. sound goofy,
				// well it is and we wouldnt have to do this if not for poor cybiko's
				// weak serial port
				for(i=0; i<MAX_SOCKIDS; i++)
				{
					sockids[i].read_enabled--;
					if (sockids[i].read_enabled < 0) sockids[i].read_enabled = 0;
				}
			}
			}
		}

		for(i=0; i<MAX_SOCKIDS; i++)
		{
			if (sockids[i].socket)
			{
#ifdef CYBIKO_RF_ACK
				if (sockids[i].read_enabled==0)
#else
				if (true)
#endif
				{
					struct timeval tv;

					tv.tv_sec = 0;
					tv.tv_usec = 0;
					//DEBG(".sockid=%d socket=%d filter_recv=%08x\n", 
					//	i, sockids[i].socket, sockids[i].socket);
					len = recv(sockids[i].socket, sockids[i].msg_data, sockids[i].msg_size, 0);
					DEBG("len=%d\n", len);
					if (len < 0) { //Probably an WSAEWOULDBLOCK meaning there are no bytes to read
						//int rc = WSAGetLastError();
						//DEBG("ERROR - recv failed\n");
						//print_error(rc);
					}
					else if (len == 0) // socket was closed by remote host
					{
						tcpmsg_close_response(i, TCP_SUCCESS, 0);
						free_sockid(i);
					}
					else if (len > sockids[i].msg_size) // what the heck???
					{
						DEBG("Number of bytes reported from recv() is %d but bufsize is only %d\n",
							len, sockids[i].msg_size);
					}
					else if (sockids[i].filter_recv) // if a filter is specified (There is always a filter)
					{
						printf("FROM SOCKET: %d %d\n", socrcv_ctr, len);
						dump(sockids[i].msg_data, len);
						DEBG(" }%d\n", socrcv_ctr);
						socrcv_ctr++;
						sockids[i].msg_data[sockids[i].msg_size] = 0; // null terminate as a courtesy for html
						sockids[i].filter_recv(i, sockids[i].msg_data, len); //call the filter with the data
					} else {
						printf("HEY! NO FILTER SPECIFIED\n");
						DEBG("HEY! NO FILTER SPECIFIED\n");
					}

				}
				else
				{
				}
			}
		}
		Sleep(1); // a little context switching
	}
	DEBG("<main\n");
}
