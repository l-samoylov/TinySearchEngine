# Makefile for 'crawler' module
# Inspired by Lab3 Makefile 
#
# Lisa Samoylov; CS50 Spring 2025

INDEXER_OBJ = indexer.o
INDEXTEST_OBJ = indextest.o

COMMON_OBJS = ../common/index.o ../common/pagedir.o ../common/word.o
COMMON_LIB = ../common/common.a

LIBS =	../common/common.a ../libcs50/libcs50-given.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=gnu11 -g -ggdb	$(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind -s	--track-origins=yes --leak-check=full --show-leak-kinds=all

# updating common.a at runtime
$(COMMON_LIB): $(COMMON_OBJS)
	ar rcs $@ $^

# individual object files 
indexer:	$(INDEXER_OBJ)
		$(CC)	$(CFLAGS)	$^ $(LIBS)	-o	$@

indextest:	$(INDEXTEST_OBJ)
		$(CC)	$(CFLAGS)	$^ $(LIBS)	-o	$@

# .o files 
indexer.o:	../libcs50/webpage.h	../common/pagedir.h	../common/index.h	../common/word.h
indextest.o: ../common/index.h

../libcs50/hashtable.o: ../libcs50/hashtable.h
../common/index.o:	../common/index.h
../common/pagedir.o:	../common/pagedir.h
../common/word.o:	../common/word.h
../libcs50/bag.o:	../libcs50/bag.h
../libcs50/mem.o:	../libcs50/mem.h
../libcs50/file.o:	../libcs50/file.h
../libcs50/counters.o: ../libcs50/counters.h

.PHONY: all test valgrind clean

all:	indexer	indextest

test:	testing.sh 
		bash -v ./testing.sh

valgrind:	testing.sh
					$(VALGRIND) ./testing.sh

clean:
				rm -rf *.dSYM  # MacOS debugger info
				rm -f *~ *.o
				rm -f indexer
				rm -f indextest
				rm -f core
				rm -f vgcore*
