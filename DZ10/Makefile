all: sigdemo

sigdemo: sigdemo.o
	gcc -lm sigdemo.o -o sigdemo
sigdemo.o: sigdemo.c
	gcc -c sigdemo.c -o sigdemo.o


all: siglog

siglog: siglog.o
	gcc -lm siglog.o -o siglog
siglog.o: siglog.c
	gcc -c siglog.c -o siglog.o

all: swdemo

swdemo: swdemo.o
	gcc -lm swdemo.o -o swdemo
siglog.o: swdemo.c
	gcc -c swdemo.c -o swdemo.o
