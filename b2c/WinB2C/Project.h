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
// Project.h: interface for the CProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_H__FE7CDA06_5292_4A92_95FE_3C96E231111C__INCLUDED_)
#define AFX_PROJECT_H__FE7CDA06_5292_4A92_95FE_3C96E231111C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BuildTree.h"

class CProject
{
public:
	CProject();
	virtual ~CProject();
	void Create();
	void Show();
	void Hide();
	void Load();
	void Save(const char *name = NULL);
	void Saveas();

	CBuildTree m_buildTree;
	CString m_buildFileName;
	HTREEITEM m_source;
	HTREEITEM m_graphics;
	HTREEITEM m_sprites;
	HTREEITEM m_3dsprites;
	HTREEITEM m_3dtextures;
	HTREEITEM m_files;
	HTREEITEM m_music;
	HTREEITEM m_objects;
};

#endif // !defined(AFX_PROJECT_H__FE7CDA06_5292_4A92_95FE_3C96E231111C__INCLUDED_)
