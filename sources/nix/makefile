SOURCEDIR=../../sources/nix

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers $(CFLAGS)

vpath %.c $(SOURCEDIR)

SOURCEFILES=*/*

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

all: libnix.a

clean:
	-rm -r $(SUBDIRS)

veryclean:
	-rm -r *

$(SUBDIRS):
	mkdir $@

libnix.a: $(SUBDIRS) $(OBJECTS) $(SOURCEDIR)/makefile $(SOURCEDIR)/filelist
	-rm $@
	ar -q /tmp/$@ $(OBJECTS)
	ranlib /tmp/$@
	echo "\$$$(V)" >>/tmp/$@
	cp /tmp/$@ .
	rm /tmp/$@
