# Some examples

.PHONY: all

all: lib libr dev helloworld

# normal library
lib: libinit.o simplelib.c
	gcc -nostdlib -O3 -fbaserel $^ -o $@

# multibase library
libr: libinitr.o simplelib.c
	gcc -nostdlib -O3 -resident $^ -o $@

# device
dev: devinit.o simpledev.c
	gcc -nostdlib -O3 -fbaserel $^ -o $@

# helloworld
helloworld: nbcrt0.o helloworld.c libstubs.a
	gcc -nostdlib -O3 -s -fbaserel $^ -o $@
