CC=gcc
CFLAGS=-Wall

all: snake

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
engine.o: engine.c
	$(CC) $(CFLAGS) -c engine.c
graphics.o: graphics.c
	$(CC) $(CFLAGS) -c graphics.c
snake: main.o engine.o graphics.o
	$(CC) $(CFLAGS) main.o engine.o graphics.o -lSDL2 -lSDL2main -o snake

clean:
    rm -f *.o
    rm -f snake