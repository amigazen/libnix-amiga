# Dedicated makefile for libb variant nix library
# Built with -fbaserel -DSMALL_DATA flags
#
# This makefile is designed to be called from lib/libb/nix/ directory

V=VER: libnix 3.1 (7.10.2025)
CFLAGS=-Wall -O3 -DOS_20_ONLY -fbaserel -DSMALL_DATA

CC=m68k-amigaos-gcc
CPP=m68k-amigaos-gcc
AS=m68k-amigaos-gcc
AR=/bin/ar
RANLIB=m68k-amigaos-ranlib

#### End system configuration section ####

ifneq ($(TARGET),clean)
include ../../../sources/nix/filelist
endif

CURDIR = $(shell pwd)

OPTIONS=-I../../../sources/headers -I../../../sources/nix/headers -I/netinclude/  $(CFLAGS)

vpath %.c ../../../sources/nix ../../../sources/nix/assert ../../../sources/nix/ctype ../../../sources/nix/errno ../../../sources/nix/extra ../../../sources/nix/locale ../../../sources/nix/math ../../../sources/nix/misc ../../../sources/nix/setjmp ../../../sources/nix/signal ../../../sources/nix/socket ../../../sources/nix/stdio ../../../sources/nix/stdlib ../../../sources/nix/string ../../../sources/nix/time

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
	$(CPP) -E -traditional $(REDEF) $*.S -o $*2.S
	$(CC) $(OPTIONS) $*2.S -c -o $@
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi

all: $(SUBDIRS) $(OBJECTS) libnix.a

$(SUBDIRS):
	mkdir -p $@

libnix.a: $(SUBDIRS) $(OBJECTS) ../../../sources/nix/Makefile ../../../sources/nix/filelist
	@mkdir -p /t
	$(AR) -r /t/$@ $(OBJECTS)
	$(RANLIB) /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@

clean:
	-rm -f *.o *.a *.err
	-rm -rf $(SUBDIRS)

veryclean: clean
	-rm -f filelist
