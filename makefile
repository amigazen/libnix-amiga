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
# Variants:
#   lib      - Standard library
#   libb     - Small data model (-fbaserel -DSMALL_DATA)
#   lib020   - 68020 specific (-mc68020)
#   libb020  - Small data + 68020 (-fbaserel -DSMALL_DATA -mc68020)
#   lib881   - 68020 + 68881 FPU (-mc68020 -m68881)
#   libb881  - Small data + 68020 + 68881 (-fbaserel -DSMALL_DATA -mc68020 -m68881)

V=VER: libnix 3.1 (7.10.2025)

MAKE=make -f ../sources/makefile

# Base CFLAGS for all variants
BASE_CFLAGS=-Wall -O3 -DOS_20_ONLY

# Ensure targets always run
.PHONY: all startup startup-baserel filelists lib libb lib020 libb020 lib881 libb881 clean veryclean

all: lib libb lib020 libb020 lib881 libb881

# Build startup files for normal (large data) model
startup:
	mkdir -p startup
	cd sources;	make filelists
	cd startup;	make -f ../sources/startup/makefile V="$(V)"

# Build startup files for small data model
startup-baserel:
	mkdir -p startup-baserel
	cd sources;	make filelists
	cd startup-baserel;	make -f ../sources/startup/makefile V="$(V)" CFLAGS="-fbaserel -DSMALL_DATA"

# Standard library variant (uses normal startup)
lib: startup sources/makefile
	mkdir -p lib
	cd sources;	make filelists
	mkdir -p lib/nix
	cp sources/nix/filelist lib/nix/filelist
	cd lib;	$(MAKE) V="$(V)" CFLAGS="$(BASE_CFLAGS)"

# Small data model variant (uses baserel startup)
libb: startup-baserel sources/makefile
	mkdir -p libb
	cd sources;	make filelists
	mkdir -p libb/nix
	cp sources/nix/filelist libb/nix/filelist
	cd libb;	$(MAKE) V="$(V)" CFLAGS="$(BASE_CFLAGS) -fbaserel -DSMALL_DATA"

# 68020 specific variant (uses normal startup)
lib020: startup sources/makefile
	mkdir -p lib020
	cd sources;	make filelists
	mkdir -p lib020/nix
	cp sources/nix/filelist lib020/nix/filelist
	cd lib020;	$(MAKE) V="$(V)" CFLAGS="$(BASE_CFLAGS) -mc68020"

# Small data + 68020 variant (uses baserel startup)
libb020: startup-baserel sources/makefile
	mkdir -p libb020
	cd sources;	make filelists
	mkdir -p libb020/nix
	cp sources/nix/filelist libb020/nix/filelist
	cd libb020;	$(MAKE) V="$(V)" CFLAGS="$(BASE_CFLAGS) -fbaserel -DSMALL_DATA -mc68020"

# 68020 + 68881 FPU variant (uses normal startup)
lib881: startup sources/makefile
	mkdir -p lib881
	cd sources;	make filelists
	mkdir -p lib881/nix
	cp sources/nix/filelist lib881/nix/filelist
	cd lib881;	$(MAKE) V="$(V)" CFLAGS="$(BASE_CFLAGS) -mc68020 -m68881"

# Small data + 68020 + 68881 variant (uses baserel startup)
libb881: startup-baserel sources/makefile
	mkdir -p libb881
	cd sources;	make filelists
	mkdir -p libb881/nix
	cp sources/nix/filelist libb881/nix/filelist
	cd libb881;	$(MAKE) V="$(V)" CFLAGS="$(BASE_CFLAGS) -fbaserel -DSMALL_DATA -mc68020 -m68881"


clean:
	cd lib;	$(MAKE) clean
	cd libb;	$(MAKE) clean
	cd lib020;	$(MAKE) clean
	cd libb020;	$(MAKE) clean
	cd lib881;	$(MAKE) clean
	cd libb881;	$(MAKE) clean
	cd startup;	$(MAKE) -f ../sources/startup/makefile clean
	cd startup-baserel;	$(MAKE) -f ../sources/startup/makefile clean

veryclean:
	cd lib;	$(MAKE) veryclean
	cd libb;	$(MAKE) veryclean
	cd lib020;	$(MAKE) veryclean
	cd libb020;	$(MAKE) veryclean
	cd lib881;	$(MAKE) veryclean
	cd libb881;	$(MAKE) veryclean
	cd startup;	$(MAKE) -f ../sources/startup/makefile veryclean
	cd startup-baserel;	$(MAKE) -f ../sources/startup/makefile veryclean

filelist:
	echo "#Computer generated partial makefile-do not edit" >filelist
	echo "OBJECTS= \\" >>filelist
	( for file in $(SOURCEFILES); do echo $$file; done ) | \
	gawk '{ print substr($$0,1,length($$0)-2) ".o \\" }' >>filelist
	echo >>filelist
	echo "SUBDIRS= \\" >>filelist
	ls -d -F *|gawk '/\// { print substr($$0,1,length($$0)-1) " \\" }' >>filelist

libnix.guide: libnix.texi
	makeinfo --amiga libnix.texi
	mv libnix.info libnix.guide

install:
	# Create target directories
	mkdir -p ./SDK/gg/lib/libnix
	mkdir -p ./SDK/gg/lib/libb/libnix
	mkdir -p ./SDK/gg/lib/libm020/libnix
	mkdir -p ./SDK/gg/lib/libb/libm020/libnix
	mkdir -p ./SDK/gg/lib/libm020/libm881/libnix
	mkdir -p ./SDK/gg/lib/libb/libm020/libm881/libnix
	
	# Copy startup files to libnix directory
	cp startup/*.o ./SDK/gg/lib/libnix/
	
	# Copy standard library files
	cp lib/*/lib*.a ./SDK/gg/lib/libnix/
	cp lib/misc/*.o ./SDK/gg/lib/libnix/
	
	# Copy small data model library files
	cp libb/*/lib*.a ./SDK/gg/lib/libb/libnix/
	cp libb/misc/*.o ./SDK/gg/lib/libb/libnix/
	
	# Copy 68020 specific library files
	cp lib020/*/lib*.a ./SDK/gg/lib/libm020/libnix/
	cp lib020/misc/*.o ./SDK/gg/lib/libm020/libnix/
	
	# Copy small data + 68020 library files
	cp libb020/*/lib*.a ./SDK/gg/lib/libb/libm020/libnix/
	cp libb020/misc/*.o ./SDK/gg/lib/libb/libm020/libnix/
	
	# Copy 68020 + 68881 FPU library files
	cp lib881/*/lib*.a ./SDK/gg/lib/libm020/libm881/libnix/
	cp lib881/misc/*.o ./SDK/gg/lib/libm020/libm881/libnix/
	
	# Copy small data + 68020 + 68881 library files
	cp libb881/*/lib*.a ./SDK/gg/lib/libb/libm020/libm881/libnix/
	cp libb881/misc/*.o ./SDK/gg/lib/libb/libm020/libm881/libnix/
	
	# Copy guide and info files
	cp guide/libnix.guide ./SDK/Help/
	
	# Note: libnix13.a files are not currently built by the main makefile
	# If nix13 libraries are needed, they should be built separately and
	# the install target should be updated to include them

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
