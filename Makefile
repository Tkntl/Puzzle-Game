CC=gcc
CFLAGS=-I.
DEPS=randomi.h libgame.h
OBJ=randomi.o libgame.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

puzzle: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
