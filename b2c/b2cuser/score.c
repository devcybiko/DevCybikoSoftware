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
#define MAX_SCORES 10

/*
 * FUNCTION: init_high_scores
 *
 * DESCRIPTION: Performs initialization of the high scores archive
 *
 * PARAMETERS: none 
 *
 * RETURNS: nothing
 */
static void init_high_scores( void )
{
  struct Input* ptr_input = 
    Archive_open_Ex( b2c->main_module.m_process->module->archive, "score.inf" );

  if (ptr_input)
  {
	  b2c->high_scores = calloc(MAX_SCORES, sizeof(struct score_t));
	  // Loads high scores from the "score.inf"
	  Input_read( ptr_input, b2c->high_scores, sizeof(struct score_t)*MAX_SCORES);

	  Input_dtor( ptr_input, FREE_MEMORY );
  }
}

/*
 * FUNCTION: update_high_scores
 *
 * DESCRIPTION: Updates current high scores
 *
 * PARAMETERS: none 
 *
 * RETURNS: nothing
 */
void _update_high_scores( long score )
{
  int index;
  struct score_t* high_scores_buffer;

  if (b2c->high_scores == (struct score_t *) NULL) return; 

  high_scores_buffer = malloc( (MAX_SCORES-1) * sizeof(struct score_t) );
  
  for( index = 0; index < MAX_SCORES; index++ )
  {
    if( score > b2c->high_scores[ index ].score )
    {
      // Shifts old high scores
      if( index != (MAX_SCORES-1) )
      {
        memcpy( high_scores_buffer, b2c->high_scores, sizeof(struct score_t) * (MAX_SCORES-1));
        memcpy( &b2c->high_scores[index + 1], &high_scores_buffer[index], ( (MAX_SCORES-1) - index ) * sizeof(struct score_t) );
      }
      // Stores new high score
      b2c->high_scores[ index ].score = score;
      b2c->high_scores[ index ].cyid = get_own_id();
      b2c->high_scores[ index ].time = time();
      strncpy( b2c->high_scores[ index ].nickname, ptr_Finder->mf.f_nick, NICKNAMESIZE ); 
      break;
    }
  }
  free( high_scores_buffer );
}

/*
 * FUNCTION: destroy_high_scores
 *
 * DESCRIPTION: Releases allocated resources of the high scores archive
 *
 * PARAMETERS: none 
 *
 * RETURNS: nothing
 */
static void destroy_high_scores( void )
{
  struct Output* ptr_output;
  
  if (b2c->high_scores == (struct score_t *) NULL) return;

  ptr_output = 
    Archive_open_write_Ex( b2c->main_module.m_process->module->archive,
      "score.inf");

  // Stores high scores in the "score.inf" archive
  Output_write( ptr_output, b2c->high_scores, sizeof( struct score_t )*MAX_SCORES);

  Output_dtor( ptr_output, FREE_MEMORY );
  free(b2c->high_scores);
}

/*
 * FUNCTION: show_high_scores
 *
 * DESCRIPTION: Shows the best scores of the game
 *
 * PARAMETERS: none 
 *
 * RETURNS: nothing
 */
static const char* sz_month[ 12 ] =
{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"  
};

void _show_high_scores( void )
{
  int index;
  char* item_text;
  struct Time high_score_time;
  int x, y, w;
  int width;
  int n = 5;
  int right;

  if (b2c->high_scores == (struct score_t *) NULL) return;

  // Allocates resources  
  item_text = (char*) malloc( 48 );

  DisplayGraphics_set_font(b2c->main_module.m_gfx, b2c->font);
  x = 0;
  y = (100-b2c->ht*n)/2;
  sprintf( item_text, "%08ld......%02d %s %04d", 0, 0, "Jan", 0);
  width = DisplayGraphics_string_width(b2c->main_module.m_gfx, item_text);
  x = (160-width)/2;
  right = 160 - x;
  DisplayGraphics_set_color(b2c->main_module.m_gfx, b2c->paper);
  DisplayGraphics_fill_rect(b2c->main_module.m_gfx, x-1, y-1, width+2, b2c->ht*n+2);
  DisplayGraphics_set_color(b2c->main_module.m_gfx, b2c->ink);

  // Fills the menu's items
  for( index = 0; index < n; index++ )
  {
    Time_decode( &high_score_time, b2c->high_scores[ index ].time );

    sprintf( item_text, "%8ld......%02d %s %04d",
        b2c->high_scores[ index ].score,
	    high_score_time.day,
        sz_month[ high_score_time.month - 1 ],
        high_score_time.year + 1900 );

    width = DisplayGraphics_string_width(b2c->main_module.m_gfx, item_text);
	x = right - width;
    DisplayGraphics_draw_text(b2c->main_module.m_gfx, item_text, x, y);
	y = y + b2c->ht;
  }
  if (_show_) DisplayGraphics_show(b2c->main_module.m_gfx);
  free( item_text );
}
