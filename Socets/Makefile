all: client

client: client.o
	gcc -lm client.o -o client
client.o: client.c
	gcc -c client.c -o client.o

all: server

server: server.o
	gcc -lm server.o -o server

server.o: server.c
	gcc -c server.c -o server.o