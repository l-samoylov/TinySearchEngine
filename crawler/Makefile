# Makefile for 'crawler' module
# Inspired by Lab3 Makefile 
#
# Lisa Samoylov; CS50 Spring 2025

OBJS = crawler.o	
LIBS =	../libcs50/libcs50-given.a	../common/common.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=gnu11 -g -ggdb	-DAPPTEST	$(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind -s --leak-check=full --show-leak-kinds=all

crawler:	$(OBJS)
		$(CC)	$(CFLAGS)	$^ $(LIBS)	-o	$@


crawler.o:	../libcs50/webpage.h	../libcs50/hashtable.h	../libcs50/bag.h	../libcs50/mem.h	../libcs50/counters.h ../common/pagedir.h

../libcs50/hashtable.o: ../libcs50/hashtable.h
../libcs50/bag.o:	../libcs50/bag.h
../libcs50/mem.o:	../libcs50/mem.h
../libcs50/file.o:	../libcs50/file.h
../libcs50/counters.o: ../libcs50/counters.h

	


.PHONY: test valgrind clean


test:	testing.sh 
		bash -v ./testing.sh

valgrind:	testing.sh
					$(VALGRIND) ./testing.sh

clean:
				rm -rf *.dSYM  # MacOS debugger info
				rm -f *~ *.o
				rm -f crawler
				rm -f core
				rm -f vgcore*
