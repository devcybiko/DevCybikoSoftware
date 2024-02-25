OBJS = helloworld.o jed.o
CYBIKO_SDK = C:\Program Files\Cybiko\SDK
CFLAGS =

PP = vcpp
CC = vcc1
AS = vas
LN = vlink
LD = filer
RM = vrm

.SUFFIXES : .c

helloworld.app : tmp/bytecode.bin $(OBJS)
	@echo building app archive...
	@$(LD) a $@ @res/filer.list tmp/bytecode.bin "$(CYBIKO_SDK)"/lib/main.e

tmp/bytecode.bin : $(OBJ)
	@echo linking ...
        $(LN) -o $@ $(OBJ)
.c.o :
	@echo compiling $<...
        @$(PP) $(CFLAGS) -I"$(CYBIKO_SDK)"/inc $< | $(CC) | $(AS) -O -o $@

clean :
	@echo cleaning...
	$(RM) -f tmp/*.* src/helloworld.o src/helloworld.app

new : clean all

