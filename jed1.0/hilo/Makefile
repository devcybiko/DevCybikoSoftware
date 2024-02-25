CYBIKO_SDK = C:\Program Files\Cybiko\SDK
PP = vcpp
CC = vcc1
AS = vas
LN = vlink
LD = filer
RM = vrm

PROGRAM=hilo

.SUFFIXES : .c

all : $(PROGRAM).app

$(PROGRAM).app : bytecode.bin $(PROGRAM).o
	@echo building app archive...
        $(LD) a $@ @filer.list bytecode.bin "$(CYBIKO_SDK)"/lib/main.e

bytecode.bin : $(PROGRAM).o
	@echo linking ...
    $(LN) -o $@ $(PROGRAM).o ../jed.o

.c.o :
	@echo compiling $<...
    $(PP) $(CFLAGS) -I"$(CYBIKO_SDK)"/inc $< | $(CC) | $(AS) -O -o $@

clean :
	@echo cleaning...
        $(RM) -f $(PROGRAM).app $(PROGRAM).o

new : clean all
