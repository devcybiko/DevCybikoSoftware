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
// display a dialog if the file / pw doesnt exist
int _dialog(
        char *info,
        char *text,
		char *data,
		int len)
{
    struct cDialog *dialog;
    int rc;
	char *disp;

    dialog = (struct cDialog *) malloc(sizeof(struct cDialog));

    // alert dialog
    if (data) 
	{
		cDialog_ctor( dialog, info, text, mbOk | mbCancel | mbEdit, len, 
			b2c->main_module.m_process );
		cDialog_SetEditText(dialog, data);
	}
	else
	{
		cDialog_ctor( dialog, info, text, mbOk | mbCancel , 0, 
			b2c->main_module.m_process );
	}

    play_tone(-1);
	disp = (char* ) malloc( TGraph_get_bytes_total( b2c->main_module.m_gfx ) );
	memcpy(disp,
		DisplayGraphics_get_page_ptr(b2c->main_module.m_gfx, 0),
    TGraph_get_bytes_total(b2c->main_module.m_gfx));

	rc = cDialog_ShowModal(dialog);
    if ((rc == mrOk) && data)
     {
        cDialog_GetEditText(dialog, data);
     }
//	cText_dtor(line0, FREE_MEMORY);
	cDialog_dtor(dialog, FREE_MEMORY);
	TGraph_put_background(b2c->main_module.m_gfx, disp );
	free(disp);
	return rc==mrOk;
}
