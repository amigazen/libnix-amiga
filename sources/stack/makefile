SOURCEDIR=../../sources/stack

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers $(CFLAGS)

vpath %.c $(SOURCEDIR)

SOURCEFILES=*.c

REDEF=-D_DOSBase=___DOSBase

%.o: %.c
	m68k-amigaos-gcc $(OPTIONS) -S $^ -o $*.S 2>&1 | tee $*.err
	m68k-amigaos-gcc -E -traditional $(REDEF) $*.S -o $*2.S
	m68k-amigaos-gcc $(OPTIONS) $*2.S -c -o $*.o
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean

all: libstack.a

clean:
	-rm -f *.o

veryclean:
	-rm -f *.o *.a *.err

libstack.a: $(OBJECTS) $(SOURCEDIR)/makefile $(SOURCEDIR)/filelist
	-rm $@
	/bin/ar -q /t/$@ $(OBJECTS)
	ranlib /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@
