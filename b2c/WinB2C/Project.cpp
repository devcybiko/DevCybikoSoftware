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
// Project.cpp: implementation of the CProject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinB2C.h"
#include "Project.h"
#include <setjmp.h>
#include "..\b2cbuild\b2cbuild.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern void do_everything(char *fname);
extern jmp_buf MainFrm_mark;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProject::CProject()
{

}

CProject::~CProject()
{

}

void CProject::Create()
{
	m_buildTree.Create(IDD_BUILDTREE_DIALOG);
	m_source = m_buildTree.m_buildTree.InsertItem("Source",TVI_ROOT, TVI_LAST);
	m_graphics = m_buildTree.m_buildTree.InsertItem("Graphics",TVI_ROOT, TVI_LAST);
				m_sprites = m_buildTree.m_buildTree.InsertItem("Sprites",m_graphics, TVI_LAST);
				m_3dsprites = m_buildTree.m_buildTree.InsertItem("3D Sprites",m_graphics, TVI_LAST);
				m_3dtextures = m_buildTree.m_buildTree.InsertItem("3D Textures",m_graphics, TVI_LAST);
	m_files = m_buildTree.m_buildTree.InsertItem("Files",TVI_ROOT, TVI_LAST);
	m_music = m_buildTree.m_buildTree.InsertItem("Music",TVI_ROOT, TVI_LAST);
	m_objects = m_buildTree.m_buildTree.InsertItem("Objects (.o)",TVI_ROOT, TVI_LAST);
}

void CProject::Show()
{
	if (!theApp.m_project.m_buildFileName.IsEmpty())
	{
		m_buildTree.SetWindowText(m_buildFileName);
		m_buildTree.ShowWindow(SW_SHOW);
		m_buildTree.SetFocus();
	}
	else
	{
		AfxMessageBox("You have not yet selected a project.");
	}
}

void CProject::Hide()
{
	m_buildTree.ShowWindow(SW_HIDE);
}

extern Build build;

