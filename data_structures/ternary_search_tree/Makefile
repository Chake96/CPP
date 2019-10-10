.POSIX: #for better cross-platform compatability


.SUFFIXES:
#compiler macros
OBJS = main.o tst.o
CC = g++
STDV = std=c++14 #compile with c++14 standard
CFLAGS = -$(STDV) -g -Wall -fstack-protector -pipe -O2 -D_GLIBCXX_ASSERTIONS

all: tst
tst: main.o tst.o
	$(CC) -o tst main.o tst.o 

main.o: main.cpp tst.o
	$(CC) -c main.cpp $(CFLAGS)

tst.o: tst.cpp tst.h
	$(CC) -o tst.cpp tst.h
#clean up system
clean : 
	rm -f tst main.o tst.o *.gch

