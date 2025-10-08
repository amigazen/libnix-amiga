SOURCEDIR=../../sources/stubs

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers -I/netinclude/ $(CFLAGS)

REDEF=-D_DOSBase=___DOSBase \
      -D_UtilityBase=___UtilityBase \
      -D_MathIeeeSingBasBase=___MathIeeeSingBasBase \
      -D_MathIeeeSingTransBase=___MathIeeeSingTransBase \
      -D_MathIeeeDoubBasBase=___MathIeeeDoubBasBase \
      -D_MathIeeeDoubTransBase=___MathIeeeDoubTransBase \
      -D_LocaleBase=___LocaleBase

vpath %.c $(SOURCEDIR) $(SOURCEDIR)/misc $(SOURCEDIR)/libbases $(SOURCEDIR)/libnames $(SOURCEDIR)/stubs

OBJECTS2=$(OBJECTS)

SUBDIRS2=$(SUBDIRS)

%.o: %.c
	@mkdir -p $(dir $@)
	m68k-amigaos-gcc $(OPTIONS) -S $< -o $*.S 2>&1 | tee $*.err
	m68k-amigaos-gcc -E -traditional $(REDEF) $*.S -o $*2.S
	m68k-amigaos-gcc $(OPTIONS) $*2.S -c -o $@
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean

all: libstubs.a

clean:
	-rm -r $(SUBDIRS)

veryclean:
	-rm -f *.o *.a *.err

$(SUBDIRS2):
	mkdir -p $@

libstubs.a: $(SUBDIRS2) $(OBJECTS2) $(SOURCEDIR)/makefile $(SOURCEDIR)/filelist
	/bin/ar -r /t/$@ $(OBJECTS2)
	ranlib /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@
