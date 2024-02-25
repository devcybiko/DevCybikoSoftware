/**
  * The QuinciChat project is a set of programs and libraries
  * that allow a pair of Cybiko computers to communicate with
  * other users on the internet using the ICQ protocol.
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
#include "CyWin.h"


//#define TEST


static struct FileInput file_input;
static struct FileOutput file_output;

static char pw_dongle_data[16] = {
	0x00, 0x02, 0x04, 0x0a,
	0x20, 0x22, 0x24, 0x2a,
	0x80, 0x42, 0x88, 0x8a,
	0xa0, 0xa2, 0xa8, 0xaa};

static char hexcodes[16]={'b', 'i', 'd', 'k', 'c', 'g', 'o', 'j', 'e', 'n', 'a', 'h', 'm', 'f', 'l', 'p'};

static char pw_scramble_string[16] = {
	0x55, 0xaa, 0x33, 0xcc, 0x5a, 0xa5, 0x3a, 0xa3,
	0xf0, 0x5f, 0xac, 0xca, 0xe7, 0x7e, 0xdd, 0x73};

static void pw_encode(char *appname, long id, char *passwd)
{
	char dongle[8];
	char *cid = (char *) &id;
	int tmp;
    int i;

    //TRACE("%ld=%02x%02x%02x%02x", id, cid[0], cid[1], cid[2], cid[3]);
    //for(i=0; i<16; i++) TRACE("%c=%02x,", appname[i], appname[i]);
    // spread the bits out and scramble them
	dongle[4] = pw_dongle_data[((cid[0] & 0xf0)>>4)&0x0f];
	dongle[5] = pw_dongle_data[((cid[1] & 0xf0)>>4)&0x0f];
	dongle[6] = pw_dongle_data[((cid[2] & 0xf0)>>4)&0x0f];
	dongle[0] = pw_dongle_data[((cid[3] & 0xf0)>>4)&0x0f];
	dongle[7] = pw_dongle_data[cid[0] & 0x0f];
	dongle[3] = pw_dongle_data[cid[1] & 0x0f];
	dongle[1] = pw_dongle_data[cid[2] & 0x0f];
	dongle[2] = pw_dongle_data[cid[3] & 0x0f];

    // spray the dongle with the appname
    for(i=0; i<14; i++)
		dongle[i%8] ^= appname[i];

	// convert to a hex string
	for(i=0; i<16; i++)
	{
		tmp = dongle[i/2];
		if (i%2==0) tmp = tmp & 0x0f;
		else tmp = (tmp >> 4) & 0x0f;
		passwd[i] = hexcodes[tmp];
#ifdef TEST
TRACE("%c", passwd[i]);   // REMOVE THIS BEFORE DELIVERY!
#endif
		//scramble this with simple xor to make it harder to see the password
        passwd[i] = passwd[i] ^ pw_scramble_string[i];
	}
}


// scramble the appname using simple xor procedure
static void pw_scramble(char *old, char *new)
{
        int i;

	// copy the old name to the new name
	memcpy(new, old, 16);
	for(i=0; i<16; i++)
		new[i] = new[i] ^ pw_scramble_string[i];
}

// lookup the dongle in the file
struct dongle_data {
    char appname[14];
    char type[2];
    char passwd[16];
};

static int pw_dongle_lookup(struct dongle_data *_dongle)
{
    struct dongle_data dongle;
    int rc;

    rc = 1;  // file not found
    FileInput_ctor_Ex( &file_input, "dongle.dat");
    if (!FileInput_is_good(&file_input)) goto EARLY_EXIT; // file not found

    rc = 2; // dongle not found
    while(FileInput_read(&file_input, &dongle, sizeof(dongle)))
	{
    	if (memcmp(dongle.appname, _dongle->appname, 16)==0)  //appname + type
		{
            memcpy(_dongle->passwd, dongle.passwd, 16);
		    rc = 0; // Success!
			break;
		}
	}
EARLY_EXIT:
    FileInput_dtor( &file_input, LEAVE_MEMORY );
	return rc;
}

static void pw_backup()
{
    struct dongle_data dongle;

    FileInput_ctor_Ex(&file_input, "dongle.dat");
    if (!FileInput_is_good(&file_input)) return;
    FileOutput_ctor_Ex(&file_output, "dongle.bak", TRUE);
    if (!FileOutput_is_good(&file_output))
    {
        FileInput_dtor( &file_input, LEAVE_MEMORY );
        return;
    }
    while(FileInput_read(&file_input, &dongle, sizeof(dongle)))
	{
        FileOutput_write(&file_output, &dongle, sizeof(dongle));
    }
    FileInput_dtor(&file_input, LEAVE_MEMORY );
    FileOutput_dtor(&file_output, LEAVE_MEMORY );
}

static void pw_remove(char *app)
{
    struct dongle_data dongle;

    FileInput_ctor_Ex(&file_input, "dongle.dat");
    if (!FileInput_is_good(&file_input)) return;
    FileOutput_ctor_Ex(&file_output, "dongle.new", TRUE);
    if (!FileOutput_is_good(&file_output))
    {
        FileInput_dtor( &file_input, LEAVE_MEMORY );
        return;
    }
    while(FileInput_read(&file_input, &dongle, sizeof(dongle)))
	{
        if (memcmp(app, dongle.appname, 16)!=0)
            FileOutput_write(&file_output, &dongle, sizeof(dongle));
    }
    FileInput_dtor(&file_input, LEAVE_MEMORY );
    FileOutput_dtor(&file_output, LEAVE_MEMORY );
    File_remove("dongle.dat");
    File_rename("dongle.new", "dongle.dat");
}

static void pw_add(struct dongle_data *dongle)
{
    FileOutput_ctor_Ex(&file_output, "dongle.dat", TRUE);
    if (!FileOutput_is_good(&file_output)) return;
    FileOutput_seek(&file_output, 0, SEEK_END);
    FileOutput_write(&file_output, dongle, sizeof(struct dongle_data));
    FileOutput_dtor(&file_output, LEAVE_MEMORY );
}

// display a dialog if the file / pw doesnt exist
static    char txt0[24];
static    char txt1[24];
static    char txt2[24];
static    char txt3[24];
static    char txt4[24];
static    char txt5[24];
static    char txt6[24];
static void pw_display_dialog(
        struct module_t *main_module,
        char *info,
        char *app, // 16 bytes
        char *method)
{
    struct cDialog *dialog;
    struct cText *line0;
    struct cText *line1;
    struct cText *line2;
    struct cText *line3;
    struct cText *line4;
    struct cText *line5;
    struct cText *line6;
    int rc;
    char passwd[17];
    struct dongle_data dongle;
    int x, y;

    sprintf(txt0, "Program Needs  Password");
    sprintf(txt1, "To Buy a Password Goto");
    sprintf(txt2, "  www.DevCybiko.com");
    sprintf(txt3, "      'Passwords'");
    sprintf(txt4, "APP = %s", app);
    sprintf(txt5, "TYPE= %s", method);
    sprintf(txt6, "CyID= %ld", get_own_id());
     dialog = (struct cDialog *) malloc(sizeof(struct cDialog));
     line0 = (struct cText *) malloc(sizeof(struct cText));
     line1 = (struct cText *) malloc(sizeof(struct cText));
     line2 = (struct cText *) malloc(sizeof(struct cText));
     line3 = (struct cText *) malloc(sizeof(struct cText));
     line4 = (struct cText *) malloc(sizeof(struct cText));
     line5 = (struct cText *) malloc(sizeof(struct cText));
     line6 = (struct cText *) malloc(sizeof(struct cText));

     // alert dialog
     cDialog_ctor( dialog, info, "", mbOk, 0, main_module->m_process );
     cText_ctor(line0, txt0, mini_bold_font , CLR_BLACK );
     cText_ctor(line1, txt1, mini_bold_font , CLR_BLACK );
     cText_ctor(line2, txt2, mini_bold_font , CLR_BLACK );
     cText_ctor(line3, txt3, mini_bold_font , CLR_BLACK );
     x = 0;
     y = 5;
     cDialog_AddObj(dialog, line0, x+0, y+0 );
     cDialog_AddObj(dialog, line1, x+10, y+10 );
     cDialog_AddObj(dialog, line2, x+10, y+20 );
     cDialog_AddObj(dialog, line3, x+10, y+30 );
     rc = cDialog_ShowModal(dialog);
     cText_dtor(line0, FREE_MEMORY);
     cText_dtor(line1, FREE_MEMORY);
     cText_dtor(line2, FREE_MEMORY);
     cText_dtor(line3, FREE_MEMORY);

     cDialog_dtor(dialog, LEAVE_MEMORY);
     cDialog_ctor( dialog, "Enter Password", "", mbOk | mbEdit, 16, main_module->m_process );
     cText_ctor(line4, txt4, mini_bold_font , CLR_BLACK );
     cText_ctor(line5, txt5, mini_bold_font , CLR_BLACK );
     cText_ctor(line6, txt6, mini_bold_font , CLR_BLACK );
     x = 10;
     y = 0;
     cDialog_AddObj(dialog, line4, x+0, y+0 );
     cDialog_AddObj(dialog, line5, x+0, y+10 );
     cDialog_AddObj(dialog, line6, x+0, y+20 );
     rc = cDialog_ShowModal(dialog);
     if (rc == mrOk)
     {
        cDialog_GetEditText(dialog, passwd);
        pw_remove(app);
        memcpy(dongle.appname, app, 16);
        memcpy(dongle.passwd, passwd, 16);
        pw_add(&dongle);
     }
     cText_dtor(line4, FREE_MEMORY);
     cText_dtor(line5, FREE_MEMORY);
     cText_dtor(line6, FREE_MEMORY);
     cDialog_dtor(dialog, FREE_MEMORY);
     return;
}
//returns if password file exists and password is in dongle file
//otherwise loops forever waiting for user to enter password
void pw_check(struct module_t *main_module,
              char *appname,  //16 bytes
              int quietly)
{
    struct dongle_data dongle;
    char encoded_name[16];
    char password[16];
    int rc;
    long cyid;
    int true=1;

    // backup the dongle.dat file to dongle.bak
    pw_backup();

	// the appname is scrambled to make it harder to crack
	// unscrample the appname
	pw_scramble(appname, dongle.appname);

	// a little vanity here
	TRACE("%s: (C) 2001, The Alcor Group, Inc. All Rights Reserved", dongle.appname);

	// loop allowing user to enter dongle
        while(true)
	{
		//
		// if donglefile does not exist or dongle not found
		// a dialog will pop up indicating
		// what to do to get the dongle
		// including input form to enter the dongle
		// donglefile is of the form
		// appname=dongle (16 digit semi-hex code)
		// if dongle is entered, then continue on
		rc = pw_dongle_lookup(&dongle);

		if (rc)
		{
			// display dongle dialog and allow user to input
			// new dongle.  update dongle file with new dongle
			if (!quietly)
		                pw_display_dialog(main_module,
                                  "Missing Password",
                                  dongle.appname,
                                  dongle.appname[14]? &dongle.appname[14] : "a");
				// note: the last 2 characters are the dongle "type"
				//       byte 14 is a-z and byte 15 is always null
				//       early versions had no type info so a null
				//       in the 14th byte defaults to type 'a'
			continue;
		}


		// encode the dongle - a mixture of the appname and the CyID
		// it comes back scrambled to make it harder to hack
		// it wont look like a password in memory
        cyid = get_own_id();
		pw_encode(dongle.appname, cyid, encoded_name);

        // scramble the dongle.passwd
        pw_scramble(dongle.passwd, password);

		// compare the dongle to the newly encoded name
		// exit now if they are the same
#ifdef TEST
{
    int i;
    for (i=0; i<16; i++)
    {
        TRACE("%02x %02x %02x", dongle.passwd[i], password[i], encoded_name[i]);
    }
}
#endif
            if (memcmp(password, encoded_name, 16)==0)
			break;

		// if the password didnt match then show a dialog
		// indicating bad dongle and instructing how to get
		// a new one
		memset(encoded_name, 0, 16);
		if (!quietly)
		    pw_display_dialog(main_module,
                              "MisMatched Password",
                              dongle.appname, dongle.type);
	}
	memset(encoded_name, 0, 16);
}


#ifdef TEST
struct module_t main_module;

char appname[16] = {'B', '2', 'C', 'R', 'u', 'n', 't', 'i',
                    'm', 'e', 0, 0, 0, 0, 'b', 0};

main()
{
    char s[16];

    init_module(&main_module);
    pw_scramble(appname, s);
    TRACE("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x",
        s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7],
        s[8], s[9], s[10], s[11], s[12], s[13], s[14], s[15]);
    pw_check(&main_module, s, 0);
    return 0;
}

#endif
