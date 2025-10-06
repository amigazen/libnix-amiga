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
	gcc $(OPTIONS) -S $^ -o $*.S 2>&1|tee $*.err
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
	ar -q /tmp/$@ $(OBJECTS2)
	ranlib /tmp/$@
	echo "\$$$(V)" >>/tmp/$@
	cp /tmp/$@ .
	rm /tmp/$@

stdio/vfprintf.o: ../nix/stdio/vfprintf.c
	gcc $(OPTIONS) $^ -c -o stdio/vfprintf.o

stdio/vfscanf.o: ../nix/stdio/vfscanf.c
	gcc $(OPTIONS) $^ -c -o stdio/vfscanf.o
