# Built one model of the libnix libraries - use
# make CFLAGS="what you like" to built them.
#
# Combine
#
# CFLAGS=-Wall -O3 -DOS_20_ONLY
#
#   -fbaserel -DSMALL_DATA	for small data model
#   -mc68020			for 68020 specific code
#   -mc68881			for 68881 specific code
#   -DIXPATHS			for Un*x path option
#   -DDEBUG_LIB 		build a library for debugging (not recommended)
#   -DOS_20_ONLY		disable some 1.3 compatibilities (use always)

SOURCEDIR=../sources

MAKELIST=make -f ../makefile filelist

SUBDIRS=nixmain nix_main misc nix math stack stubs

all: $(SUBDIRS)
	for subdir in $(SUBDIRS); do \
	( cd $$subdir;make -f ../$(SOURCEDIR)/$$subdir/makefile V="$(V)" \
	  CFLAGS="$(CFLAGS)" ); \
	done

$(SUBDIRS):
	mkdir $@

libamiga:
	@-mkdir amiga
	cd amiga;make -f ../$(SOURCEDIR)/amiga/makefile CFLAGS="$(CFLAGS)"

filelists:
	-cd math;	$(MAKELIST) SOURCEFILES="*/*"
	-cd stack;	$(MAKELIST) SOURCEFILES="*.c"
	-cd nix;	$(MAKELIST) SOURCEFILES="*/*"
	-cd stubs;	make -f ../makefile libbases/dos.c; \
		$(MAKELIST) SOURCEFILES=" \
		libbases/* misc/__DOSBase.c misc/__UtilityBase.c \
		misc/__MathIeeeSingBasBase.c misc/__MathIeeeDoubBasBase.c \
		misc/__MathIeeeSingTransBase.c misc/__MathIeeeDoubTransBase.c \
		misc/__initlibraries.c misc/__cpucheck.c libnames/* stubs/*"
	-cd amiga;	$(MAKELIST) SOURCEFILES="*/*"

filelist:
	echo "#Computer generated partial makefile-do not edit" >filelist
	echo "OBJECTS= \\" >>filelist
	( for file in $(SOURCEFILES); do echo $$file; done ) | \
	gawk '{ print substr($$0,1,length($$0)-2) ".o \\" }' >>filelist
	echo >>filelist
	echo "SUBDIRS= \\" >>filelist
	ls -d -F *|gawk '/\// { print substr($$0,1,length($$0)-1) " \\" }' >>filelist

# build stubs for library base pointers
libbases/dos.c: ../makefile library.list
	-rm libbases/* libnames/*
	gawk <library.list '{ sname=substr($$2,1,length($$2)-8);        \
	  fname="libbases/" sname ".c";                                 \
	  print "/* Machine-generated C-file- do not edit ! */" >fname; \
	  print "#include <stabs.h>"                            >fname; \
	  print "extern char __" sname "name[];"                >fname; \
	  print "void *" $$1 "[2]={ 0l,__" sname "name };"      >fname; \
	  print "ADD2LIB(" $$1 ");"                             >fname; \
	  fname="libnames/" sname ".c";                                 \
	  print "/* Machine-generated C-file- do not edit ! */" >fname; \
	  print "char __" sname "name[]=\"" $$2 "\";"           >fname;}'

clean:
	cd nixmain;	make clean
	cd nix_main;	make clean
	cd misc;	make clean
	cd math;	make clean
	cd stack;	make clean
	cd nix; 	make clean
	cd stubs;	make clean

veryclean:
	-rm -r *
