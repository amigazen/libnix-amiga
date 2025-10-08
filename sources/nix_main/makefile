SOURCEDIR=../../sources/nix_main

OBJECTS=__nocommandline.o _main.o

OPTIONS=-I $(SOURCEDIR)/../headers -I/netinclude/ $(CFLAGS)

vpath %.c $(SOURCEDIR)

REDEF=-D_DOSBase=___DOSBase \
      -D_UtilityBase=___UtilityBase \
      -D_MathIeeeSingBasBase=___MathIeeeSingBasBase \
      -D_MathIeeeSingTransBase=___MathIeeeSingTransBase \
      -D_MathIeeeDoubBasBase=___MathIeeeDoubBasBase \
      -D_MathIeeeDoubTransBase=___MathIeeeDoubTransBase \
      -D_LocaleBase=___LocaleBase

#Use private library bases to avoid naming collisions
%.o: %.c
	m68k-amigaos-gcc $(OPTIONS) -S $^ -o $*.S 2>&1 | tee $*.err
	m68k-amigaos-gcc -E -traditional $(REDEF) $*.S -o $*2.S
	m68k-amigaos-gcc $(OPTIONS) $*2.S -c -o $*.o
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all filelist subdirs clean veryclean

all: libnix_main.a

filelist:

subdirs:

clean:
	-rm *.o *.err

veryclean: clean
	-rm libnix_main.a

libnix_main.a: $(OBJECTS) $(SOURCEDIR)/makefile
	-rm $@
	/bin/ar -q /t/$@ $(OBJECTS)
	ranlib /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@
