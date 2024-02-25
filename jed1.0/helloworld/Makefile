CYBIKO_SDK = C:\Program Files\Cybiko\SDK
PP = vcpp
CC = vcc1
AS = vas
LN = vlink
LD = filer
RM = vrm

.SUFFIXES : .c

all : helloworld.app

helloworld.app : bytecode.bin helloworld.o
	@echo building app archive...
        $(LD) a $@ @helloworld.list bytecode.bin "$(CYBIKO_SDK)"/lib/main.e

bytecode.bin : helloworld.o
	@echo linking ...
    $(LN) -o $@ helloworld.o ../jed.o

.c.o :
	@echo compiling $<...
    $(PP) $(CFLAGS) -I"$(CYBIKO_SDK)"/inc $< | $(CC) | $(AS) -O -o $@

clean :
	@echo cleaning...
        $(RM) -f helloworld.app helloworld.o

new : clean all
