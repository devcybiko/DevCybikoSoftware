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
// WinB2C.h : main header file for the WINB2C application
//

#if !defined(AFX_WINB2C_H__5D952A55_B490_4D51_84EE_A6D98FA1A822__INCLUDED_)
#define AFX_WINB2C_H__5D952A55_B490_4D51_84EE_A6D98FA1A822__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#pragma warning( disable : 4786 )
#include "BuildTree.h"

/////////////////////////////////////////////////////////////////////////////
// CWinB2CApp:
// See WinB2C.cpp for the implementation of this class
//

#include "Project.h"

class CWinB2CApp : public CWinApp
{
public:
	CWinB2CApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinB2CApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWinB2CApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	CProject m_project;
	void CloseAllDocuments( BOOL bEndSession );
};
extern CWinB2CApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINB2C_H__5D952A55_B490_4D51_84EE_A6D98FA1A822__INCLUDED_)
