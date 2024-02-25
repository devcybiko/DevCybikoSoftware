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
//
// quincichat.c
// gregory l. smith
// 11/14/2001
//

#include "quincichat.h"
int working=1;

//
// main
//
main()
{
	icq_Link *icqlink=NULL;
	HANDLE tty;
	char *buf;
	int keep_alive=0;

	DBG(">main\n");

	icq_LogLevel=0;

	printf("QuinciChat Version 1.2.0\n");
	printf("By Gregory Smith\n");
	printf("Copyright 2001 by The Alcor Group, Inc.\n");

	tty = serial_new();
	while(working)
	{
		buf = serial_read(tty);
		if (buf) junction_dispatch(tty, &icqlink, buf);
		if (icqlink) icq_Main();
		keep_alive++;
		if ((keep_alive > 500000) && icqlink)
		{
			icq_KeepAlive(icqlink);
			keep_alive=0;
			printf("...Keepalive sent\n");
		}
	}
	icq_LinkDelete(icqlink);
	DBG("<main\n");
	return 0;
}
