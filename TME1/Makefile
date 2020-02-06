CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=maintab

all: $(EXEC)

run: all
	./$(EXEC)

maintab: maintab.o tab.o
	$(CC) -o $@ $^ $(LDFLAGS)

maintab.o: maintab.c tab.h
	$(CC) -c $<

tab.o: tab.c tab.h
	$(CC) -c $<

clean:
	rm -rf *.o $(EXEC)