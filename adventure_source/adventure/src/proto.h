#ifdef __STDC__
# define	P(s) s
#else
# define P(s) ()
#endif


/* advent.c */
/*      37 */ int main (int argc , char **argv );
/*      89 */ int scanint (int *pi , char *str );
/*     106 */ int initplay (void );
/*     180 */ int opentxt (void );
/*     207 */ int saveadv (void );
/*     244 */ int restore (void );
char *game_name (char *username);

/* database.c */
/*      25 */ int gettrav (int loc );
/*      62 */ int rdupto (FILE *fdi , int uptoc , int print , char *string );
/*      89 */ int rdskip (FILE *fdi , int skipc , int n , int rewind );
/*     108 */ int yes (int msg1 , int msg2 , int msg3 );
/*     130 */ int rspeak (int msg );
/*     147 */ int pspeak (int item , int state );
/*     158 */ int desclg (int loc );
/*     168 */ int descsh (int loc );
/*     184 */ int vocab (char *word , int val );
/*     208 */ int binary (char *w , struct wac wctable [], int maxwc );
/*     237 */ int dark (void );
/*     247 */ int here (int item );
/*     256 */ int toting (int item );
/*     266 */ int forced (int atloc );
/*     275 */ int pct (int x );
/*     285 */ int at (int item );
/*     294 */ int dstroy (int obj );
/*     303 */ int move (int obj , int where );
/*     318 */ int juggle (int loc );
/*     326 */ int carry (int obj , int where );
/*     340 */ int drop (int obj , int where );
/*     357 */ int put (int obj , int where , int pval );
/*     367 */ int dcheck (void );
/*     380 */ int liq (void );
/*     391 */ int liqloc (int loc );
/*     405 */ int liq2 (int pbottle );
/*     414 */ int bug (int n );

/* english.c */
/*      21 */ int english (void );
/*     100 */ int analyze (char *word , int *type , int *value );
/*     130 */ int getwords (void );
/*     150 */ int outwords (void );

/* itverb.c */
/*      16 */ int itverb (void );
/*      91 */ int ivtake (void );
/*     116 */ int ivopen (void );
/*     143 */ int ivkill (void );
int iveat(void);
int ivfill(void);
/*     193 */ int ivdrink (void );
/*     207 */ int ivquit (void );
/*     231 */ int ivfoo (void );
/*     288 */ int inventory (void );
/*     312 */ int addobj (int obj );

/* turn.c */
/*      18 */ int turn (void );
/*     116 */ int describe (void );
/*     133 */ int descitem (void );
/*     165 */ int domove (void );
/*     199 */ int goback (void );
/*     242 */ int copytrv (struct trav *trav1 , struct trav *trav2 );
/*     258 */ int dotrav (void );
/*     326 */ int badmove (void );
/*     344 */ int spcmove (int rdest );
/*     396 */ int dwarfend (void );
/*     405 */ int normend (void );
/*     414 */ int score (void );
/*     467 */ int death (void );
/*     499 */ int doobj (void );
/*     560 */ int trobj (void );
/*     572 */ char *probj (int object );
/*     581 */ int dwarves (void );
/*     688 */ int dopirate (void );
/*     742 */ int stimer (void );

/* verb.c */
/*      16 */ int trverb (void );
/*     106 */ int vtake (void );
/*     182 */ int vdrop (void );
/*     271 */ int vopen (void );
/*     357 */ int vsay (void );
/*     368 */ int von (void );
/*     387 */ int voff (void );
/*     400 */ int vwave (void );
/*     417 */ int vkill (void );
/*     484 */ int vpour (void );
/*     523 */ int veat (void );
/*     546 */ int vdrink (void );
/*     562 */ int vthrow (void );
/*     658 */ int vfind (void );
/*     681 */ int vfill (void );
/*     721 */ int vfeed (void );
/*     780 */ int vread (void );
/*     816 */ int vblast (void );
/*     834 */ int vbreak (void );
/*     861 */ int vwake (void );
/*     874 */ int actspk (int verb );
/*     891 */ int needobj (void );

#undef P
