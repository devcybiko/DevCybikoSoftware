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
#ifndef _TCPLIB_H_
#define _TCPLIB_H_

typedef int (*TCP_Msg_Handler)(int tcpqueue, char *data, char *user_data);
typedef int (*TCP_Cybiko_Handler)(struct Message *);
long tcp_init(struct module_t *main_module);
long tcp_connect(char *addr, long port, long size, TCP_Cybiko_Handler handler, char *data);
long tcp_write(long tcpqueue, char *data, int len);
long tcp_close(long tcpqueue);
long tcp_dispatch(void *xx);
long tcp_ack(long tcpqueue);
long tcp_filter(long tcpqueue, long filter_type);

long tcp_connect_accept(void *cr);
long tcp_write_accept(void *wr);
long tcp_close_accept(void *cr);
char *tcp_read_accept(void *rr);
long tcp_filter_accept(void *xx);

long tcp_swaplong(long x);
short tcp_swapshort(short x);

long tcp_msgid(void *xx);
long tcp_tcpqueue(void *xx);
char *tcp_getdata(void *xx, long *len);
long tcp_get_message(int delay, TCP_Cybiko_Handler handler);
long tcp_process_message(struct Message *msg);

extern long tcp_errno;
extern long tcp_timeout;
extern long tcp_serialno;

#define MSG_TCP (MSG_USER+256)
#define TCP_STATUS (MSG_TCP)
#define TCP_MAX_TCPQUEUES 64

#endif