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
#include "debug.h"

int filter_recv_raw(int sockid, char *msgbuf, int len)
{
	DEBG("filter_recv_raw(sockid=%d, msgbuf=%s, len=%d\n", sockid, msgbuf, len);
	tcpmsg_read_response(sockid, 0, 0, msgbuf, len);
	DEBG("Read %d bytes=%s\n", len, msgbuf);
	DEBG("\nawaiting ack...\n");
	return 0;
}

int filter_send_raw(int sockid, char *msgbuf, int len)
{
	DEBG("filter_send_raw(sockid=%d, msgbuf=%s, len=%d\n", sockid, msgbuf, len);
	return send(sockids[sockid].socket, msgbuf, len, 0);
}
