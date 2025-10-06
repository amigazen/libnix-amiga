SOURCEDIR=../../sources/stubs

include $(SOURCEDIR)/filelist

OPTIONS=-I $(SOURCEDIR)/../headers $(CFLAGS)

vpath %.c $(SOURCEDIR)

OBJECTS2=$(OBJECTS) ../nix/misc/__request.o

SUBDIRS2=$(SUBDIRS) ../nix/misc

%.o: %.c
	gcc $(OPTIONS) -c $^ -o $@ 2>&1|tee $*.err
	-if test ! -s $*.err; then rm $*.err; fi

.PHONY: all clean veryclean

all: libstubs.a

clean:
	-rm -r $(SUBDIRS)

veryclean:
	-rm -r *

$(SUBDIRS2):
	mkdir $@

libstubs.a: $(SUBDIRS2) $(OBJECTS2) $(SOURCEDIR)/makefile $(SOURCEDIR)/filelist
	-rm $@
	ar -q /tmp/$@ $(OBJECTS2)
	ranlib /tmp/$@
	echo "\$$$(V)" >>/tmp/$@
	cp /tmp/$@ .
	rm /tmp/$@
