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
#include "../libfaim/aim.h"

#include "miachat.h"

struct aim_session_t session;
struct aim_conn_t *conn;
HANDLE tty;
char global_sn[20];
char global_passwd[20];
char msgbuf[1024];

errexit(char *s)
{
	printf("%s", s);
	exit(0);
}

main(int argc, char **argv)
{
	int rc;
	char *buf;
	int lastnop=0;
	char comport[32];
	strcpy(comport, "com1");
	conn = 0;

	DBG(">main\n");
	printf("MiaChat Version %s\n", VERSION);
	printf("By Gregory Smith\n");
	printf("Copyright 2001 by The Alcor Group, Inc.\n");

	if (argv[1])
		sprintf(comport, "com%s", argv[1]);
	
	tty = serial_new(comport);

	while(1)
	{
		buf = serial_read(tty);
		if (buf) junction_dispatch(tty, buf);

		if (conn)
		{
			if (time(NULL)-lastnop > 30) 
			{
				lastnop = time(NULL);
				//aim_flap_nop(&session, aim_getconn_type(&session, AIM_CONN_TYPE_BOS));
				aim_flap_nop(&session, conn);
			}
			rc = aim_get_command(&session, conn);
			//if (rc<0) errexit("ERROR: aim_get_command\n");
			aim_rxdispatch(&session);
			//printf(". fd=%d", conn->fd);
		}
		Sleep(10);
	}
	DBG("<main\n");
}
