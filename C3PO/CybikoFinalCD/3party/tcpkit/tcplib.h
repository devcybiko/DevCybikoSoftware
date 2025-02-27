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

extern long tcp_errno;
extern long tcp_timeout;
extern long tcp_serialno;

#define MSG_TCP (MSG_USER+256)
#define TCP_STATUS (MSG_TCP)
#define TCP_MAX_TCPQUEUES 64

#endif