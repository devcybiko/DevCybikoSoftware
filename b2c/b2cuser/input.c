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
static int xtruex = 1;
static char *disp;

static void init_input()
{
    b2c->dk = DirectKeyboard_get_instance();
    b2c->keyclicks = get_clicks_enabled();
	b2c->msgbuf = calloc(MAX_MSGBUF, 1);
}

static void destroy_input()
{
    DirectKeyboard_dtor(b2c->dk, FREE_MEMORY);
    set_clicks_enabled((bool)b2c->keyclicks);
	free(b2c->msgbuf);
	if (disp) free(disp);
}

static void _repaint_string(int x, int y)
{
	int len=Graphics_string_width(b2c->main_module.m_gfx, b2c->buf);

    Graphics_set_font(b2c->main_module.m_gfx, b2c->font);
    TGraph_set_color(b2c->main_module.m_gfx, b2c->paper);
    if (_c_coords)
		TGraph_fill_rect(b2c->main_module.m_gfx, x, y, len, b2c->ht);
    else
		TGraph_fill_rect(b2c->main_module.m_gfx, 80+x, 50-y, len, b2c->ht);
	_printxy(x, y, "%s", b2c->buf);
    DisplayGraphics_show(b2c->main_module.m_gfx);
    return;
}

static void _handle_char(int x, int y, int c)
{
    switch(c)
    {
        case KEY_BACKSPACE:
		case KEY_DEL:
        {
            if (b2c->cursor)
            {
                b2c->cursor--;
				b2c->buf[b2c->cursor] = ' ';
				_repaint_string(x,y);
                b2c->buf[b2c->cursor] = 0;
            }
            _repaint_string(x, y);
        } break;
        default:
            if (c >=32 && c <128)
            {
                if (b2c->cursor == sizeof(b2c->buf)-1)
                {
                    _error_noise();
                    goto EARLY_EXIT;
                }
                else
                {
                    b2c->buf[b2c->cursor] = (char) c;
                    b2c->cursor++;
                    b2c->buf[b2c->cursor] = 0;
                    _repaint_string(x, y);
                }
            }
            else
            {
                _error_noise();
                goto EARLY_EXIT;
            }
            break;
    }
EARLY_EXIT:
    return;
}

void _input_fixed(fixed *d, char *prompt)
{
    char s[64];
    _input_string(s, sizeof(s), prompt);
	*d = fixed_from_string(s);
}

void _input_long(long *d, char *prompt)
{
    char s[32];
    _input_string(s, sizeof(s), prompt);
    *d = atoul(s);
}

void _input_int(int *d, char *prompt)
{
    char s[32];
    _input_string(s, sizeof(s), prompt);
    *d = (int) atoul(s);
}

void _input_char(char *d, char *prompt)
{
    char s[32];
    _input_string(s, sizeof(s), prompt);
    *d = (char)atoul(s);
}

void _inputxy_fixed(int x, int y, fixed *d, char *prompt)
{
    char s[32];
    _inputxy_string(x, y, s, sizeof(s), prompt);
	*d = fixed_from_string(s);
}

void _inputxy_int(int x, int y, int *d, char *prompt)
{
    char s[32];
    _inputxy_string(x, y, s, sizeof(s), prompt);
    *d = (int) atoul(s);
}

void _inputxy_long(int x, int y, long *d, char *prompt)
{
    char s[32];
    _inputxy_string(x, y, s, sizeof(s), prompt);
    *d = atoul(s);
}

void _inputxy_char(int x, int y, char *d, char *prompt)
{
    char s[32];
    _inputxy_string(x, y, s, sizeof(s), prompt);
    *d = (char)atoul(s);
}

void _inputxy_string(int x, int y, char *s, int len, char *prompt)
{
	int key;

	if (prompt) 
	{
		_printxy(x, y, "%s", prompt);
		x = x + Graphics_string_width(b2c->main_module.m_gfx, prompt);
	    DisplayGraphics_show(b2c->main_module.m_gfx);
	}

	b2c->buf[0] = 0;
	b2c->cursor = 0;
	while(xtruex)
	{
		key = _getchar();
		if (key == KEY_ENTER) 
		{
			strncpy(s, b2c->buf, len);
			s[len-1] = 0;
			break;
		}
        _handle_char(x, y, key);
    }  //  while(!exit_loop)
    return;
}

void _input_string(char *s, int len, char *prompt)
{
	int key;
	int old_c_coords=_c_coords;

	_c_coords = 1;

	if (prompt) _print("%s", prompt);
	else _print("");

	b2c->buf[0] = 0;
	b2c->cursor = 0;
	while(xtruex)
	{
		key = _getchar();
		if (key == KEY_ENTER) 
		{
			strncpy(s, b2c->buf, len);
			s[len-1] = 0;
			strcat(b2c->lines[b2c->currline-1], b2c->buf);
			break;
		}
        _handle_char(b2c->x, b2c->y, key);
    }  //  while(!exit_loop)
	_c_coords = old_c_coords;
    return;
}

static int directkey(int which)
{
	DirectKeyboard_scan(b2c->dk);
	if( DirectKeyboard_is_key_pressed( b2c->dk, which ) ) return which;
	return 0;
}

