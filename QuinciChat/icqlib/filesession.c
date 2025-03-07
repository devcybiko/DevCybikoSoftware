/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

/*
 * $Id: filesession.c,v 1.9 2001/06/17 05:42:53 cyreve Exp $
 *
 * Copyright (C) 1998-2001, Denis V. Dmitrienko <denis@null.net> and
 *                          Bill Soudan <soudan@kde.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifdef _MSVC_
#include <io.h>
#define open _open
#define close _close
#define read _read
#define write _write
#define lseek _lseek
#endif

#include "icqlib.h"
#include "filesession.h"
#include "stdpackets.h"

icq_FileSession *icq_FileSessionNew(icq_Link *icqlink)
{
  icq_FileSession *p=(icq_FileSession *)malloc(sizeof(icq_FileSession));

  if (p)
  {
    p->status=0;
    p->id=0L;
    p->icqlink=icqlink;
    p->tcplink=NULL;
    p->current_fd=-1;
    p->current_file_num=0;
    p->current_file_progress=0;
    p->current_file_size=0;
    p->files=0L;
    p->current_speed=100;
    p->total_bytes=0;
    p->total_files=0;
    p->total_transferred_bytes=0;
    p->working_dir[0]=0;
    p->user_data=NULL;
    icq_ListInsert(icqlink->d->icq_FileSessions, 0, p);
  }
	
  return p;
}

void icq_FileSessionDelete(void *pv)
{
  icq_FileSession *p=(icq_FileSession *)pv;

  invoke_callback(p->icqlink, icq_FileNotify)(p, FILE_NOTIFY_CLOSE, 0, 
    NULL);

  if(p->files) {
    char **p2=p->files;
    while(*p2)
      free(*(p2++));
    free(p->files);
    p->files=NULL;
  }

  if (p->current_fd > -1 ) {
     close(p->current_fd);
     p->current_fd=-1;
  }

  free(p);
}

int _icq_FindFileSession(void *p, va_list data)
{
  icq_FileSession *psession=(icq_FileSession *)p;
  DWORD uin=va_arg(data, DWORD);
  unsigned long id=va_arg(data, unsigned long);
  
  return (psession->remote_uin == uin) && ( id ? (psession->id == id) : 1 );

}

icq_FileSession *icq_FindFileSession(icq_Link *icqlink, DWORD uin,
  unsigned long id)
{
  return icq_ListTraverse(icqlink->d->icq_FileSessions, _icq_FindFileSession, 
    uin, id);
}

void icq_FileSessionSetStatus(icq_FileSession *p, int status)
{
  if(status!=p->status)
  {
    p->status=status;
    if(p->id)
      invoke_callback(p->icqlink, icq_FileNotify)(p, FILE_NOTIFY_STATUS,
        status, NULL);
    if (status == FILE_STATUS_SENDING)
      icq_SocketSetHandler(p->tcplink->socket, ICQ_SOCKET_WRITE,
        icq_FileSessionSendData, p);
    else
      icq_SocketSetHandler(p->tcplink->socket, ICQ_SOCKET_WRITE, NULL, NULL);
  }
}

void icq_FileSessionSetHandle(icq_FileSession *p, const char *handle)
{
  strncpy(p->remote_handle, handle, 64);
}

void icq_FileSessionSetCurrentFile(icq_FileSession *p, const char *filename)
{
#ifdef _WIN32
  struct _stat file_status;
#else
  struct stat file_status;
#endif
  char file[1024];

  strcpy(file, p->working_dir);
  strcat(file, filename);

  if (p->current_fd>-1) {
    close(p->current_fd);
    p->current_fd=-1;
  }

  strncpy(p->current_file, file, 64);
  p->current_file_progress=0;

  /* does the file already exist? */
