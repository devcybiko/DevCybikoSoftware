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
void load(char *filename)
{
	struct Input *in;
	struct FileOutput *out;
	struct Archive *archive = main_module.m_process->module->archive;
	int c;

	sprintf(tmp, "/%s/%s", DEFAULT_DRIVE_NAME, filename);
    if (File_exists(tmp)) return;

	in = Archive_open_Ex(archive, filename);
	out = malloc(sizeof(struct FileOutput));
	FileOutput_ctor_Ex(out,filename, 1); // create the file

	while(!Input_is_eof(in))
	{
		c = Input_read_byte(in);
		FileOutput_write_byte(out, c);
	}

    FileOutput_dtor(out, FREE_MEMORY);
	Input_dtor(in, FREE_MEMORY);
}
