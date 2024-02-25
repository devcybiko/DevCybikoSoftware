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
// BuildTree.cpp : implementation file
//

#include "stdafx.h"
#include "WinB2C.h"
#include "BuildTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuildTree dialog


CBuildTree::CBuildTree(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildTree::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuildTree)
	m_Author = _T("");
	m_Copyright = _T("");
	m_Cyosversion = _T("");
	m_Environment = _T("");
	m_HelpText = _T("");
	m_Keep = FALSE;
	m_Name = _T("");
	m_Output = _T("");
	m_Path = _T("");
	m_Sdk20 = -1;
	m_Sdk30 = -1;
	m_SplashText = _T("");
	m_Version = _T("");
	m_AppType = _T("");
	//}}AFX_DATA_INIT
	m_dirty = FALSE;
}


void CBuildTree::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildTree)
	DDX_Control(pDX, IDC_PROJECT_PATH_BUTTON, m_PathButton);
	DDX_Text(pDX, IDC_PROJECT_AUTHOR, m_Author);
	DDX_Text(pDX, IDC_PROJECT_COPYRIGHT, m_Copyright);
	DDX_Text(pDX, IDC_PROJECT_CYOSVERSION, m_Cyosversion);
	DDX_Text(pDX, IDC_PROJECT_ENVIRONMENT, m_Environment);
	DDX_Text(pDX, IDC_PROJECT_HELP_TEXT, m_HelpText);
	DDX_Check(pDX, IDC_PROJECT_KEEP, m_Keep);
	DDX_Text(pDX, IDC_PROJECT_NAME, m_Name);
	DDX_Text(pDX, IDC_PROJECT_OUTPUT, m_Output);
	DDX_Text(pDX, IDC_PROJECT_PATH, m_Path);
	DDX_Radio(pDX, IDC_PROJECT_SDK20, m_Sdk20);
	DDX_Radio(pDX, IDC_PROJECT_SDK30, m_Sdk30);
	DDX_Text(pDX, IDC_PROJECT_SPLASH_TEXT, m_SplashText);
	DDX_Text(pDX, IDC_PROJECT_VERSION, m_Version);
	DDX_CBString(pDX, IDC_PROJECT_APPTYPE, m_AppType);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_PROJECT_BUILDTREE, m_buildTree);
}


BEGIN_MESSAGE_MAP(CBuildTree, CDialog)
	//{{AFX_MSG_MAP(CBuildTree)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_PROJECT_SDK20, OnProjectSdk20)
	ON_BN_CLICKED(IDC_PROJECT_SDK30, OnProjectSdk30)
	ON_CBN_EDITCHANGE(IDC_PROJECT_APPTYPE, OnEditchangeProjectApptype)
	ON_EN_CHANGE(IDC_PROJECT_AUTHOR, OnChangeProjectAuthor)
	ON_EN_CHANGE(IDC_PROJECT_COPYRIGHT, OnChangeProjectCopyright)
	ON_EN_CHANGE(IDC_PROJECT_CYOSVERSION, OnChangeProjectCyosversion)
	ON_EN_CHANGE(IDC_PROJECT_ENVIRONMENT, OnChangeProjectEnvironment)
	ON_EN_CHANGE(IDC_PROJECT_HELP_TEXT, OnChangeProjectHelpText)
	ON_BN_CLICKED(IDC_PROJECT_KEEP, OnProjectKeep)
	ON_EN_CHANGE(IDC_PROJECT_NAME, OnChangeProjectName)
	ON_EN_CHANGE(IDC_PROJECT_OUTPUT, OnChangeProjectOutput)
	ON_EN_CHANGE(IDC_PROJECT_PATH, OnChangeProjectPath)
	ON_EN_CHANGE(IDC_PROJECT_SPLASH_TEXT, OnChangeProjectSplashText)
	ON_EN_CHANGE(IDC_PROJECT_VERSION, OnChangeProjectVersion)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_PROJECT_CLOSE, OnProjectClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildTree message handlers


void CBuildTree::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
}

void CBuildTree::OnProjectSdk20() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	m_Sdk30 = !m_Sdk20;
	this->UpdateData(FALSE);
	m_dirty = TRUE;
}

void CBuildTree::OnProjectSdk30() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	m_Sdk20 = !m_Sdk30;
	this->UpdateData(FALSE);
	m_dirty = TRUE;
}

void CBuildTree::OnEditchangeProjectApptype() 
{
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectAuthor() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectCopyright() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectCyosversion() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectEnvironment() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectHelpText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnProjectKeep() 
{
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectOutput() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectPath() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectSplashText() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnChangeProjectVersion() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	m_dirty = TRUE;
}

void CBuildTree::OnAppExit() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("CBuildTree::OnAppExit()");
}

void CBuildTree::OnCancelEditCntr() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("CBuildTree::OnCancelEditCntr()");
}

void CBuildTree::OnProjectClose() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("CBuildTree::OnProjectClose()");
}

