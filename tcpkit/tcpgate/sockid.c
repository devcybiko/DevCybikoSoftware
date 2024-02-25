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
#include "tcpgate.h"

long alloc_sockid()
{
	int i;
	for(i=1; i<MAX_SOCKIDS; i++)
	{
		if (sockids[i].tcpqueue == 0) 
		DEBG(">alloc_sockid()=%d\n", i);
		return i;
	}
	DEBG(">alloc_sockid()=0\n");
	return 0;
}

void free_sockid(long sockid)
{
	if (sockids[sockid].filter_data) free(sockids[sockid].filter_data);
	if (sockids[sockid].msg_data) free(sockids[sockid].msg_data);
	memset(&sockids[sockid], 0, sizeof(sockids[sockid]));
}

