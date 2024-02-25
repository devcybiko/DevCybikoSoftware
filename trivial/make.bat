2trv general.dat
call build general.bld
2trv tweens.dat
call build tweens.bld
vcc -o FileListForm.o FileListForm.c
call build trivial.bld
call build gentest.bld
