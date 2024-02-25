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
static void init_fileio()
{
}

static void destroy_fileio()
{
	int i;

    for(i=0; i<MAX_FILES; i++)
    {
        if (b2c->files[i]) _close(i);
    }
	if (b2c->find_in_progress)
	{
		File_dtor(&b2c->file_info, LEAVE_MEMORY);
		FileFind_dtor(&b2c->searcher, LEAVE_MEMORY);
	}
}

void _close(int filenum)
{
	error = 0;
    if (filenum < 0 || filenum > MAX_FILES-1)
	{
        error = ERROR_FILE_NUMBER;
		return;
	}
    if (b2c->files[filenum] == (void *) NULL)
	{
        error = ERROR_FILE_ALREADY_CLOSED;
		return;
	}
    if (b2c->file_modes[filenum] == MODE_READ)
        FileInput_dtor( b2c->files[filenum], LEAVE_MEMORY );
    else if (b2c->file_modes[filenum] == MODE_ARCHIVE)
        Input_dtor( b2c->files[filenum], LEAVE_MEMORY );
    else if (b2c->file_modes[filenum] == MODE_WRITE)
        FileOutput_dtor( b2c->files[filenum], LEAVE_MEMORY );
    else if (b2c->file_modes[filenum] == MODE_APPEND)
		FileOutput_dtor( b2c->files[filenum], LEAVE_MEMORY );
    free(b2c->files[filenum]);
    b2c->files[filenum] = NULL;
}

void _open(int mode, char *filename, int filenum)
{
	error = 0;
    if (filenum < 0 || filenum > MAX_FILES-1)
	{
		error = ERROR_FILE_NUMBER;
		return;
	}
    if (b2c->files[filenum] != (void *) NULL)
	{
		error = ERROR_FILE_ALREADY_OPEN;
		return;
	}

    switch(mode)
    {
        case MODE_ARCHIVE: {
            struct Input *infile;
            if (infile = open_resource_Ex(filename))
            {
                b2c->files[filenum] = infile;
                b2c->file_modes[filenum] = mode;
            }
            else
            {
				error = ERROR_FILE_OPEN;
				return;
            }
            break;
        }
        case MODE_READ: {
            struct FileInput *infile;
            infile = malloc(sizeof(struct FileInput));
            FileInput_ctor(infile);
            if (FileInput_open(infile, filename))
            {
                b2c->files[filenum] = infile;
                b2c->file_modes[filenum] = mode;
            }
            else
            {
				free(infile);
				error = ERROR_FILE_OPEN;
				return;
            }
            break;
        }
        case MODE_WRITE: {
            struct FileOutput *outfile;
            outfile = malloc(sizeof(struct FileOutput));
            FileOutput_ctor(outfile);
            if( FileOutput_open(outfile, filename, TRUE ) )
            {
                FileOutput_truncate(outfile, 0);
                b2c->files[filenum] = outfile;
                b2c->file_modes[filenum] = mode;
            }
            else
            {
				free(outfile);
				error = ERROR_FILE_CREATE;
				return;
            }
            break;
        }
        case MODE_APPEND: {
            struct FileOutput *outfile;
            outfile = malloc(sizeof(struct FileOutput));
            FileOutput_ctor(outfile);
            if( FileOutput_open(outfile, filename, TRUE ) )
            {
                b2c->files[filenum] = outfile;
                b2c->file_modes[filenum] = mode;
                FileOutput_seek(outfile, 0, SEEK_END );
            }
            else
            {
				error = ERROR_FILE_OPEN;
				return;
            }
            break;
        }
        default : {
            TRACE("...INTERNAL ERROR IN OPEN - UNKNOWN MODE - %d", mode);
        }
    }
}

int _eof(int filenum)
{
    if (filenum < 0 || filenum > MAX_FILES-1)
	{
		error = ERROR_FILE_NUMBER;
		return 0;
	}
    if (b2c->files[filenum] == (void *) NULL)
	{
		error = ERROR_FILE_UNOPENED;
		return 0;
	}
    return FileInput_is_eof(b2c->files[filenum]);
}

void _put(int filenum, long filepos, void *data, int size)
{
	error = 0;

    if (filenum < 0 || filenum > MAX_FILES-1)
	{
		error = ERROR_FILE_NUMBER;
		return;
	}
    if (b2c->files[filenum] == (void *) NULL)
	{
		error = ERROR_FILE_UNOPENED;
		return;
	}
    if (b2c->file_modes[filenum] == MODE_READ || b2c->file_modes[filenum] == MODE_ARCHIVE)
	{
		error = ERROR_FILE_WRITE;
		return;
	}

    if (filepos != -1)
    {
        filepos = FileOutput_seek(b2c->files[filenum], filepos, SEEK_SET);
		if (filepos == -1)
		{
			error = ERROR_FILE_SEEK;
			return;
		}
    }

    if (size >=0 )
    {
        if (0==FileOutput_write(b2c->files[filenum], data, size))
		{
			error = ERROR_FILE_WRITE;
			return;
		}
    }
}

void _get(int filenum, long filepos, void *data, int size)
{
    if (filenum < 0 || filenum > MAX_FILES-1)
	{
		error = ERROR_FILE_NUMBER;
		return;
	}
    if (b2c->files[filenum] == (void *) NULL)
	{
		error = ERROR_FILE_UNOPENED;
		return;
	}
    if (b2c->file_modes[filenum] != MODE_READ  && b2c->file_modes[filenum] != MODE_ARCHIVE)
	{
		error = ERROR_FILE_READ;
		return;
	}

    if (filepos != -1)
    {
        filepos = FileInput_seek(b2c->files[filenum], filepos, SEEK_SET);
		if (filepos == -1)
		{
			error = ERROR_FILE_SEEK;
			return;
		}
    }

    if (size >= 0)
    {
        if (0==FileInput_read(b2c->files[filenum], data, size))
		{
			error = ERROR_FILE_READ;
			return;
		}
    }
}

void _printno(int filenum, char *fmt, ...)
{
    va_list parameters;

    DBG(">_printno");

	error = 0;
    if (filenum < 0 || filenum > MAX_FILES-1)
	{
		error = ERROR_FILE_NUMBER;
		return;
	}
    if (b2c->files[filenum] == (void *) NULL)
	{
		error = ERROR_FILE_UNOPENED;
		return;
	}
    if (b2c->file_modes[filenum] == MODE_READ || b2c->file_modes[filenum] == MODE_ARCHIVE)
	{
		error = ERROR_FILE_WRITE;
		return;
	}

    va_start( parameters, fmt );
    vsprintf( b2c->buf, fmt, parameters );
    va_end( parameters );

    if (0==FileOutput_write(b2c->files[filenum], b2c->buf, strlen(b2c->buf)))
	{
		error = ERROR_FILE_WRITE;
		return;
	}

    DBG("<_printno");
}

void _findfile(char *pattern)
{
	if (b2c->find_in_progress)
	{
		File_dtor(&b2c->file_info, LEAVE_MEMORY);
		FileFind_dtor(&b2c->searcher, LEAVE_MEMORY);
	}
	
	File_ctor(&b2c->file_info);
	FileFind_ctor(&b2c->searcher, &b2c->file_info, pattern);
	b2c->find_in_progress = 1;
}

int _nextfile(char *s)
{
	bool rc;

	rc = FileFind_has_more_elements(&b2c->searcher);
	if (!rc) return 0;
	FileFind_next_element(&b2c->searcher);
	strcpy(s, b2c->file_info.name);
	return 1;
}

