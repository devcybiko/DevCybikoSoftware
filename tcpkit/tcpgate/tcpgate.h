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
#ifndef _TCPGATE_H_
#define _TCPGATE_H_

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#include "serial.h"
#include "..\tcpmsgs.h"
#include "..\tcplib\tcperror.h"

#define VERSION "1.1.0"

//#define DEBG debug_output
#define DEBG

#define SAME(a,b) (strcmp(a,b)==0)
extern HANDLE tty;
extern FILE *outfile;

extern errexit(char *s);
extern void tcpmsg_read_response(long sockid, long status, long serialno, char *data, int len);
extern void debug_output(char *format, ...);
extern void null_func();

#define MAX_SOCKIDS 64
#define MSG_USER         0x2000
#define MSG_TCP (MSG_USER+256)

typedef int (*Filter_proc)(int sockid, char *msgbuf, int len);

struct sockid_t {
	long port;
	long tcpqueue;
	long socket;
	long cyid;
	char appname[APPNAME_LEN];
	long read_enabled;
	Filter_proc filter_recv;
	Filter_proc filter_send;
	char *filter_data;
	char *msg_data;
	long msg_size;
};

extern struct sockid_t *sockids;

#endif /* _TCPGATE_H_ */