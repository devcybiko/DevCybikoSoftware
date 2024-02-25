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
char *strtok(char *s, char *seps)
{
    static char *last;
    char *r;

    if (s == NULL) s=last;
    r = s;
    while(*s)
    {
        if (strchr(seps, *s))
        {
            *s=0;
            last=s+1;
            return r;
        }
        s++;
    }
    if (*r == 0) return NULL;
    return r;
}

void junction_get()
{
    long tmp[1];
    char nickname[32];

    tmp[0] = 0;
    junction = select_partner_Ex(
        main_module.m_process,
        SGP_NONE,
        nickname,
        "SELECT Quinci JUNCTION",
        tmp);
}

void msg_send(char *s)
{
    send_remote_msg(junction, "quincijunction", MSG_USER, 0, 0, s, strlen(s)+1);
}
