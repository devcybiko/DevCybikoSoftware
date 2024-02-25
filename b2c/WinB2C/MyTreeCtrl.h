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
#if !defined(AFX_MYTREECTRL_H__F79A3E78_7117_403F_B1FC_29DA497BD0C3__INCLUDED_)
#define AFX_MYTREECTRL_H__F79A3E78_7117_403F_B1FC_29DA497BD0C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl window

class CMyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CMyTreeCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyTreeCtrl();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__F79A3E78_7117_403F_B1FC_29DA497BD0C3__INCLUDED_)
