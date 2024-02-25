/**
  * The MiaChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the AIM protocol.
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
#ifndef _MIACHAT_H_
#define _MIACHAT_H_

#include "junction.h"
#include "serial.h"

#define VERSION "2.0.0"

typedef unsigned int fu16_t;
typedef unsigned char fu8_t;
typedef unsigned long fu32_t;

//#define DBG printf
#define DBG

#define SAME(a,b) (strcmp(a,b)==0)
#define MSG_LEN 2048
/* The above should normally be the same as BUF_LEN,
 * but just so we're explictly asking for the max message
 * length. */
#define BUF_LEN MSG_LEN
#define BUF_LONG BUF_LEN * 2
#define AIM_MAX_FILE_SIZE 98304

extern struct aim_session_t session;
extern struct aim_conn_t *conn;
extern char global_sn[20];
extern char global_passwd[20];
extern HANDLE tty;
extern char msgbuf[1024];

extern errexit(char *s);

#endif /* _MIACHAT_H_ */