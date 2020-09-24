.POSIX: #for better cross-platform compatability


.SUFFIXES:
#compiler macros
OBJS = main.o tst.o
CC = g++
STDV = std=c++14 #compile with c++14 standard
CFLAGS = -$(STDV) -g -Wall -fstack-protector -pipe -O2 -D_GLIBCXX_ASSERTIONS
FILENAME = tst

all: tst

tst: main.o tst.o
	$(CC) main.o tst.o -o $(FILENAME) $(CFLAGS)
main.o: main.cpp 
	$(CC) -c main.cpp $(CFLAGS)

tst.o: tst.cpp tst.h
	$(CC) $(CFLAGS) -c tst.cpp tst.h
#clean up system:

clean : 
	rm -f tst main.o tst.o *.gch

