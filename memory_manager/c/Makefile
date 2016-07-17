#CFLAGS=-g
CFLAGS=-O2

all: base list map

test.c: test.h

base: base.c test.c

list: list.c test.c

map: map.c test.c

clean:
	rm -rf *.o base list map

