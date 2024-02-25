# use 'vmake' (not 'make'!) to run this script!

# set this to where Cybiko SDK actually resides
#CYBIKO_SDK = C:\Program Files\Cybiko Inc\Cybiko SDK

# you may also want to change this...
NAME = advent
OBJ = src/$(NAME).o
RES = res/0.help res/filer.list \
      res/root.ico res/root.inf res/root.spl

PP = vcpp
CC = vcc1
AS = vas
LN = vlink
LD = filer
RM = vrm

.SUFFIXES : .c

all : $(NAME).app

# You must add to archive "$(CYBIKO_SDK)"/lib/main.e ,
# your bytecode and application resources
# (*.pic better place first).
# *.spl - splash screen.
# *.help - help file.
# *.inf - information for programm manager.
# For more details see filer.exe manual.
$(NAME).app : tmp/bytecode.bin $(RES)
	@echo building app archive...
	@$(LD) a $@ @res/filer.list tmp/bytecode.bin "$(CYBIKO_SDK)"/lib/main.e

tmp/bytecode.bin : $(OBJ)
	@echo linking ...
	@$(LN) -o $@ src/*.o

.c.o :
	@echo compiling $<...
	@$(PP) -I"$(CYBIKO_SDK)"/inc $< | $(CC) | $(AS) -O -o $@

clean :
	@echo cleaning...
	@$(RM) -f tmp/*.* src/*.o $(NAME).app

new : clean all
