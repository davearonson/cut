CC=gcc
CFLAGS=-Wall -Werror -I. -g

all: .testflag example

cut.o: cut.c cut.h cut_PRIVATE.h

cut_test: cut_test.o cut.o

cut_test.o: cut_test.c cut.h cut_PRIVATE.h

.testflag: cut_test
	./cut_test
	touch .testflag

example: example.o cut.o

example.o: example.c cut.h cut_PRIVATE.h

clean:
	rm -f cut_test example .testflag *.o
