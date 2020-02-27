all: shell1.0 shell2.0 shell3.0

shell1.0: shell1.0.o
	gcc -o $@ $^

shell2.0: shell2.0.o
	gcc -o $@ $^

shell3.0: shell3.0.o
	gcc -o $@ $^

shell1.0.o: shell1.0.c
	gcc -c $^

shell2.0.o: shell2.0.c
	gcc -c $^

shell3.0.o: shell3.0.c
	gcc -c $^

clean:
	rm -rf *.o shell1.0 shell2.0 shell3.0
