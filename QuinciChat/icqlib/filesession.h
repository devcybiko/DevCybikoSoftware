/* -*- Mode: C; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */

/*
 * $Id: filesession.h,v 1.3 2001/06/11 01:47:35 cyreve Exp $
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

#ifndef _FILE_SESSION_H
#define _FILE_SESSION_H

#include "icq.h"
#include "icqtypes.h"

icq_FileSession *icq_FileSessionNew(icq_Link *);
void icq_FileSessionDelete(void *);
void icq_FileSessionSetStatus(icq_FileSession *, int);
icq_FileSession *icq_FindFileSession(icq_Link *, unsigned long, unsigned long);
void icq_FileSessionSetHandle(icq_FileSession *, const char *);
void icq_FileSessionSetCurrentFile(icq_FileSession *, const char *);
void icq_FileSessionPrepareNextFile(icq_FileSession *);
void icq_FileSessionSendData(icq_FileSession *);

#endif
