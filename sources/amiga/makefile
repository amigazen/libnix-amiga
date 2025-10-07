SOURCEDIR=../../sources/amiga

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers $(CFLAGS)

vpath %.c $(SOURCEDIR)
vpath %.S $(SOURCEDIR)

SOURCEFILES=*/*

%.o: %.c
	gcc $(OPTIONS) -c $^ -o $@ 2>&1 | tee $*.err
	-if test ! -s $*.err; then rm $*.err; fi

%.o: %.S
	gcc $(OPTIONS) -c $^ -o $@ 2>&1 | tee $*.err
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean splitinline

all: libamiga.a

clean:
	-rm -r $(SUBDIRS)

veryclean:
	-rm -r *

$(SUBDIRS):
	mkdir $@

libamiga.a: $(SUBDIRS) $(OBJECTS) libglue.a $(SOURCEDIR)/makefile $(SOURCEDIR)/filelist
	-rm libamiga.a
	-cp libglue.a libamiga.a
	/bin/ar -q libamiga.a $(OBJECTS)
	ranlib libamiga.a

libglue.a:
	-mkdir tmp
# Build assembler stubs out of inline headers:
# * First transform all vararg #defines into real functions
# * Compile all functions with 'extern' and '__inline' disabled
# * Split resulting assembler output at function entries
	-cd tmp; \
	echo "" >dummy.c; \
	for file in /gnu/os-include/inline/*.h; do \
	( gawk 'nf==1 { fn=$$1;nf=0 } \
	        /inline/ { vs="long";rs="return ";nf=1 } \
	        /void/ { vs="void";rs="";nf=1 } \
	        /\.\.\./ \
	        { st=substr($$0,1,index($$0,"tags...")-1); \
	          st=substr(st,index(st," ")); \
	          st2=st;gsub(/\(/,"(long ",st2);gsub(/,/,",long ",st2); \
	          print "#undef" substr(st,1,index(st,"(")-1) "\n" vs st2 "tags,...)"; \
	          print "{ " rs fn substr(st,index(st,"(")) "&tags); }\n" \
	        }' $$file >vararg.c; \
	  ( gcc $(CFLAGS) -w -include $$file vararg.c -S -o -; \
	    gcc -Dextern= -D__inline= -D_STRSUP_H -include $$file $(CFLAGS) dummy.c -S -o - ) | \
	  gawk '/.even/ { next } /.comm/ { next } \
	        /.globl/ { if(file!="") close(file); file=$$2 ".s"; \
	                   print "\t.even\n" $$0 >file; next; } \
	        { if(file!="") print $$0 >file; }' ); done
	-cd tmp;rm vararg.c dummy.c;gcc -c *.s
	-rm libglue.a
	-cd tmp;/bin/ar -q ../libglue.a *.o
	-rm -r tmp
