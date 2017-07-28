CFLAGS=-Wall -Wextra -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

all: egg egg_drop

egg: egg.c egg.h
	gcc $(CFLAGS) -c egg.c -o egg.o

egg_drop: egg.o egg_drop.c
	gcc $(CFLAGS) egg.o egg_drop.c -o egg_drop -lm

debug: CFLAGS += -g
debug: all

profile: CFLAGS += -pg
profile: all

test: all
	curl https://raw.githubusercontent.com/tclasen/egg_drop/master/test.sh -o test.sh && chmod 755 test.sh && ./test.sh
clean:
	rm -f egg.o egg_drop
