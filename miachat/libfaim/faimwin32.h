#ifdef _WIN32
//already in aim.h #define close closesocket        //potentially unsafe: CHECK!!!
#define random rand
#define errno WSAGetLastError()	 //potentially unsafe: CHECK!!!
#define errno_set(x)  WSASetLastError(x)
#define EINPROGRESS WSAEINPROGRESS
#define ETIMEDOUT   WSAETIMEDOUT
#define F_SETFL    1
#define F_GETFL    2
#define O_NONBLOCK 1
static int fcntl(SOCKET fd,int flag,int value)
{
	switch(flag) {
		case F_SETFL:
		{	unsigned long nonBlock;
			if(value&O_NONBLOCK) nonBlock=1;
			else nonBlock=0;
		    ioctlsocket(fd, FIONBIO, &nonBlock);
			return 0;
		}
		case F_GETFL:
			//can't see how to get the state of the blocking flag, so we'll assume blocking by default
			return 0;
	}
	return 0;
}

struct utsname {
	char nodename[256];
};

static int uname(struct utsname *uts)
{
	gethostname(uts->nodename,sizeof(uts->nodename));
	return 0;
}
#else
#define errno_set(x) errno=x
#endif