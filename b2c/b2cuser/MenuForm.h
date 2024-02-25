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


#ifndef __MENUFORM_H__
#define __MENUFORM_H__

////////////////////////////////////////////////////////////
//be sure to #include CyWin.h prior to including this file//
////////////////////////////////////////////////////////////

//this result is given if an MSG_QUIT or MSG_SHUTUP message is received
#define MENUFORM_QUIT	-2
//this result is given if ESC is pressed
#define MENUFORM_CANCEL	-1


//SimpleMenuForm function(returns item selected, or -1 if cancelled using <Esc>
//int SimpleMenuForm(
//	char* title,				//(in)title of the menu
//	char** ItemList,			//(in)list of items (array of char*, with last item being "")
//	int x,						//(in) x coordinate of upperleft
//	int y,						//(in) y coordinate of upperleft
//	int width,					//(in) width of form
//	int height,					//(in) height of form
//	bool round,					//(in) TRUE=rounded, FALSE=rectangular
//	struct cWinApp* ptr_win_app	//(in)application pointer(main_module.m_process)
//);

#endif
