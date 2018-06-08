CC=gcc
CFLAGS=-Wall

all: snake

main.o: main.h engine.h graphics.h engine.o graphics.o
	$(CC) $(CFLAGS) -c main.c
engine.o: engine.h graphics.h main.h engine.o
	$(CC) $(CFLAGS) -c engine.c
graphics.o: engine.h graphics.h main.h engine.o
	$(CC) $(CFLAGS) -c graphics.c
snake: main.o engine.o graphics.o
	$(CC) $(CFLAGS) main.o engine.o graphics.o -lSDL2 -o snake

clean:
    rm -f *.o
    rm -f snake