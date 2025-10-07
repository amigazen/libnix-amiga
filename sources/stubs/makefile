SOURCEDIR=../../sources/stubs

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers $(CFLAGS)

vpath %.c $(SOURCEDIR)

OBJECTS2=$(OBJECTS)

SUBDIRS2=$(SUBDIRS)

%.o: %.c
	gcc $(OPTIONS) -c $^ -o $@ 2>&1 | tee $*.err
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
	-rm $@
	/bin/ar -q /t/$@ $(OBJECTS2)
	ranlib /t/$@
	echo "\$$$(V)" >>/t/$@
	cp /t/$@ .
	rm /t/$@
