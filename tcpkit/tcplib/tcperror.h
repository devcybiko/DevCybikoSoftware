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
#ifndef _TCPERROR_H_
#define _TCPERROR_H_

enum {
	TCP_SUCCESS,
	TCP_ERROR,
	TCP_ERROR_MANGLED_MESSAGE,
	TCP_ERROR_MESSAGE_SEND,
	TCP_ERROR_NO_MORE_CLIENT_MSGQUEUES,
	TCP_ERROR_NO_MORE_GATE_SOCKIDS,
	TCP_ERROR_UNINITIALIZED,
	TCP_ERROR_BUFFERLESS,
	TCP_ERROR_WRITE_FAILED,
	TCP_ERROR_SOCKET_FAILED,
	TCP_ERROR_CONNECT_FAILED,
	TCP_ERROR_TIMED_OUT,
	TCP_ERROR_UNKNOWN_MESSAGE,
	TCP_ERROR_UNKNOWN_FILTER,
	TCP_MAX_ERROR};

enum
{
	TCPMSG_CONNECT_REQUEST,
	TCPMSG_CONNECT_RESPONSE,
	TCPMSG_WRITE_REQUEST,
	TCPMSG_WRITE_RESPONSE,
	TCPMSG_CLOSE_REQUEST,
	TCPMSG_CLOSE_RESPONSE,
	TCPMSG_READ_RESPONSE,
	TCPMSG_ACKNOWLEDGE,
	TCPMSG_FILTER_REQUEST,
	TCPMSG_FILTER_RESPONSE,
	TCPMSG_MAX
};

enum
{
	TCP_FILTER_RAW,
	TCP_FILTER_WML,
	TCP_FILTER_HTML,
	TCP_FLITER_MAX
};

#define TCPMSG_MESSAGE_MAX 1024

#endif