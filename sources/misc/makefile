SOURCEDIR=../../sources/misc

OBJECTS=detach.o swapstack.o

OPTIONS=-I $(SOURCEDIR)/../headers $(CFLAGS)

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
	gcc $(OPTIONS) -S $^ -o $*.S 2>&1|tee $*.err
	gcc -E -traditional $(REDEF) $*.S -o $*2.S
	gcc $(OPTIONS) $*2.S -c -o $*.o
	-rm $*.S $*2.S
	-if test ! -s $*.err; then rm $*.err; fi
	echo "\$$$(V)" >>$*.o

.PHONY: all filelist subdirs clean veryclean

all: $(OBJECTS)

filelist:

subdirs:

clean:
	-rm *.o *.err

veryclean: clean