int _key(int which)
{
	struct Message* message=0;
	int key = 0;
	int true=1;
	static int already_in_key=0;

	//
	// update the music sequence if its playing in the background
	//
	if (b2c->background_playing)
	{
		if (b2c->channel[0] && !MSequence_is_playing(b2c->channel[0]))
			MSequence_play_background(b2c->channel[0]);
	}

	//
	// if a key is selected then do directkey
	// esc key cannot be detected this way
	// must use x = key(0) to detect escape
	// kludge alert - key(KEY_ESC) is special case of doing normal escape processing
	if (which && (which != KEY_ESC)) return directkey(which);

	if (already_in_key) goto EARLY_EXIT;

TOP:
	message = cWinApp_get_message(b2c->main_module.m_process, 1, 1, MSG_USER+1024);
	if (!message) goto EARLY_EXIT;

	switch(message->msgid)
	{                            
		case MSG_SHUTUP:     //  Processes system exit signal.
		case MSG_QUIT:
			Message_delete(message);
			_exit_basic(0);
			break;
		case MSG_LOSTFOCUS:
			if (_multitask_) _background_ = 1;
			else
			{
			    while(true)
				{
					if (message) Message_delete(message);
					message = cWinApp_get_message(b2c->main_module.m_process, 1, 1, MSG_USER+1024);
					if (message && (message->msgid == MSG_GOTFOCUS)) break;
				}
				if (disp)
				{
					TGraph_put_background(b2c->main_module.m_gfx, disp );
					free(disp);
					disp = 0;
					DisplayGraphics_show(b2c->main_module.m_gfx);
				}
			}
			break;
		case MSG_GOTFOCUS:
			if (_multitask_) _background_ = 0;
			if (disp)
			{
				TGraph_put_background(b2c->main_module.m_gfx, disp );
				free(disp);
				disp = 0;
				DisplayGraphics_show(b2c->main_module.m_gfx);
			}
			break;
		case MSG_PAINT:
			if (disp)
			{
				TGraph_put_background(b2c->main_module.m_gfx, disp );
				free(disp);
				disp = 0;
				DisplayGraphics_show(b2c->main_module.m_gfx);
			}
			break;
		case MSG_KEYDOWN:    //  Processes keyboard messages.
			key = Message_get_key_param(message)->scancode;
			switch(key)
			{
				case KEY_ESC:
				{
					// kludge alert - which==KEY_ESC does regular escape processing when _escape_ is off
					if (!_escape_ && (which != KEY_ESC)) goto EARLY_EXIT; // if escape processing is off
					if (_basic_ask_exit("Esc Pressed - Quit?"))
					{
						Message_delete(message);
						_exit_basic(0);
					}
					key = 0;
					break;
				}
				case KEY_HELP:
				{
					if (disp) 
					{
						free(disp);
						disp = 0;
					}
					if (!_help_) goto EARLY_EXIT;  // if help processing is off
					play_tone(-1);
					vibrate(0);
					_music(MUSIC_LOAD, 0, NULL); //free channel 0
					_music(MUSIC_LOAD, 1, NULL); //free channel 1
					disp = (char* ) malloc( TGraph_get_bytes_total( b2c->main_module.m_gfx ) );
					memcpy(disp,
						DisplayGraphics_get_page_ptr(b2c->main_module.m_gfx, 0),
						TGraph_get_bytes_total(b2c->main_module.m_gfx));
					cWinApp_defproc(b2c->main_module.m_process, message);
					Message_delete(message);
					key = 0;
					goto TOP;
					break;
				}
                case KEY_ENTER:
                case KEY_UP:
                case KEY_DOWN:
                case KEY_LEFT:
                case KEY_RIGHT:
                case KEY_DEL:
                case KEY_BACKSPACE:
				case KEY_INS:
				case KEY_TAB:
				case KEY_SELECT:
					break;
				default:
					key = 0;
					break;
			}
			break;
		case MSG_CHARTYPED:
		{
			key = Message_get_key_param(message)->ch;
			break;
		}
		default:             //  Processes all unprocessed messages.
		{
			if (message->msgid >= MSG_USER)
			{
				struct Buffer *bufptr;
				//TRACE("...msgid=%d", message->msgid);
				if (Message_has_buffer(message))
				{
					bufptr = Message_get_buffer(message);
					Buffer_load_string(bufptr, b2c->msgbuf, 0, MAX_MSGBUF);
				}
				else
				{
					strcpy(b2c->msgbuf, "");
				}
				already_in_key++;
				onmessage(
					message->cyid_from,
					message->msgid-MSG_USER,
					b2c->msgbuf);
				already_in_key--;
			}
			else
			{
				cWinApp_defproc(b2c->main_module.m_process, message);
			}
			break;
		}
	}
EARLY_EXIT:
	if (message) Message_delete(message);
	return key;
}

int _getkey()
{
	int key;

	while((key=_key(0)) == 0);
	return key;
}

static cook_raw_key(int c)
{
	static int shift=0;

    switch(c)
    {
        case KEY_SHIFT:
        {
            if (shift == KEY_SHIFT) shift = 0;
            else shift = KEY_SHIFT;
			c = 0;
			break;
        }
        case KEY_CONTROL:
        {
            if (shift == KEY_CONTROL) shift = 0;
            else shift = KEY_CONTROL;
			c = 0;
			break;
        }
        default:
		{
            if (c >=32 && c <128)
            {
				if (shift == KEY_SHIFT)
                {
					c = uppercase[c-32];
		            shift = 0;
                }
				else if (shift == KEY_CONTROL)
                {
					c = controlcase[c-32];
		            shift = 0;
                }
            }
            break;
		}
    }
	return c;
}

/** non-blocking cooked key **/
int _char(int which)
{
	int key = cook_raw_key(_key(which));
	return key;
}

/** blocking cooked key **/
int _getchar()
{
	int key=0;
	
	while (key==0)
	{
		key = cook_raw_key(_key(0));
	}
	return key;
}

void _keyclick(int state)
{
    set_clicks_enabled((bool)state);
}

