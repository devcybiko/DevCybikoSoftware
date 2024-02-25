
/*	program DATABASE.C					*\
\*	WARNING: "advent.c" allocates GLOBAL storage space by	*\
\*		including "advdef.h".				*\
\*		All other modules use "advdec.h".		*/


//#include	<stdio.h>	/* drv = 1.1st file 2.def 3.A	*/
//#include	"advent.h"
//#include	"advdec.h"



/*
	Routine to fill travel array for a given location
*/
char *db_atrav;
int gettrav(int loc)
{
	int	i;
	long	t;
	char	*atrav, *aptr;

	if (db_atrav == NULL)
		db_atrav = MALLOC(256, char);
	atrav = db_atrav;
	strcpy(atrav, icave[loc - 1]);
	while (aptr = rindex(atrav, ','))
		*aptr = '\0';		/* terminate substring	*/
	aptr = &atrav[0];
	for (i = 0; i < MAXTRAV; ++i) {
		t = atoi(aptr);		/* convert to long int	*/
		itravel[i].tcond = (int) (t % 1000L);
		t /= 1000L;
		itravel[i].tverb = (int) (t % 1000L);
		t /= 1000L;
		itravel[i].tdest = (int) (t % 1000L);
		while (*(aptr++));		/* to next substring	*/
		if (!(*aptr)) {
		    itravel[++i].tdest = -1;/* end of array	*/
		    if (dbugflg)
			for (i = 0; i < MAXTRAV; ++i)
				printf("cave[%d] = %d %d %d\n", \
				loc, itravel[i].tdest, \
				itravel[i].tverb, itravel[i].tcond);
		    return;		/* terminate for loop	*/
		}
	}
	bug(33);
}

/*
	Function to scan a file up to a specified
	point and either print or return a string.
*/
int rdupto(FILE *fdi, int uptoc, int print, char *string)
{
	int	c;

    DBG0(">rdupto %s", __FILE__);
	while ((c = fgetc(fdi)) != uptoc) {
		if (c == EOF)
			return(0);
		if (c == '\r')
			continue;
		if (print)
			fputc(c, stdout);
		else
			*string++ = (char)c;
	}
	if (!print)
		*string = '\0';
    DBG0("<rdupto");
	return(1);
}

/*
	Function to read a file skipping
	a given character a specified number
	of times, with or without repositioning
	the file.
*/
int rdskip(FILE *fdi, int skipc, int n, int rewind)
{
	int	c;

	if (rewind)
		if (fseek(fdi, 0, 0) == -1)
			bug(31);
	while (n--)
		while ((c = fgetc(fdi)) != skipc)
			if (c == EOF)
				bug(32);
}

/*
	Routine to request a yes or no answer to a question.
*/
int yes(int msg1, int msg2, int msg3)
{
	char	answer[80];

	if (msg1)
		rspeak(msg1);
	fputc('>', stdout);
	fgets(answer, 80, stdin);
	if (tolower(answer[0]) == 'n') {
		if (msg3)
			rspeak(msg3);
		return(0);
	}
	if (msg2)
		rspeak(msg2);
	return(1);
}

/*
	Print a location description from "advent4.txt"
*/
int rspeak(int msg)
{
    DBG0(">rspeak %s", __FILE__);
	if (msg == 54)
		printf("ok.\n");
	else {
		if (dbugflg)
		    printf("Seek loc msg #%d @ %ld\n", msg, idx4[msg]);
		fseek(fd4, idx4[msg - 1], 0);
		rdupto(fd4, '#', 1, 0);
	}
    DBG0("<rspeak");
	return;
}

/*
	Print an item message for a given state from "advent3.txt"
*/
int pspeak(int item, int state)
{
	fseek(fd3, idx3[item - 1], 0);
	rdskip(fd3, '/', state+2, 0);
	rdupto(fd3, '/', 1, 0);
}

/*
	Print a long location description from "advent1.txt"
*/
int desclg(int loc)
{
DBG0(">desclg loc=%d", loc);
	fseek(fd1, idx1[loc - 1], 0);
	rdupto(fd1, '#', 1, 0);
DBG0("<desclg");
}

/*
	Print a short location description from "advent2.txt"
*/
int descsh(int loc)
{
	fseek(fd2, idx2[loc - 1], 0);
	rdupto(fd2, '#', 1, 0);
}

