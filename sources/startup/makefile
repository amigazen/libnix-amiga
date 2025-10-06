# make startup-files
# 13-Apr-94 G. Nikl
# 14-Apr-94 M. Fleischer clean+veryclean added

VPATH=../sources/startup

OPTIONS=-I ../sources/headers -O -fomit-frame-pointer

%.o: %.c
	gcc $(OPTIONS) -c $^ 2>&1|tee $*.err
	-if test ! -s $*.err; then rm $*.err; fi
	echo "\$$$(V)" >>$@

.PHONY: all filelist subdirs clean veryclean

all: nrcrt0.o nbcrt0.o ncrt0.o libinit.o libinitr.o devinit.o

subdirs:

filelist:

clean:

veryclean:
	-rm *.o

# baserelative resident startup-code

nrcrt0.o: nrcrt0.S
	gcc -c $^
	echo "\$$$(V)" >>$@

# baserelative startup code

nbcrt0.o: nbcrt0.S
	gcc -c $^
	echo "\$$$(V)" >>$@

# normal (=large) startup code

ncrt0.o: ncrt0.S
	gcc -c $^
	echo "\$$$(V)" >>$@
