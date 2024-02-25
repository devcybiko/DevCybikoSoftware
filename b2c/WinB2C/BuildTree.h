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
#if !defined(AFX_BUILDTREE_H__298E7BF4_4190_48ED_82C6_77A2A49F86DC__INCLUDED_)
#define AFX_BUILDTREE_H__298E7BF4_4190_48ED_82C6_77A2A49F86DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildTree.h : header file
//

#include "MyTreeCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CBuildTree dialog

class CBuildTree : public CDialog
{
// Construction
public:
	CBuildTree(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBuildTree)
	enum { IDD = IDD_BUILDTREE_DIALOG };
	CButton	m_PathButton;
	CString	m_Author;
	CString	m_Copyright;
	CString	m_Cyosversion;
	CString	m_Environment;
	CString	m_HelpText;
	BOOL	m_Keep;
	CString	m_Name;
	CString	m_Output;
	CString	m_Path;
	int		m_Sdk20;
	int		m_Sdk30;
	CString	m_SplashText;
	CString	m_Version;
	CString	m_AppType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildTree)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuildTree)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnProjectSdk20();
	afx_msg void OnProjectSdk30();
	afx_msg void OnEditchangeProjectApptype();
	afx_msg void OnChangeProjectAuthor();
	afx_msg void OnChangeProjectCopyright();
	afx_msg void OnChangeProjectCyosversion();
	afx_msg void OnChangeProjectEnvironment();
	afx_msg void OnChangeProjectHelpText();
	afx_msg void OnProjectKeep();
	afx_msg void OnChangeProjectName();
	afx_msg void OnChangeProjectOutput();
	afx_msg void OnChangeProjectPath();
	afx_msg void OnChangeProjectSplashText();
	afx_msg void OnChangeProjectVersion();
	afx_msg void OnAppExit();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnProjectClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CMyTreeCtrl m_buildTree;
	int m_dirty;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDTREE_H__298E7BF4_4190_48ED_82C6_77A2A49F86DC__INCLUDED_)
