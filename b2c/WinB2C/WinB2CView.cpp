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
// WinB2CView.cpp : implementation of the CWinB2CView class
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
// CWinB2CView

IMPLEMENT_DYNCREATE(CWinB2CView, CRichEditView)

BEGIN_MESSAGE_MAP(CWinB2CView, CRichEditView)
	//{{AFX_MSG_MAP(CWinB2CView)
	ON_WM_DESTROY()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinB2CView construction/destruction

CWinB2CView::CWinB2CView()
{
	initialized = false;
}

CWinB2CView::~CWinB2CView()
{
}

BOOL CWinB2CView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	// Set the printing margins (720 twips = 1/2 inch).
	return CRichEditView::PreCreateWindow(cs);
}

void CWinB2CView::SetFormat()
{

	if (!initialized)
	{
		memset(&cf, 0, sizeof(cf));
		cf.cbSize = sizeof(cf);
		cf.dwMask = CFM_FACE | CFM_BOLD;
		cf.dwEffects = 0;
		strcpy(cf.szFaceName, "Courier");

		memset(&pf, 0, sizeof(pf));
		pf.cbSize = sizeof(pf);
		pf.dwMask = PFM_TABSTOPS;
		pf.cTabCount = 32;

		int i;
		for (i=0; i<32; i++)
			pf.rgxTabs[i]=(i+1)*480;
		initialized=true;
	}

	CRichEditCtrl & rectrl = this->GetRichEditCtrl();
	rectrl.SetDefaultCharFormat(cf);
	this->SetCharFormat(cf);
	SetParaFormat(pf);
}