/*
	look-up vocabulary word in lex-ordered table.  words may have
	two entries with different codes. if minimum acceptable value
	= 0, then return minimum of different codes.  last word CANNOT
	have two entries(due to binary sort).
	word is the word to look up.
	val  is the minimum acceptable value,
		if != 0 return %1000
*/
int vocab(char *word, int val)
{
	int	v1, v2;

	if ((v1 = binary(word, wc, MAXWC)) >= 0) {
		v2 = binary(word, wc, MAXWC-1);
		if (v2 < 0)
			v2 = v1;
		if (!val)
			return(wc[v1].acode < wc[v2].acode\
			       ? wc[v1].acode : wc[v2].acode);
		if (val <= wc[v1].acode)
			return(wc[v1].acode % 1000);
		else if (val <= wc[v2].acode)
			return(wc[v2].acode % 1000);
		else
			return(-1);
	}
	else
		return(-1);
}

int binary(char *w, struct wac wctable[], int maxwc)
{
	int	lo, mid, hi, check;

	lo = 0;
	hi = maxwc - 1;
	while (lo <= hi) {
		mid = (lo + hi) / 2;
		if ((check = strcmp(w, wctable[mid].aword)) < 0)
			hi = mid - 1;
		else if (check > 0)
			lo = mid + 1;
		else
			return(mid);
	}
	return(-1);
}


/*
	Utility Routines
*/

/*
	Routine to test for darkness
*/
int dark(void)
{
	return(!(cond[loc] & LIGHT) &&
		(!prop[LAMP] ||
		!here(LAMP)));
}

/*
	Routine to tell if an item is present.
*/
int here(int item)
{
	return(place[item] == loc || toting(item));
}

/*
	Routine to tell if an item is being carried.
*/
int toting(int item)
{
	return(place[item] == -1);
}

/*
	Routine to tell if a location causes
	a forced move.
*/
int forced(int atloc)
{
	return(cond[atloc] == 2);
}

/*
	Routine true x% of the time.
*/
int pct(int x)
{
	return(rand() % 100 < x);
}

/*
	Routine to tell if player is on
	either side of a two sided object.
*/
int at(int item)
{
	return(place[item] == loc || fixed[item] == loc);
}

/*
	Routine to destroy an object
*/
int dstroy(int obj)
{
	move(obj, 0);
}

/*
	Routine to move an object
*/
int move(int obj, int where)
{
	int	from;

	from = (obj<MAXOBJ) ? place[obj] : fixed[obj];
	if (from>0 && from<=300)
		carry(obj, from);
	drop(obj, where);
}

/*
	Juggle an object
	currently a no-op
*/
int juggle(int loc)
{
}

/*
	Routine to carry an object
*/
int carry(int obj, int where)
{
	if (obj<MAXOBJ){
		if (place[obj] == -1)
			return;
		place[obj]=-1;
		++holding;
	}
}

/*
	Routine to drop an object
*/
int drop(int obj, int where)
{
	if (obj<MAXOBJ) {
		if (place[obj] == -1)
			--holding;
		place[obj]=where;
	}
	else
		fixed[obj-MAXOBJ]=where;
}

/*
	routine to move an object and return a
	value used to set the negated prop values
	for the repository.
*/
int put(int obj, int where, int pval)
{
	move(obj, where);
	return((-1)-pval);
}
/*
	Routine to check for presence
	of dwarves..
*/
int dcheck(void)
{
	int	i;

	for (i =1; i < (DWARFMAX-1); ++i)
		if (dloc[i] == loc)
			return(i);
	return(0);
}

/*
	Determine liquid in the bottle
*/
int liq(void)
{
	int	i, j;
	i=prop[BOTTLE];
	j=-1-i;
	return(liq2(i>j ? i : j));
}

/*
	Determine liquid at a location
*/
int liqloc(int loc)
{
	if (cond[loc]&LIQUID)
		return(liq2(cond[loc]&WATOIL));
	else
		return(liq2(1));
}

/*
	Convert  0 to WATER
		 1 to nothing
		 2 to OIL
*/
int liq2(int pbottle)
{
	return((1-pbottle)*WATER+(pbottle>>1)*(WATER+OIL));
}

/*
	Fatal error routine
*/
int bug(int n)
{
	printf("Fatal error number %d\n", n);
	exit(-1);
}


	

