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
#include <windows.h>
#include <stdio.h>

#include "tcpgate.h"

static char serial_buf[1024]={0};

#define END 0300
#define ESC 0333
#define ESC_END 0334
#define ESC_ESC 0335
#define CHUNK_SIZE 32

static void null_func() {}

void serial_flush(HANDLE tty)
{
	int c;
	int true = 1;
	int rc;
	int nbytes;

	while(true)
	{
		rc = ReadFile(tty, &c, 1, &nbytes, NULL);
		if (rc==0)
		{
			printf("Error in ReadFile=%d\n", GetLastError());
			exit(0);
		}
		if (nbytes == 0) return;
	}
}

long serial_swaplong(long x)
{
	char *y = (char *)&x;
	char tmp;

	tmp = y[0];
	y[0] = y[3];
	y[3] = tmp;
	tmp = y[1];
	y[1] = y[2];
	y[2] = tmp;
	return x;
}

short serial_swapshort(short x)
{
	char *y = (char *)&x;
	char tmp;

	tmp = y[0];
	y[0] = y[1];
	y[1] = tmp;
	return x;
}

HANDLE serial_new(char *comport)
{
	HANDLE tty;
	int rc;
	DCB dcb;
	COMMTIMEOUTS timeout;

	tty = CreateFile(comport,
					GENERIC_READ | GENERIC_WRITE,
					0, // exclusive access
					NULL, //no security attrs
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);

	if (tty == INVALID_HANDLE_VALUE)
	{
		printf("Could not CreateFile for %s\n", comport);
		exit(1);
	}

	rc = SetCommMask(tty, 0);
	if (rc == 0)
	{
		printf("error setting comm mask\n");
		exit(1);
	}

	memset(&dcb, 0, sizeof(dcb));
	GetCommState(tty, &dcb);
	dcb.BaudRate=CBR_9600;
	rc=SetCommState(tty, &dcb);
	if (rc==0)
	{
		printf("SetCommState error\n");
		exit(1);
	}

	timeout.ReadIntervalTimeout=MAXDWORD;
	timeout.ReadTotalTimeoutConstant=0;
	timeout.ReadTotalTimeoutMultiplier=0;
	timeout.WriteTotalTimeoutConstant=0;
	timeout.WriteTotalTimeoutMultiplier=0;
	rc=SetCommTimeouts(tty, &timeout);

	memset(serial_buf, 0, sizeof(serial_buf));

	serial_flush(tty);

	return tty;
}

static void MyWriteFile(HANDLE tty, char *c, long n, long *b, void *xxx) 
{
   if (!WriteFile(tty, c, n, b, NULL)) 
   {
      printf("----ERROR WRITING SERIAL ---- %d\n", GetLastError());
   } 
}

void serial_send_byte(HANDLE tty, char c)
{
	char end=(char)END;
	char esc=(char)ESC;
	char esc_end=(char)ESC_END;
	char esc_esc=(char)ESC_ESC;
	int nbytes;

	if (c == end) {
		c = (char)ESC;
		MyWriteFile(tty, &c, 1, &nbytes, NULL);
		c = (char)ESC_END;
		MyWriteFile(tty, &c, 1, &nbytes, NULL);
	}
	else if (c == esc)
	{
		c = (char)ESC;
		MyWriteFile(tty, &c, 1, &nbytes, NULL);
		c = (char)ESC_ESC;
		MyWriteFile(tty, &c, 1, &nbytes, NULL);
	}
	else
	{
		MyWriteFile(tty, &c, 1, &nbytes, NULL);
	}
}

void serial_send(HANDLE tty, char *buf, int len)
{
	int retry;
	int i;
	long checksum=0;
	char *cp;
	unsigned char c;
	int nbytes;


	for(retry=0; retry<16; retry++) { 
		DBG("sending retry=%d len=%d %s\n", retry, len, buf);
		c = (char)END;
		MyWriteFile(tty, &c, 1, &nbytes, NULL);
		checksum = 0;
		for(i=0; i<len; i++)
		{
			checksum += buf[i];
			serial_send_byte(tty, buf[i]);
			if (((i % CHUNK_SIZE) == 0) && i) Sleep(100); // delay to let cybiko to read serial port **HACK**
		}
		DBG("...Checksum=%d", checksum);
		checksum = serial_swaplong(checksum);

		cp = (char *)&checksum;
		serial_send_byte(tty, cp[0]);
		serial_send_byte(tty, cp[1]);
		serial_send_byte(tty, cp[2]);
		serial_send_byte(tty, cp[3]);
		c = (char)END;
		MyWriteFile(tty, &c, 1, &nbytes, NULL);

		// get a ack/nack
		nbytes = 0;
		while(nbytes == 0)
		{
			int rc;
			rc = ReadFile(tty, &c, 1, &nbytes, NULL);
			if (rc==0)
			{
				printf("Error in ReadFile=%d\n", GetLastError());
				exit(0);
			}
			if (nbytes == 0) Sleep(10); //waiting for a ack/nack
		}
		if (c == 0x82) 
		{
			printf("NACK Received... Resending....\n");
			Sleep(100*retry);
			continue; // resend
		}
		else if (c == 0x81)
		{
			printf("ACK Received!\n");
			break; // exit function
		}
		else if (c == 0xc0)
		{
			printf("Incoming Message - ACK Cancelled\n");
			break; // exit function
		}
		else
		{
			printf(">>>ACK ERROR<<< %02x(%c) Received\n", c, c>32?c:' ');
			serial_flush(tty);
			break; // exit function
		}
	}
	printf("xxxx done\n");
}

static int bufptr=0;

char *serial_read(HANDLE tty, int *len)
{
	char c;
	int rc;
	int nbytes;
	int true = 1;
	char end=(char)END;
	char esc=(char)ESC;
	char esc_end=(char)ESC_END;
	char esc_esc=(char)ESC_ESC;

	while(true)
	{
		rc = ReadFile(tty, &c, 1, &nbytes, NULL);
		if (rc==0)
		{
			printf("Error in ReadFile=%d\n", GetLastError());
			exit(0);
		}
		if (nbytes == 0) return NULL;
		if (c == end)
		{
			DBG("END\n");
			if (bufptr == 0) return NULL;
			*len = bufptr;
			bufptr = 0;
			return serial_buf;
			break;
		}
		else if (c == esc)
		{
			DBG("ESC\n");
			if (c == esc_end) 
			{
				DBG("ESC_END\n");
				c=(char)end;
			}
			else if (c == esc_esc)
			{
				DBG("ESC_ESC\n");
				c=(char)esc;
			}
		}
		else
		{
			//DBG("%c %d\n", c, c);
			if (bufptr < sizeof(serial_buf))
				serial_buf[bufptr++] = c;
		}
	}
	return NULL;
}
