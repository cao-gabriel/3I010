CC=gcc

all: loopsys loopcpu mytimes

loopsys: loopsys.o
	$(CC) -o $@ $^

loopsys.o: loopsys.c
	$(CC) -c $<

loopcpu: loopcpu.o
	$(CC) -o $@ $^

loopcpu.o: loopcpu.c
	$(CC) -c $<

mytimes: lancer.o
	$(CC) -o $@ $^

lancer.o: lancer.c
	$(CC) -c $<
	
clean:
	rm -rf mytimes loopcpu loopsys *.o