void CWinB2CView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();

	SetMargins(CRect(720, 720, 720, 720));

	CRichEditCtrl & rectrl = this->GetRichEditCtrl();

	rectrl.SetSel(0, -1);
	CString s = rectrl.GetSelText();

	SetFormat();

	rectrl.ReplaceSel(s, FALSE);

	m_nWordWrap = WrapNone;
	WrapChanged();

	rectrl.SetSel(0, 0);
	Colorize();

	this->GetDocument()->SetModifiedFlag(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CWinB2CView printing

BOOL CWinB2CView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CWinB2CView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CWinB2CView diagnostics

#ifdef _DEBUG
void CWinB2CView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CWinB2CView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CWinB2CDoc* CWinB2CView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinB2CDoc)));
	return (CWinB2CDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinB2CView message handlers

static void select_current_line(CRichEditCtrl &rectrl, long &beginning, long &ending, int len)
{
	int start = beginning;
	int end = ending;
	while(rectrl.LineFromChar(start) >= rectrl.LineFromChar(beginning))
	{
		if (start == 0) break;
		start--;
	}
	while(rectrl.LineFromChar(end) <= rectrl.LineFromChar(ending))
	{
		if (end >= len) break;
		end++;
	}
	beginning = start;
	ending = end;
}

const COLORREF crStandard[]={ 
	RGB(  0,   0,   0), //none
	RGB(  0,   0,   0), //blanks
	RGB( 64, 192,   0), //punctuation
	RGB(  0, 128,   0), //quoted string
	RGB(128, 128, 128), //comment
	RGB(  0,   0, 192), //word
	RGB(  0, 192,   0), //literal character
	RGB(192,   0,   0), //number
	RGB(192,   0, 192), //INLINE
	RGB(192, 128,   0), //OPTION
	RGB(255,0,0)        //OTHER
};

enum {
	TOKEN_NONE,
	TOKEN_BLANKS, 
	TOKEN_PUNCTUATION,
	TOKEN_QUOTE,
	TOKEN_COMMENT,
	TOKEN_WORD,
	TOKEN_CHAR,
	TOKEN_NUMBER,
	TOKEN_INLINE,
	TOKEN_OPTION,
	TOKEN_OTHER,
	TOKEN_MAX};

static char *keyword_table[]= {
"dim"	,
"char"	,
"int"	,
"long"	,
"double" ,
"as"	 ,
"for"	 ,
"to"	 ,
"step"   ,
"next"   ,
"exit"	 ,
"if"	 ,
"then"	 ,
"end"	 ,
"else"	 ,
"elseif" ,
"print"	 ,
"while"	 ,
"wend"	 ,
"sub"	 ,
"function" ,
"byval"  ,
"byref"  ,
"call"	 ,
"wait"	 ,
"input"  ,
"inputxy"  ,
"line"	 ,
"point"  ,
"ink"    ,
"paper"  ,
"cls"    ,
"printxy"	,
"sin"	,
"sinh"	,
"asin"	,
"asinh"	,
"cos"	,
"cosh"	,
"acos"  ,
"acosh"	,
"tan"	,
"actan"	,
"actanh" ,
"atan"	,
"atanh"	,
"sqrt"	,
"exp"	,
"log"	,
"log10"	,
"log2"	,
"pow2"	,
"rnd"	,
"pow"   ,
"inv"	,
"sqr_pow" ,
"key"   ,
"eof"   ,
"open"  ,
"read"  ,
"write" ,
"append" ,
"close" ,
"put"   ,
"get"   ,
"and"	,
"or"	,
"<>"	,
"beep"	,
"mid"	,
"right" ,
"inline" ,
"outline" ,
"font"	,
"goto"	,
"type"	,
"sprite" ,
"move" ,
"redraw" ,
"collision" ,
"music" ,
"foreground" ,
"background" ,
"stop" ,
"play" ,
"flip_x" ,
"flip_y" ,
"vibrate" ,
"option" ,
"c_strings" ,
"cybasic_strings" ,
"on" ,
"gosub" ,
"show" ,
"all" ,
"c_coords" ,
"cybasic_coords" ,
"sprites" ,
"score" ,
"white" ,
"ltgrey" ,
"dkgrey" ,
"black" ,
"menu"	,
"menuxy" ,
"endif" ,
"keyclick" ,
"off" ,
"program" ,
"not" ,
"mod" ,
"abs" ,
"dabs" ,
"int" ,
"escape" ,
"help" ,
"multitask" ,
"getchar" ,
"getkey" ,
"sendmessage" ,
"sprint"	,
"tokenize"  ,
"tocyid" ,
"touser" ,
"usermenu" ,
"dialog" ,
"3droom" ,
"3dsprite" ,
"3dredraw" ,
"3dwall" ,
"3dcollision" ,
"3dmove" ,
"3drmove" ,
"3dget" ,
"camera" ,
"true" ,
"false" ,
"error" ,
"sprite_get" ,
"findfile" ,
"nextfile" ,
"filelist" ,
"rect" ,
"rectfill" ,
"page" ,
"pagecopy" ,
"remove"	,
"rename"	,
"exists"	,
"load"		,
"len"		,
"stringwidth"	,
"stringheight"	,
"wrap"			,
"left"			,
"center"		,
"word"			,
"archive"		,
"3dsprites"		,
"3drooms"		,
"circle"		,
"circfill"		,
"include",
0};

static void my_strncpy(char *s, char *t, int n)
{
	strncpy(s, t, n);
	s[n]=0;
}

static int my_strlen(const char *s)
{
	int i;
	for(i=0; (s[i] != 0) && (s[i] != '\n'); i++);
	return i;
}

static int tokenize(const char *s, int start, int& end)
{
	int i;
	int len = strlen(&s[start]);


	if (len == 0) 
	{
		end = start;
		return TOKEN_NONE;
	}

	//get blanks
	if (isspace(s[start]))
	{
		for(i=start; i<(start+len); i++)
		{
			if (isspace(s[i])) continue;
			break;
		}
		end = i-1;
		return TOKEN_BLANKS;
	}

	//get word
	if (isalpha(s[start]) || (s[start]=='_'))
	{
		for(i=start; i<(start+len); i++)
		{
			if (isalnum(s[i]) || (s[i]=='_')) continue;
			break;
		}
		end = i-1;
		if (strnicmp(&s[start], "inline ", 7)==0 || strnicmp(&s[start], "outline ", 8)==0)
		{
			char *t = strchr(&s[start+1], '\n');
			if (t) end = t-s;
			else end = start+my_strlen(&s[start+1]);
			return TOKEN_INLINE;
		}
		if (strnicmp(&s[start], "option ", 7)==0)
		{
			char *t = strchr(&s[start+1], '\n');
			if (t) end = t-s;
			else end = start+my_strlen(&s[start+1]);
			return TOKEN_OPTION;
		}
		return TOKEN_WORD;
	}

	//get number
	if (isdigit(s[start]) || ((s[start]=='.') && (isdigit(s[start+1]))))
	{
		for(i=start; i<(start+len); i++)
		{
			if (isdigit(s[i]) || s[i]=='.') continue;
			break;
		}
		end = i-1;
		return TOKEN_NUMBER;
	}
	//get punctuation
	if (strchr("/?!@#$%^&*()<>,.{}[]+-=|:;", s[start]))
	{
		end=start;
		return TOKEN_PUNCTUATION;
	}

	//get comment
	if (s[start] == '\'')
	{
		char *t = strchr(&s[start+1], '\n');
		if (t) end = t-s;
		else end = start+my_strlen(&s[start+1]);
		return TOKEN_COMMENT;
	}

	//get quoted string
	if (s[start] == '"')
	{
		char *t = strchr(&s[start+1], '"');
		if (t) end = t-s;
		else end = start+my_strlen(&s[start+1]);
		return TOKEN_QUOTE;
	}

	//get quoted char
	if (s[start] == '\\')
	{
		char *t = strchr(&s[start+1], '\\');
		if (t) end = t-s;
		else end = start+my_strlen(&s[start+1]);
		return TOKEN_CHAR;
	}
	end = start;
	char t[32];
	sprintf(t, "Unparsed character %d (%c)", s[start], s[start]);
	AfxMessageBox(t);
	return TOKEN_OTHER;
}

static int my_search(const void *elem1, const void *elem2 )
{
	char **bb = (char **)elem2;
	char *a = (char *) elem1;
	char *b = *bb;

	return stricmp(a, b);
}

static int my_sort(const void *elem1, const void *elem2 )
{
	char **aa = (char **)elem1;
	char **bb = (char **)elem2;
	char *a = *aa;
	char *b = *bb;

	return strcmp(a, b);
}

static int iskeyword(const char *s)
{
	static int sorted=false;
	int rc;

	if (!sorted)
	{
		qsort(keyword_table, sizeof(keyword_table)/sizeof(char *)-1, sizeof(char *), my_sort);
		sorted = true;
	}
	rc = (int) bsearch(
		s, 
		keyword_table, 
		sizeof(keyword_table)/sizeof(char *)-1, 
		sizeof(char *), my_search);
	return rc;
}

void CWinB2CView::ColorLine(int beginning, int ending)
{
	CString s;
	int color;

	cf.dwMask |= CFM_COLOR;
	cf.dwEffects = 0;

	//get the current selection
	CRichEditCtrl & rectrl = this->GetRichEditCtrl();

	//reset all characters to black
	rectrl.SetSel(beginning, ending);
	s = rectrl.GetSelText();
	cf.crTextColor = crStandard[0]; //black
	this->SetCharFormat(cf);
	rectrl.ReplaceSel(s, FALSE);

	int token;
	int a=0;
	int b;

	while(token=tokenize(s, a, b))
	{
		color = token;
		if (token == TOKEN_WORD)
		{
			if (iskeyword((LPCTSTR )s.Mid(a, b-a+1))) color = token;
			else color = 0; //black
		}
		rectrl.SetSel(beginning+a, beginning+b+1);
		cf.crTextColor = crStandard[color];
		this->SetCharFormat(cf);
		rectrl.ReplaceSel(s.Mid(a, (b-a+1)), FALSE);
		a = b+1;
	}
}

//
// Color every line of text in the view
//
void CWinB2CView::Colorize()
{
	long start;
	long end;

	// turn off redraw to avoid flicker
	this->SetRedraw(FALSE);

	//get the current selection
	CRichEditCtrl & rectrl = this->GetRichEditCtrl();
	rectrl.GetSel(start, end);
	rectrl.SetSel(0,0);

	ColorLine(0, -1);

	// turn redraw back on
	this->SetRedraw(TRUE);
	
	//restore the selection to its original state
	rectrl.SetSel(start, end);

	//Redraw the whole window
	RedrawWindow();
}

void CWinB2CView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	long old_start;
	long old_end;
	int start;
	int end;

	// turn off redraw to avoid flicker
	this->SetRedraw(FALSE);

	CRichEditView::OnChar(nChar, nRepCnt, nFlags);

	CRichEditCtrl & rectrl = this->GetRichEditCtrl();
	rectrl.GetSel(old_start, old_end);
	start = rectrl.LineIndex(-1);
	rectrl.SetSel(0,0);
	end = start + rectrl.LineLength(-1);
	ColorLine(start, end);

	//restore the selection to its original state
	rectrl.SetSel(old_start, old_end);

	// turn on redraw to avoid flicker
	this->SetRedraw(TRUE);

	//Redraw the whole window
	RedrawWindow();
}

