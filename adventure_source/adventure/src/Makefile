# Colossal Cave Adventure Makefile

HEADERS= advcave.h advdec.h advdef.h advent.h advtext.h advword.h proto.h
SRC= advent.c database.c english.c itverb.c turn.c verb.c
OBJ= advent.o database.o english.o itverb.o turn.o verb.o
DATA= advent1.txt advent2.txt advent3.txt advent4.txt

CFLAGS= -O
LDFLAGS=
CC= cc

all: advent

advent: $(OBJ)
	cc -o advent $(CFLAGS) $(LDFLAGS) $(OBJ)

advent0: advent0.o
	cc -o advent0 $(CFLAGS) $(LDFLAGS) advent0.o

clean:
	rm -f *.o *.err advent advent0 advtext.h

install:
	cp -f advent /usr/local/bin
	chmod 0644 $(DATA)
	cp -f $(DATA) /usr/local/lib/games

advtext.h: advent0 $(DATA)
	advent0

advent.o: advent.c $(HEADERS)
database.o: database.c $(HEADERS)
english.o: english.c $(HEADERS)
itverb.o: itverb.c $(HEADERS)
turn.o: turn.c $(HEADERS)
verb.o: verb.c $(HEADERS)

