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
// CntrItem.h : interface of the CWinB2CCntrItem class
//

#if !defined(AFX_CNTRITEM_H__846CD10C_417A_4B92_96FD_B481603E54BF__INCLUDED_)
#define AFX_CNTRITEM_H__846CD10C_417A_4B92_96FD_B481603E54BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWinB2CDoc;
class CWinB2CView;

class CWinB2CCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CWinB2CCntrItem)

// Constructors
public:
	CWinB2CCntrItem(REOBJECT* preo = NULL, CWinB2CDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CWinB2CDoc* GetDocument()
		{ return (CWinB2CDoc*)CRichEditCntrItem::GetDocument(); }
	CWinB2CView* GetActiveView()
		{ return (CWinB2CView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinB2CCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CWinB2CCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__846CD10C_417A_4B92_96FD_B481603E54BF__INCLUDED_)