void CProject::Load()
{
	char *filters = "Build Files (*.bld)|*.bld||";
	int i, j;
	HTREEITEM last;

	CFileDialog dlg(TRUE, "bld", "*.bld",
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, filters);

	if (dlg.DoModal() == IDOK)
	{
		const char *filename = (LPCTSTR) dlg.GetFileName();
		int jmpret;
		jmpret = setjmp( MainFrm_mark );
		if( jmpret == 0 )
		{
			memset(&build, 0, sizeof(build));
			do_everything((char *)filename);
			this->m_buildFileName = filename;
			m_buildTree.SetWindowText("Project: "+m_buildFileName);
			m_buildTree.m_Author = build.author;
			m_buildTree.m_Copyright = build.copyright;
			m_buildTree.m_Cyosversion = build.cyos;
			m_buildTree.m_Environment = "";
			m_buildTree.m_HelpText = "";
			m_buildTree.m_Keep = build.keep;
			m_buildTree.m_Name = build.name;
			m_buildTree.m_Output = build.output;
			m_buildTree.m_Path = build.path;
			m_buildTree.m_Sdk20 = (build.sdk == 2);
			m_buildTree.m_Sdk30 = (build.sdk == 3);
			m_buildTree.m_SplashText = "";
			m_buildTree.m_AppType = build.type;
			m_buildTree.m_Version = build.version;

			m_buildTree.m_HelpText = "";
			for(i=0; build.help.node[i]; i++)
			{
				m_buildTree.m_HelpText += (char *)build.help.node[i];
				m_buildTree.m_HelpText += "\015\012";
			}

			m_buildTree.m_SplashText = "";
			for(i=0; build.splash_text.node[i]; i++)
			{
				m_buildTree.m_SplashText += (char *)build.splash_text.node[i];
				m_buildTree.m_SplashText += "\015\012";
			}

			m_buildTree.m_Environment = "";
			for(i=0; build.environment.node[i]; i++)
			{
				m_buildTree.m_Environment += (char *)build.environment.node[i];
				m_buildTree.m_Environment += "\015\012";
			}

			m_buildTree.m_buildTree.DeleteItem(m_source);
			m_source = m_buildTree.m_buildTree.InsertItem("Source",TVI_ROOT, TVI_LAST);
			for(i=0; build.source.node[i]; i++)
				m_buildTree.m_buildTree.InsertItem(
					(const char *)build.source.node[i], m_source, TVI_LAST);

			m_buildTree.m_buildTree.DeleteItem(m_graphics);
			m_graphics = m_buildTree.m_buildTree.InsertItem("Graphics",TVI_ROOT, TVI_LAST);

			m_sprites = m_buildTree.m_buildTree.InsertItem("Sprites",m_graphics, TVI_LAST);
			for(i=0; build.pics.node[i]; i++)
			{
				List *list = (List *)build.pics.node[i];


				last = m_buildTree.m_buildTree.InsertItem(
					(const char *)list->node[0], m_sprites, TVI_LAST);

				for(j=1; list->node[j]; j++)
				{
					m_buildTree.m_buildTree.InsertItem(
						(const char *) list->node[j], last, TVI_LAST);
				}
			}

			m_3dsprites = m_buildTree.m_buildTree.InsertItem("3D Sprites",m_graphics, TVI_LAST);
			for(i=0; build.pics.node[i]; i++)
			{
				List *list = (List *)build.d3sprites.node[i];

				last = m_buildTree.m_buildTree.InsertItem(
					(const char *)list->node[0], m_3dsprites, TVI_LAST);

				for(j=1; list->node[j]; j++)
				{
					m_buildTree.m_buildTree.InsertItem(
						(const char *) list->node[j], last, TVI_LAST);
				}
			}

			m_3dtextures = m_buildTree.m_buildTree.InsertItem("3D Textures",m_graphics, TVI_LAST);
			for(i=0; build.tex.node[i]; i++)
				m_buildTree.m_buildTree.InsertItem(
					(const char *)build.tex.node[i], m_3dtextures, TVI_LAST);

			m_buildTree.m_buildTree.DeleteItem(m_files);
			m_files = m_buildTree.m_buildTree.InsertItem("Files",TVI_ROOT, TVI_LAST);
			for(i=0; build.files.node[i]; i++)
				m_buildTree.m_buildTree.InsertItem(
					(const char *)build.files.node[i], m_files, TVI_LAST);

			m_buildTree.m_buildTree.DeleteItem(m_music);
			m_music = m_buildTree.m_buildTree.InsertItem("Music",TVI_ROOT, TVI_LAST);
			for(i=0; build.music.node[i]; i++)
				m_buildTree.m_buildTree.InsertItem(
					(const char *)build.music.node[i], m_music, TVI_LAST);

			m_buildTree.m_buildTree.DeleteItem(m_objects);
			m_objects = m_buildTree.m_buildTree.InsertItem("Objects",TVI_ROOT, TVI_LAST);
			for(i=0; build.objects.node[i]; i++)
				m_buildTree.m_buildTree.InsertItem(
					(const char *)build.objects.node[i], m_objects, TVI_LAST);
			m_buildTree.UpdateData(FALSE);
			m_buildTree.ShowWindow(SW_SHOW);
			m_buildTree.SetFocus();
		}
		else
		{
			AfxMessageBox("ERROR: Build File cannot be parsed");
		}
	}
}

static bool blankline(const char *s)
{
	while(*s)
	{
		if (!isspace(*s)) return false;
	}
	return true;
}

static saveline(CStdioFile &f, const char *heading, const char *value)
{
	if (heading && blankline(heading))
	{
		f.WriteString("[");
		f.WriteString(heading);
		f.WriteString("]\n");
		f.WriteString(value);
		f.WriteString("\n\n");
	}
}

