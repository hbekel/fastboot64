KASM?=java -jar /usr/share/kickassembler/KickAss.jar
CC?=gcc
CFLAGS=-Wall -O2 -std=c99 -static-libgcc

PREFIX?=/usr/local
DESTDIR?=

all: fastboot64

fastboot64: fastboot64.c patch.h
	$(CC) $(CFLAGS) -o fastboot64 fastboot64.c

patch.h: tools/make-code patch.asm
	$(KASM) -binfile patch.asm
	tools/make-code patch.bin > patch.h

tools/make-code: tools/make-code.c
	$(CC) $(CFLAGS) -o tools/make-code tools/make-code.c

clean:
	rm -rf fastboot64{,.exe} patch.{h,bin}
	rm -rf tools/make-code{,.exe} *.stackdump

install: all
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m755 fastboot64 $(DESTDIR)$(PREFIX)/bin

