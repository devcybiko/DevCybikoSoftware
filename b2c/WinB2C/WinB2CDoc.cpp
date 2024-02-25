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
// WinB2CDoc.cpp : implementation of the CWinB2CDoc class
//

#include "stdafx.h"
#include "WinB2C.h"

#include "WinB2CDoc.h"
#include "CntrItem.h"
#include "WinB2CView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinB2CDoc

IMPLEMENT_DYNCREATE(CWinB2CDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CWinB2CDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CWinB2CDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinB2CDoc construction/destruction

CWinB2CDoc::CWinB2CDoc()
{
	// TODO: add one-time construction code here

}

CWinB2CDoc::~CWinB2CDoc()
{
}

BOOL CWinB2CDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
	{
		return FALSE;
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

CRichEditCntrItem* CWinB2CDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CWinB2CCntrItem(preo, (CWinB2CDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CWinB2CDoc serialization

void CWinB2CDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CRichEditDoc::m_bRTF=FALSE;
		CRichEditDoc::Serialize(ar);
		CRichEditDoc::m_bRTF=TRUE;
	}
	else
	{
		CRichEditDoc::m_bRTF=FALSE;
		CRichEditDoc::Serialize(ar);
		CRichEditDoc::m_bRTF=TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWinB2CDoc diagnostics

#ifdef _DEBUG
void CWinB2CDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CWinB2CDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinB2CDoc commands
