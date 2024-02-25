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
static struct MSequence *seq=0;
void music_play(char *filename)
{
    if (seq == (struct MSequence *) NULL)
    {
        seq=(struct MSequence *)malloc(sizeof(struct MSequence));
        MSequence_ctor(seq, filename);
    }
    else
    {
        MSequence_dtor(seq, LEAVE_MEMORY);
        MSequence_ctor(seq, filename);
    }
    MSequence_play(seq);
}

void music_free()
{
    if (seq) MSequence_dtor(seq, FREE_MEMORY);
}