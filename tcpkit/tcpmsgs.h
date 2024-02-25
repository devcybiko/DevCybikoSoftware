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
#ifndef _TCPMSGS_H_
#define _TCPMSGS_H_

#define APPNAME_LEN 16

/**************************************
 **
 ** CLIENT TO GATE MESSAGES
 **
 **************************************/

/** message header **/
struct tcpclient_header {
	long serialno;
	long sockid;
	long msgid;
};

struct tcpcg_connect_request {
	struct tcpclient_header hdr;
	long cyid;
	long port;
	long tcpqueue;
	long size;
	char appname[APPNAME_LEN];
	char addr[0];
};

struct tcpcg_write_request {
	struct tcpclient_header hdr;
	char data[0];
};

struct tcpcg_close_request {
	struct tcpclient_header hdr;
};

struct tcpcg_filter_request {
	struct tcpclient_header hdr;
	long filter_type;
};

struct tcpcg_acknowledge {
	struct tcpclient_header hdr;
};

/**************************************
 ** 
 ** GATE TO JUNCTION MESSAGES
 **
 **************************************/
struct tcpgj_header {
	long msg_queue;
	long cyid;
	char appname[APPNAME_LEN];
	char data[0];
};

/***************************************
 **
 ** GATE TO CLIENT MESSAGES
 **
 ***************************************/
struct tcpgc_hdr {
	long msgid;
	long status;
	long serialno;
};

struct tcpgc_connect_response {
	struct tcpgc_hdr hdr;
	long tcpqueue;
	long sockid;
};

struct tcpgc_close_response {
	struct tcpgc_hdr hdr;
	long tcpqueue;
};

struct tcpgc_filter_response {
	struct tcpgc_hdr hdr;
	long tcpqueue;
};

struct tcpgc_write_response {
	struct tcpgc_hdr hdr;
	long tcpqueue;
};

struct tcpgc_read_response {
	struct tcpgc_hdr hdr;
	long tcpqueue;
	long len;
	char data[0];
};

struct tcpgc_status_response {
	struct tcpgc_hdr hdr;
	long status;
};

#endif /* _TCPMSGS_H_ */