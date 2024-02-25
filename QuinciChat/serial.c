/**
  * The QuinciChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the ICQ protocol.
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
#include "quincichat.h"

static char serial_buf[1024]={0};

HANDLE serial_new()
{
	HANDLE tty;
	int rc;
	DCB dcb;
	COMMTIMEOUTS timeout;

	tty = CreateFile("com1",
					GENERIC_READ | GENERIC_WRITE,
					0, // exclusive access
					NULL, //no security attrs
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
	if (tty == INVALID_HANDLE_VALUE)
	{
		printf("Could not CreateFile for COM1\n");
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
	dcb.BaudRate=CBR_56000;
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

	return tty;
}

void serial_send(HANDLE tty, char *buf)
{
	int nbytes;
	WriteFile(tty, buf, strlen(buf)+1, &nbytes, NULL);
}

static int bufptr=0;

char *serial_read(HANDLE tty)
{
	char c;
	int rc;
	int nbytes;

	rc = ReadFile(tty, &c, 1, &nbytes, NULL);
	if (rc==0)
	{
		printf("Error in ReadFile=%d\n", GetLastError());
		exit(0);
	}
	if (nbytes==0) return NULL;
	serial_buf[bufptr++]=c;
	if (c == 0) 
	{
		bufptr=0;
		return serial_buf;
	}
	return NULL;
}
