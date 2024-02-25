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
static void init_music()
{
}

static void destroy_music()
{
	play_tone(-1);
    vibrate(0);
    _music(MUSIC_LOAD, 0, NULL); //free channel 0
    _music(MUSIC_LOAD, 1, NULL); //free channel 1
}


void _music(int opn, int channel, char *filename)
{
	switch(opn) {
	case MUSIC_LOAD:
		if (b2c->channel[channel])
		{
			MSequence_stop(b2c->channel[channel]);
			MSequence_dtor(b2c->channel[channel], FREE_MEMORY);
			b2c->channel[channel] = NULL;
		}
        if (filename)
        {
            b2c->channel[channel] = (struct MSequence *) malloc(sizeof(struct MSequence));
            MSequence_ctor(b2c->channel[channel], filename);
        }
		break;
	case MUSIC_PLAY:
		if (b2c->channel[channel])
		{
			if (channel==0)
                        {
				MSequence_play_background(b2c->channel[channel]);
                                b2c->background_playing = 1;
                        }
			else
				MSequence_play(b2c->channel[channel]);
		}
		break;
	case MUSIC_STOP:
		if (b2c->channel[channel])
        {
            if (channel == 0) b2c->background_playing = 0;
			MSequence_stop(b2c->channel[channel]);
        }
		break;
	}
}

void _vibrate(int n)
{
	vibrate(n);
	return;
}

/**
 ** plays a single tone, -1=stop tone
 **/
void _beep(int sound)
{
    play_tone(sound);
}



