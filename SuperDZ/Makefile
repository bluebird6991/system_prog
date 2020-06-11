all: temp

temp: temp.o
	gcc -lm temp.o -o temp
temp.o: temp.c
	gcc -c temp.c -o temp.o