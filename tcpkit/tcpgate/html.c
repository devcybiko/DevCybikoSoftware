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
#include "tcpgate.h"
#include "serial.h"
#include "..\tcpmsgs.h"
#include "..\tcplib\tcperror.h"
#include "html.h"
#include "debug.h"

//
// is it a blank line?
//
static int blank_line(char *s)
{
	while(*s)
	{
		if (isspace(*s)) s++; 
		else return 0;
	}
	return 1;
}

//
// condense multiple whitespace down to one space
//
static void collapse_line(char *s)
{
	while(*s)
	{
		if (isspace(*s) && isspace(s[1])) strcpy(s, s+1);
		else s++;
	}
}

//
// filter data received from a socket
// note: sockid is an index into an array of structures
// note: s is the data that was received
// note: len is the number of bytes in s
//
int filter_recv_html(int sockid, char *s, int len)
{
	//
	// get the html data structure (keeps the state between bits of html)
	//
	struct filter_html_t *html = (struct filter_html_t *) sockids[sockid].filter_data;

	DEBG("filter_recv_html(sockid=%d, s=%s, len=%d\n", sockid, s, len);
	
	//
	// write to the debug file
	//
	fwrite(s, len, 1, outfile);
	fflush(outfile);
	DEBG("Read %d bytes=%s\n", len, s);
	DEBG("\nawaiting ack...\n");

	//printf("READ_RESPONSE");
	while(len>0)
	{
		//
		// check for quotes
		//
		if (*s == '"') html->quotemode = !html->quotemode;

		//
		// check for <..>
		///
		if (!html->quotemode && (*s == '<')) 
		{
			html->inside=1;
			//
			// if its <br> then send the line to the cybiko
			//
			if ((s[1]&0x5f)=='B' && (s[2]&0x5f)=='R')
			{
				html->text[html->len++]=0;
				collapse_line(html->text);
				//
				// all messages coming from cybiko are requests
				// all messages going to cybiko are responses
				//
				tcpmsg_read_response(sockid, 0, 0, html->text, html->len);
				html->len=0;
			}
		}
		if (!html->inside)
		{
			//
			// if we're not inside the <..> its "real" text
			// add it to the buffer
			//
			if (*s >= 32) html->text[html->len++]=*s;

			//
			// if its a newline or we've exceeded the buffer
			// send the buffer
			//
			if (html->len==(sizeof(html->text)-1) || *s == '\n')
			{
				html->text[html->len++]=0;
				if (!blank_line(html->text)) // we dont bother to send blank lines
				{
					//
					// compress the line
					//
					collapse_line(html->text);
					//
					// send it along to the cybiko
					//
					tcpmsg_read_response(sockid, 0, 0, html->text, html->len);
				}
				html->len=0;
			}
		}
		//
		// exiting the <..> mode
		//
		if (!html->quotemode && (*s == '>')) html->inside=0;
		s++; // next character
		len--; // decrement counter
	}
	return 0;
}

//
// no filtering done on outbound data
//
int filter_send_html(int sockid, char *msgbuf, int len)
{
	DEBG("filter_send_html(sockid=%d, msgbuf=%s, len=%d\n", sockid, msgbuf, len);
	return send(sockids[sockid].socket, msgbuf, len, 0);
}
