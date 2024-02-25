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
#include "email.h"
#include "pop3.h"
#include "..\tcplib.h"
#include "..\tcperror.h"

static char buf[1024];

struct Pop3Data {
	char username[64];
	char password[64];
};

struct Pop3Data pop3Data;

int pop3_open(char *hostname, char *username, char *password) {

	strcpy(pop3Data.username, username);
	strcpy(pop3Data.password, password);

	TRACE("hostname=%s", hostname);
	TRACE("username=%s", username);
	TRACE("password=%s", password);
	if (tcpqueue) tcp_close(tcpqueue);
	tcpqueue = tcp_connect(hostname, 110, 512, pop3_handler, &pop3Data);

	return 0;
}

int pop3_list() {

	return 0;
}

int pop3_handler(int tcpqueue, char *data, char *user_data)
{
	switch(tcp_msgid(data)) {
		case TCPMSG_WRITE_RESPONSE: 
		{
			tcp_write_accept(data); 
			break;
		}
		case TCPMSG_CLOSE_RESPONSE: 
		{
			tcp_close_accept(data); 
			tcpqueue = 0;
			break;
		}
		case TCPMSG_FILTER_RESPONSE: 
		{
			break;
		}
		case TCPMSG_CONNECT_RESPONSE:
		{
			tcp_connect_accept(data);
			if (tcp_errno)
			{
				TRACE("ERROR DETECTED");
				tcp_close(tcp_tcpqueue(data));
				break;
			}
			sprintf(buf, "USER %s\n", pop3Data.username);
			tcp_write(tcpqueue, buf, strlen(buf));
			sprintf(buf, "PASS %s\n", pop3Data.password);
			tcp_write(tcpqueue, buf, strlen(buf));
			break;
		}
		case TCPMSG_READ_RESPONSE:
		{
			int i;
			char *s;
			long llen;
			short len;
			TRACE("READ_RESPONSE");
			tcp_read_accept(data);
			s = tcp_getdata(data, &llen);
			len = (short) llen;
			TRACE("%d: '%s'", len, s);
			break;
		}
		default:
		{
		}
	}
	return 0;
}

