# Generated automatically from Makefile.in by configure.
#### Start of system configuration section. ####

srcdir =	.

CC =		m68k-amigaos-gcc
CPP =		m68k-amigaos-gcc -E
AS =		m68k-amigaos-as

AR =		/bin/ar
RANLIB =	m68k-amigaos-ranlib
AWK =		gawk
V	=	VER: libnix 3.1 (08.10.2025)
CFLAGS	=	-Wall -m68020-60 -O2 -msoft-float -funroll-loops -fomit-frame-pointer -noixemul -I../headers -g

#### End system configuration section ####

ifneq ($(TARGET),clean)
include ../../sources/nix/filelist
endif

CURDIR = $(shell pwd)

OPTIONS=-I../../sources/headers -I../../sources/nix/headers -I/netinclude/  $(CFLAGS)

vpath %.c ../../sources/nix ../../sources/nix/assert ../../sources/nix/ctype ../../sources/nix/errno ../../sources/nix/extra ../../sources/nix/locale ../../sources/nix/math ../../sources/nix/misc ../../sources/nix/setjmp ../../sources/nix/signal ../../sources/nix/socket ../../sources/nix/stdio ../../sources/nix/stdlib ../../sources/nix/string ../../sources/nix/time

REDEF=-D_DOSBase=___DOSBase \
      -D_UtilityBase=___UtilityBase \
      -D_MathIeeeSingBasBase=___MathIeeeSingBasBase \
      -D_MathIeeeSingTransBase=___MathIeeeSingTransBase \
      -D_MathIeeeDoubBasBase=___MathIeeeDoubBasBase \
      -D_MathIeeeDoubTransBase=___MathIeeeDoubTransBase \
      -D_LocaleBase=___LocaleBase

%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(OPTIONS) -S $< -o $*.S 2>&1 | tee $*.err
	$(CPP) -traditional $(REDEF) $*.S -o $*2.S
	$(CC) $(OPTIONS) $*2.S -c -o $@
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean

all: libnix.a

clean:
	-rm -f */*.o *.a

filelists:
	# filelist is now hardcoded - do not delete
	cd ../ && make filelists

$(SUBDIRS):
	mkdir -p $@

libnix.a: $(SUBDIRS) $(OBJECTS) ../../sources/nix/Makefile ../../sources/nix/filelist
	$(AR) -r /t/$@ $(OBJECTS)
	$(RANLIB) /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@