void CProject::Save(const char *name)
{
	HTREEITEM item, list;
	if (name) this->m_buildFileName = name;
	m_buildTree.SetWindowText(m_buildFileName);

	TRY
	{
		bool title;
		CStdioFile f( this->m_buildFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText );

		m_buildTree.UpdateData(TRUE);
		if (m_buildTree.m_Keep) saveline(f, "option", "keep");

		title = true;
		for(item=m_buildTree.m_buildTree.GetChildItem(m_source);
			item;
			item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
		{
			if (title) f.WriteString("[source]\n");
			title = false;
			CString s = m_buildTree.m_buildTree.GetItemText(item);
			f.WriteString(s);
			f.WriteString("\n");
		}
		f.WriteString("\n");
		
		saveline(f, "author", m_buildTree.m_Author);
		saveline(f, "copyright", m_buildTree.m_Copyright);
		saveline(f, "cyos", m_buildTree.m_Cyosversion);
		saveline(f, "name", m_buildTree.m_Name);
		saveline(f, "output", m_buildTree.m_Output);
		saveline(f, "path", m_buildTree.m_Path);
		saveline(f, "sdk", m_buildTree.m_Sdk20 ? "2" : "3");
		saveline(f, "type", m_buildTree.m_AppType);
		saveline(f, "version", m_buildTree.m_Version);
		saveline(f, "help", m_buildTree.m_HelpText);
		saveline(f, "splash.text", m_buildTree.m_SplashText);
		saveline(f, "environment", m_buildTree.m_Environment);

		for(list=m_buildTree.m_buildTree.GetChildItem(m_sprites);
			list;
			list=m_buildTree.m_buildTree.GetNextItem(list, TVGN_NEXT))
		{

			f.WriteString("[pic=");
			f.WriteString(m_buildTree.m_buildTree.GetItemText(list));
			f.WriteString("]\n");
			for(item=m_buildTree.m_buildTree.GetChildItem(list);
				item;
				item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
			{
				CString s = m_buildTree.m_buildTree.GetItemText(item);
				f.WriteString(s);
				f.WriteString("\n");
			}
		}
		f.WriteString("\n");
		
		for(list=m_buildTree.m_buildTree.GetChildItem(m_3dsprites);
			list;
			list=m_buildTree.m_buildTree.GetNextItem(list, TVGN_NEXT))
		{

			f.WriteString("[3dsprite=");
			f.WriteString(m_buildTree.m_buildTree.GetItemText(list));
			f.WriteString("]\n");
			for(item=m_buildTree.m_buildTree.GetChildItem(list);
				item;
				item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
			{
				CString s = m_buildTree.m_buildTree.GetItemText(item);
				f.WriteString(s);
				f.WriteString("\n");
			}
		}
		f.WriteString("\n");

		title=true;
		for(item=m_buildTree.m_buildTree.GetChildItem(m_3dtextures);
			item;
			item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
		{
			if (title) f.WriteString("[3dtex]\n");
			title = false;
			CString s = m_buildTree.m_buildTree.GetItemText(item);
			f.WriteString(s);
			f.WriteString("\n");
		}
		f.WriteString("\n");

		title=true;
		for(item=m_buildTree.m_buildTree.GetChildItem(m_files);
			item;
			item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
		{
			if (title) f.WriteString("[files]\n");
			title = false;
			CString s = m_buildTree.m_buildTree.GetItemText(item);
			f.WriteString(s);
			f.WriteString("\n");
		}
		f.WriteString("\n");

		title = true;
		for(item=m_buildTree.m_buildTree.GetChildItem(m_music);
			item;
			item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
		{
			if (title) f.WriteString("[music]\n");
			title = false;
			CString s = m_buildTree.m_buildTree.GetItemText(item);
			f.WriteString(s);
			f.WriteString("\n");
		}
		f.WriteString("\n");

		title = true;
		for(item=m_buildTree.m_buildTree.GetChildItem(m_objects);
			item;
			item=m_buildTree.m_buildTree.GetNextItem(item, TVGN_NEXT))
		{
			if (title) f.WriteString("[objects]\n");
			title = false;
			CString s = m_buildTree.m_buildTree.GetItemText(item);
			f.WriteString(s);
			f.WriteString("\n");
		}
	}
	CATCH( CFileException, e )
	{
		CString s = "Could not open file: ";
		s = s + name;
		AfxMessageBox(s);
	}
	END_CATCH
}

void CProject::Saveas()
{
	char *filters = "Build Files (*.bld)|*.bld||";

	CFileDialog dlg(FALSE, "bld", this->m_buildFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filters);
	if (dlg.DoModal() == IDOK)
	{
		Save((LPCTSTR) dlg.GetFileName());
	}
}
