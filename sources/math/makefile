SOURCEDIR=../../sources/math

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers -DFULL_SPECIFIERS $(CFLAGS)

vpath %.c $(SOURCEDIR)

SOURCEFILES=*/*

OBJECTS2=$(OBJECTS) \
         ../nix/stdio/printf.o ../nix/stdio/fprintf.o ../nix/stdio/sprintf.o \
         ../nix/stdio/vprintf.o ../nix/stdio/vsprintf.o stdio/vfprintf.o \
         ../nix/stdio/scanf.o ../nix/stdio/fscanf.o ../nix/stdio/sscanf.o \
         ../nix/stdio/vscanf.o ../nix/stdio/vsscanf.o stdio/vfscanf.o

SUBDIRS2=$(SUBDIRS) ../nix/stdio

REDEF=-D_DOSBase=___DOSBase \
      -D_UtilityBase=___UtilityBase \
      -D_MathIeeeSingBasBase=___MathIeeeSingBasBase \
      -D_MathIeeeSingTransBase=___MathIeeeSingTransBase \
      -D_MathIeeeDoubBasBase=___MathIeeeDoubBasBase \
      -D_MathIeeeDoubTransBase=___MathIeeeDoubTransBase \
      -D_LocaleBase=___LocaleBase

%.o: %.c
	gcc $(OPTIONS) -S $^ -o $*.S 2>&1 | tee $*.err
	gcc -E -traditional $(REDEF) $*.S -o $*2.S
	gcc $(OPTIONS) $*2.S -c -o $*.o
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean

all: libm.a

clean:
	-rm -r $(SUBDIRS)

veryclean:
	-rm -r *

$(SUBDIRS2):
	mkdir $@

libm.a: $(SUBDIRS2) $(OBJECTS2) $(SOURCEDIR)/makefile $(SOURCEDIR)/filelist
	-rm $@
	/bin/ar -q /t/$@ $(OBJECTS2)
	ranlib /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@

stdio/vfprintf.o: ../nix/stdio/vfprintf.c
	mkdir -p stdio
	gcc $(OPTIONS) -S $^ -o stdio/vfprintf.S 2>&1 | tee stdio/vfprintf.err
	gcc -E -traditional $(REDEF) stdio/vfprintf.S -o stdio/vfprintf2.S
	gcc $(OPTIONS) stdio/vfprintf2.S -c -o stdio/vfprintf.o
	-rm stdio/vfprintf.S stdio/vfprintf2.S
	-if test ! -s stdio/vfprintf.err; then rm stdio/vfprintf.err; fi

stdio/vfscanf.o: ../nix/stdio/vfscanf.c
	mkdir -p stdio
	gcc $(OPTIONS) -S $^ -o stdio/vfscanf.S 2>&1 | tee stdio/vfscanf.err
	gcc -E -traditional $(REDEF) stdio/vfscanf.S -o stdio/vfscanf2.S
	gcc $(OPTIONS) stdio/vfscanf2.S -c -o stdio/vfscanf.o
	-rm stdio/vfscanf.S stdio/vfscanf2.S
	-if test ! -s stdio/vfscanf.err; then rm stdio/vfscanf.err; fi
