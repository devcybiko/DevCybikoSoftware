/**
  * The B2C project is a set of programs and libraries
  * that comprise a languate translator.  B2C compiles
  * a BASIC program into C which is compiled by the Cybiko
  * SDK 2.10 into an application.
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
void _mid(char *a, char *b, int start, int len)
{
    if (len >= 0)
    {
        strncpy(a, &b[start], len);
        a[len] = 0;
    }
    else
    {
        strcpy(a, &b[start]);
    }
}

void _right(char *a, char *b, int len)
{
    if (len > 0)
    {
        int x = strlen(b) - len;
        strcpy(a, &b[x]);
    }
}

void _sprint(char *var, char *fmt, ...)
{
    va_list parameters;

    va_start( parameters, fmt );
    vsprintf( var, fmt, parameters );
    va_end( parameters );

    DBG("<_sprint");
}

void _tokenize(char *s, char *seps, ...)
{
	va_list parameters;
	char *var;

	va_start( parameters, seps);
	while(var = va_arg(parameters, char *))
	{
		while(*s && (strchr(seps, *s)==0))
		{
			*var = *s;
			var++;
			s++;
		}
		*var = 0;
		if (*s) s++;
	}
	va_end(parameters);
}
