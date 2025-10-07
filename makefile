# Build all models of the libnix libraries.
#
# CFLAGS=-Wall -O3 -DOS_20_ONLY
#
#   -fbaserel -DSMALL_DATA	for small data model
#   -mc68020			for 68020 specific code
#   -mc68881			for 68881 specific code
#   -DIXPATHS			for Un*x path option
#   -DDEBUG_LIB 		build a library for debugging (not yet fully working)
#   -DOS_20_ONLY		disable some 1.3 compatibilities (use always)

V=VER: libnix 3.1 (7.10.2025)

MAKE=make -f ../sources/makefile

SUBDIRS=startup lib libb lib020 libb020 lib881 libb881

all: $(SUBDIRS)
#all: libnix.guide $(SUBDIRS)
	cd sources;	make filelists
	cd startup;	make -f ../sources/startup/makefile V="$(V)"
	cd lib;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY"
	cd libb;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY -fbaserel -DSMALL_DATA"
	cd lib020;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY -mc68020"
	cd libb020;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY -fbaserel -DSMALL_DATA -mc68020"
	cd lib881;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY -mc68020 -m68881"
	cd libb881;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY -fbaserel -DSMALL_DATA -mc68020 -m68881"
#	cd libix;	$(MAKE) V="$(V)" CFLAGS="-Wall -O3 -DOS_20_ONLY -DIXPATHS"

$(SUBDIRS):
	mkdir -p $@

libamiga:
	@-mkdir lib lib/libb
	cd sources;	make filelists
	cd lib/lib;	$(MAKE) libamiga CFLAGS="-O3"
	cd lib/libb;	$(MAKE) libamiga CFLAGS="-O3 -fbaserel"

clean:
	-rm sources/*/filelist sources/stubs/libbases/* sources/stubs/libnames/*
	cd lib;	$(MAKE) clean
	cd libb;	$(MAKE) clean
	cd lib020;	$(MAKE) clean
	cd libb020;	$(MAKE) clean
	cd lib881;	$(MAKE) clean
	cd libb881;	$(MAKE) clean
#	cd libix;	$(MAKE) clean

veryclean:
	-rm sources/*/filelist
	cd lib;	$(MAKE) veryclean
	cd libb;	$(MAKE) veryclean
	cd lib020;	$(MAKE) veryclean
	cd libb020;	$(MAKE) veryclean
	cd lib881;	$(MAKE) veryclean
	cd libb881;	$(MAKE) veryclean
#	cd libix;	$(MAKE) veryclean

libnix.guide: libnix.texi
	makeinfo --amiga libnix.texi
	mv libnix.info libnix.guide

install:
	cp startup/*.o	./SDK/lib/libnix
	cp lib/*/lib*.a ./SDK/lib/libnix
	cp lib/misc/*.o ./SDK/lib/libnix
	cp libb/*/lib*.a ./SDK/lib/libb/libnix
	cp libb/misc/*.o ./SDK/lib/libb/libnix
	cp lib020/*/lib*.a ./SDK/lib/libm020/libnix
	cp lib020/misc/*.o ./SDK/lib/libm020/libnix
	cp libb020/*/lib*.a ./SDK/lib/libb/libm020/libnix
	cp libb020/misc/*.o ./SDK/lib/libb/libm020/libnix
	cp lib881/*/lib*.a ./SDK/lib/libm020/libm881/libnix
	cp lib881/misc/*.o ./SDK/lib/libm020/libm881/libnix
	cp libb881/*/lib*.a ./SDK/lib/libb/libm020/libm881/libnix
	cp libb881/misc/*.o ./SDK/lib/libb/libm020/libm881/libnix

distribution:
	mkdir T:gnu T:gnu/lib T:gnu/lib/libnix
	lha a -mraxez T:gnu/libnix-sources.lha makefile libnix.texi
	lha a -mraxez T:gnu/libnix-sources.lha sources examples
	mkdir T:gnu/lib/libm020 T:gnu/lib/libm020/libnix \
	      T:gnu/lib/libm020/libm881 T:gnu/lib/libm020/libm881/libnix \
	      T:gnu/lib/libb T:gnu/lib/libb/libnix \
	      T:gnu/lib/libb/libm020 T:gnu/lib/libb/libm020/libnix \
	      T:gnu/lib/libb/libm020/libm881 T:gnu/lib/libb/libm020/libm881/libnix
	cp -p startup/*.o T:gnu/lib/libnix
	cp -p lib/*/*.a T:gnu/lib/libnix
	cp -p lib/misc/*.o T:gnu/lib/libnix
	cp -p libb/*/*.a T:gnu/lib/libb/libnix
	cp -p libb/misc/*.o T:gnu/lib/libb/libnix
	cp -p lib020/*/*.a T:gnu/lib/libm020/libnix
	cp -p lib020/misc/*.o T:gnu/lib/libm020/libnix
	cp -p libb020/*/*.a T:gnu/lib/libb/libm020/libnix
	cp -p libb020/misc/*.o T:gnu/lib/libb/libm020/libnix
	cp -p lib881/*/*.a T:gnu/lib/libm020/libm881/libnix
	cp -p lib881/misc/*.o T:gnu/lib/libm020/libm881/libnix
	cp -p libb881/*/*.a T:gnu/lib/libb/libm020/libm881/libnix
	cp -p libb881/misc/*.o T:gnu/lib/libb/libm020/libm881/libnix
	-rm T:gnu/lib/libnix/libglue.a T:gnu/lib/libb/libnix/libglue.a
	-cp * T:gnu
	rm T:gnu/makefile T:gnu/libnix.texi
	cd /t;lha m -mraxeZ libnix.lha gnu
	rm -r T:gnu