#ifdef _WIN32
  if (_stat(file, &file_status)==0) {
#else
  if (stat(file, &file_status)==0) {
#endif
    p->current_file_progress=file_status.st_size;
    p->total_transferred_bytes+=file_status.st_size;
#ifdef _WIN32
    p->current_fd=open(file, _O_WRONLY | _O_APPEND | _O_BINARY);
#else
    p->current_fd=open(file, O_WRONLY | O_APPEND);
#endif
  } else {
#ifdef _WIN32
    p->current_fd=open(file, _O_WRONLY | _O_CREAT | _O_BINARY, 
      _S_IREAD|_S_IWRITE);
#else
    p->current_fd=open(file, O_WRONLY | O_CREAT, S_IRWXU);
#endif
  }

  /* make sure we have a valid filehandle */
  if (p->current_fd == -1)
    perror("couldn't open file: ");
      
}

void icq_FileSessionPrepareNextFile(icq_FileSession *p)
{
  int i=0;
  char **files=p->files;

  p->current_file_num++;

  while(*files) {
    i++;
    if(i==p->current_file_num)
      break;
    else
      files++;
  }

  if(*files) {
#ifdef _WIN32
    struct _stat file_status;
#else
    struct stat file_status;
#endif

    if (p->current_fd>-1) {
       close(p->current_fd);
       p->current_fd=-1;
    }

#ifdef _WIN32
    if (_stat(*files, &file_status)==0) {
       char *basename=*files;
       char *pos=strrchr(basename, '\\');
#else
    if (stat(*files, &file_status)==0) {
       char *basename=*files;
       char *pos=strrchr(basename, '/');
#endif
       if(pos) basename=pos+1;
       strncpy(p->current_file, basename, 64);
       p->current_file_progress=0;
       p->current_file_size=file_status.st_size;
#ifdef _WIN32
       p->current_fd=open(*files, _O_RDONLY | _O_BINARY);
#else
       p->current_fd=open(*files, O_RDONLY);
#endif
    }

    /* make sure we have a valid filehandle */
    if (p->current_fd == -1)
       perror("couldn't open file: ");
  }     
}        

void icq_FileSessionSendData(icq_FileSession *p)
{
  /* for now just send a packet at a time */
  char buffer[2048];
  int count=read(p->current_fd, buffer, sizeof(buffer));
  int sentcount;

  if(count>0) {
      icq_Packet *p2=icq_TCPCreateFile06Packet(count, buffer);
      sentcount=icq_TCPLinkSend(p->tcplink, p2);
	  if(sentcount==-1) icq_FmtLog(p->icqlink, ICQ_LOG_WARNING, "Tried to send file while still connecting\n");
	  else if(sentcount<count) {
		icq_FmtLog(p->icqlink, ICQ_LOG_MESSAGE, "Send buffers full: rolling back %d/%d bytes\n",count-sentcount,count);
		if(count<sizeof(buffer)) count=sizeof(buffer);  //don't close if we roll back
		lseek(p->current_fd,sentcount-count,SEEK_CUR);
	  }
      p->total_transferred_bytes+=sentcount;
      p->current_file_progress+=sentcount;
      icq_FileSessionSetStatus(p, FILE_STATUS_SENDING);

      invoke_callback(p->icqlink, icq_FileNotify)(p, FILE_NOTIFY_DATAPACKET,
        count, buffer);
  }

  /* done transmitting if read returns less that 2048 bytes */
  if(count<sizeof(buffer))
      icq_FileSessionClose(p);

  return;
}

/* public */

void icq_FileSessionSetSpeed(icq_FileSession *p, int speed)
{
  icq_Packet *packet=icq_TCPCreateFile05Packet(speed);

  icq_TCPLinkSend(p->tcplink, packet);
}

void icq_FileSessionClose(icq_FileSession *p)
{
  icq_TCPLink *plink=p->tcplink;

  /* TODO: handle closing already unallocated filesession? */

  /* if we're attached to a tcplink, unattach so the link doesn't try
   * to close us, and then close the tcplink */
  if (plink)
  {
    plink->session=0L;
    icq_TCPLinkClose(plink);
  }

  icq_ListRemove(p->icqlink->d->icq_FileSessions, p);
  icq_FileSessionDelete(p);
}   

void icq_FileSessionSetWorkingDir(icq_FileSession *p, const char *dir)
{
  int length = sizeof(p->working_dir);
  strncpy(p->working_dir, dir, length);
  p->working_dir[length-1]='\0';
}  

void icq_FileSessionSetFiles(icq_FileSession *p, char **files)
{
  p->files=files;
}

