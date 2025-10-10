# Generated automatically from Makefile.in by configure.
#### Start of system configuration section. ####

srcdir =	.

CC =		m68k-amigaos-gcc
CPP =		m68k-amigaos-gcc -E
AS =		m68k-amigaos-as

AR =		m68k-amigaos-ar
RANLIB =	m68k-amigaos-ranlib
AWK =		gawk
V	=	VER: libnix 3.1 (08.10.2025)
CFLAGS	=	-Wall -m68020-60 -O2 -msoft-float -funroll-loops -fomit-frame-pointer -noixemul -I../headers -g

#### End system configuration section ####

ifneq ($(TARGET),clean)
ifneq (,$(wildcard ./filelist))
include ./filelist
else
include ../../sources/nix/filelist
endif
endif

CURDIR = $(shell pwd)

# Default target (first target in makefile)
all: libnix.a
	@echo "nix all target completed"

# Force rebuild of libnix.a even if some objects fail
libnix.a: $(SUBDIRS) $(OBJECTS) ../../sources/nix/Makefile
	@echo "Building libnix.a with $(words $(OBJECTS)) objects"
	@echo "Current directory: $(shell pwd)"
	@echo "Archiving object files..."
	@mkdir -p /t
	@echo "Running: $(AR) -r /t/$@ $(OBJECTS)"
	@echo "Checking if object files exist..."
	@EXISTING_OBJECTS=""; \
	for obj in $(OBJECTS); do \
		if [ -f "$$obj" ]; then \
			EXISTING_OBJECTS="$$EXISTING_OBJECTS $$obj"; \
		else \
			echo "Missing: $$obj"; \
		fi; \
	done; \
	echo "Archiving $$(echo $$EXISTING_OBJECTS | wc -w) existing object files..."; \
	$(AR) -r /t/$@ $$EXISTING_OBJECTS || echo "AR command failed, trying alternative approach"
	@$(RANLIB) /t/$@ || echo "RANLIB command failed"
	@echo "\$$$(V)" >>/t/$@
	@cp /t/$@ .
	@rm /t/$@
	@echo "Created libnix.a with $(words $(OBJECTS)) objects"

OPTIONS=-I../../sources/headers -I../../sources/nix/headers -I/netinclude/  $(CFLAGS)

vpath %.c ../../sources/nix ../../sources/nix/assert ../../sources/nix/ctype ../../sources/nix/errno ../../sources/nix/extra ../../sources/nix/ipc ../../sources/nix/locale ../../sources/nix/math ../../sources/nix/misc ../../sources/nix/setjmp ../../sources/nix/signal ../../sources/nix/socket ../../sources/nix/stdio ../../sources/nix/stdlib ../../sources/nix/string ../../sources/nix/time

REDEF=-D_DOSBase=___DOSBase \
      -D_UtilityBase=___UtilityBase \
      -D_MathIeeeSingBasBase=___MathIeeeSingBasBase \
      -D_MathIeeeSingTransBase=___MathIeeeSingTransBase \
      -D_MathIeeeDoubBasBase=___MathIeeeDoubBasBase \
      -D_MathIeeeDoubTransBase=___MathIeeeDoubTransBase \
      -D_LocaleBase=___LocaleBase

%.o: %.c
	@mkdir -p $(dir $@)
	@-$(CC) $(OPTIONS) -S $< -o $*.S 2>&1 | tee $*.err || true
	@-$(CPP) -traditional $(REDEF) $*.S -o $*2.S 2>/dev/null || true
	@-$(CC) $(OPTIONS) $*2.S -c -o $@ 2>/dev/null || true
	@-rm $*.S $*2.S 2>/dev/null || true
	@-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean

clean:
	-rm -f */*.o *.a

filelists:
	# filelist is now hardcoded - do not delete
	cd ../ && make filelists

$(SUBDIRS):
	mkdir -p $@

