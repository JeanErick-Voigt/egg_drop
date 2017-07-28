CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: egg egg_drop

egg: egg.c egg.h
	gcc $(CFLAGS) -c egg.c -o egg.o

egg_drop: egg.o egg_drop.c
	gcc $(CFLAGS) egg.o egg_drop.c -o egg_drop

debug: CFLAGS += -g
debug: all

clean:
	rm -f egg.o egg_drop
