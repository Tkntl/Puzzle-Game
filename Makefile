CC=gcc
CFLAGS=-I.
DEPS=randomi.h libgame.h searchAgent.h
OBJ=randomi.o libgame.o searchAgent.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

puzzle: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
