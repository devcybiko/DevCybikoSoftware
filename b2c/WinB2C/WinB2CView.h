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
// WinB2CView.h : interface of the CWinB2CView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINB2CVIEW_H__7F6800F4_D3B6_42AA_A291_DC64B9DB2874__INCLUDED_)
#define AFX_WINB2CVIEW_H__7F6800F4_D3B6_42AA_A291_DC64B9DB2874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWinB2CCntrItem;

class CWinB2CView : public CRichEditView
{
protected: // create from serialization only
	CWinB2CView();
	DECLARE_DYNCREATE(CWinB2CView)
	void ColorLine(int start, int end);
	afx_msg void OnWindowPosChanged( WINDOWPOS* lpwndpos );


	CHARFORMAT cf;
	PARAFORMAT pf;
	void SetFormat();
	int initialized;

	// Attributes
public:
	CWinB2CDoc* GetDocument();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinB2CView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinB2CView();
	void Colorize();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinB2CView)
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WinB2CView.cpp
inline CWinB2CDoc* CWinB2CView::GetDocument()
   { return (CWinB2CDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINB2CVIEW_H__7F6800F4_D3B6_42AA_A291_DC64B9DB2874__INCLUDED_)
