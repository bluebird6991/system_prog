all: test

test: test.o
	gcc -lm test.o -o test
test.o: test.c
	gcc -c test.c -o test.o
