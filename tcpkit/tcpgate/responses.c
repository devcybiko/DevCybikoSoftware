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

void swap_chdr(struct tcpgc_hdr *hdr)
{
	hdr->msgid = serial_swaplong(hdr->msgid);
	hdr->serialno = serial_swaplong(hdr->serialno);
	hdr->status = serial_swaplong(hdr->status);
}

void tcpmsg_send_data(long sockid, long tcpqueue, char *data, long len)
{
	struct tcpgj_header *msg;
	int acklen=0;
	static to_cybiko_ctr=0;

	DEBG("tcpmsg_send_data(sockid=%d, tcpqueue=%d data=%s len=%d)\n",
		sockid, tcpqueue,data,len);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);

	msg = malloc(sizeof(struct tcpgj_header)+len);
	strcpy(msg->appname, sockids[sockid].appname);
	msg->cyid = sockids[sockid].cyid;
	if (tcpqueue == 0)
		msg->msg_queue = sockids[sockid].tcpqueue;
	else
		msg->msg_queue = tcpqueue;
	DEBG("  Sockid=%d\n", sockid);
	DEBG("  Sending to queue %d\n", msg->msg_queue);
	memcpy(msg->data, data, len);

#ifdef CYBIKO_RF_ACK
	sockids[sockid].read_enabled++;  // disable reading from the socket until cybiko ACKs
#endif

	msg->cyid = serial_swaplong(msg->cyid);
	msg->msg_queue = serial_swaplong(msg->msg_queue);
	printf("<%d ", to_cybiko_ctr);
	DEBG(" <%d\n", to_cybiko_ctr);
	to_cybiko_ctr++;
	serial_send(tty, (char *)msg, sizeof(struct tcpgj_header)+len);
	free(msg);
}

void tcpmsg_connect_response(long sockid, long status, long serialno)
{
	struct tcpgc_connect_response cr;

	DEBG("tcpmsg_connect_response(sockid=%d, status=%d serialno=%d)\n",
		sockid, status, serialno);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	cr.hdr.serialno = serialno;
	cr.hdr.status = status;
	cr.hdr.msgid = TCPMSG_CONNECT_RESPONSE;
	cr.sockid = sockid;
	cr.tcpqueue = sockids[sockid].tcpqueue;

	swap_chdr(&cr.hdr);
	cr.sockid = serial_swaplong(cr.sockid);
	cr.tcpqueue = serial_swaplong(cr.tcpqueue);
	tcpmsg_send_data(sockid, 0, (char *)&cr, sizeof(cr));
}

void tcpmsg_read_response(long sockid, long status, long serialno, char *data, int len)
{
	int rrlen=sizeof(struct tcpgc_read_response) + len;
	struct tcpgc_read_response *rr = malloc(rrlen);

	DEBG("tcpmsg_read_response(sockid=%d status=%d serialno=%d data=%s len=%d)\n",
		sockid, status, serialno, data, len);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	rr->hdr.serialno = serialno;
	rr->hdr.status = status;
	rr->hdr.msgid = TCPMSG_READ_RESPONSE;
	rr->len = len;
	rr->tcpqueue = sockids[sockid].tcpqueue;
	memcpy(rr->data, data, len);

	swap_chdr(&rr->hdr);
	rr->len = serial_swaplong(rr->len);
	rr->tcpqueue = serial_swaplong(rr->tcpqueue);
	tcpmsg_send_data(sockid, 0, (char *)rr, rrlen);
	free(rr);
}

void tcpmsg_write_response(long sockid, long status, long serialno)
{
	struct tcpgc_write_response wr;

	DEBG("tcpmsg_write_response(sockid=%d status=%d serialno=%d)\n",
		sockid, status, serialno);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	wr.hdr.serialno = serialno;
	wr.hdr.status = status;
	wr.hdr.msgid = TCPMSG_WRITE_RESPONSE;
	wr.tcpqueue = sockids[sockid].tcpqueue;

	swap_chdr(&wr.hdr);
	wr.tcpqueue = serial_swaplong(wr.tcpqueue);
	tcpmsg_send_data(sockid, 0, (char *)&wr, sizeof(wr));
}

void tcpmsg_close_response(long sockid, long status, long serialno)
{
	struct tcpgc_close_response cr;

	DEBG("tcpmsg_close_response(sockid=%d, status=%d, serialno=%d)\n",
		sockid, status, serialno);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	cr.hdr.serialno = serialno;
	cr.hdr.status = status;
	cr.hdr.msgid = TCPMSG_CLOSE_RESPONSE;
	cr.tcpqueue = sockids[sockid].tcpqueue;

	swap_chdr(&cr.hdr);
	cr.tcpqueue = serial_swaplong(cr.tcpqueue);
	tcpmsg_send_data(sockid, 0, (char *)&cr, sizeof(cr));
}

void tcpmsg_filter_response(long sockid, long status, long serialno)
{
	struct tcpgc_filter_response cr;

	DEBG("tcpmsg_filter_response(sockid=%d, status=%d, serialno=%d)\n",
		sockid, status, serialno);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	cr.hdr.serialno = serialno;
	cr.hdr.status = status;
	cr.hdr.msgid = TCPMSG_FILTER_RESPONSE;
	cr.tcpqueue = sockids[sockid].tcpqueue;

	swap_chdr(&cr.hdr);
	cr.tcpqueue = serial_swaplong(cr.tcpqueue);
	tcpmsg_send_data(sockid, 0, (char *)&cr, sizeof(cr));
}

void tcpmsg_status_response(long sockid, long status)
{
	struct tcpgc_status_response sr;

	DEBG("tcpmsg_status_response(sockid=%d, status=%d)\n",
		sockid, status);
	DEBG("  sockid=%d socket=%d\n", sockid, sockids[sockid].socket);
	sr.status = serial_swaplong(status);
	tcpmsg_send_data(sockid, 0, (char *)&sr, sizeof(sr));
}

