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