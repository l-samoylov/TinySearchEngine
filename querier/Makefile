# Lab 6 Makefile for 'querier' module
# Lisa Samoylov; CS50 Spring 2025

QUERIER_OBJ = querier.o	
FUZZY_OBJ = fuzzquery.o

# COMMON_OBJS = ../common/index.o ../common/pagedir.o ../common/word.o
# COMMON_LIB = ../common/common.a

LIBS =	../common/common.a ../libcs50/libcs50-given.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=gnu11 -g -ggdb3	$(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make

# for memory-leak tests
VALGRIND = valgrind -s	--track-origins=yes --leak-check=full --show-leak-kinds=all

# # updating common.a at runtime
# $(COMMON_LIB): $(COMMON_OBJS)
# 	ar rcs $@ $^

# individual object files 
querier:	$(QUERIER_OBJ)
		$(CC)	$(CFLAGS)	$^ $(LIBS)	-o	$@
fuzzquery:	$(FUZZY_OBJ)
		$(CC)	$(CFLAGS)	$^	$(LIBS)	-o	$@

# .o files 
querier.o:	../libcs50/webpage.h	../common/pagedir.h	../common/index.h	../common/word.h	../libcs50/file.h	../libcs50/libcs50-given.a
fuzzquery.o:	../libcs50/mem.h	../libcs50/file.h	

../libcs50/hashtable.o: ../libcs50/hashtable.h
../common/index.o:	../common/index.h
../common/pagedir.o:	../common/pagedir.h	../libcs50/webpage.h
../common/word.o:	../common/word.h
../libcs50/bag.o:	../libcs50/bag.h
../libcs50/mem.o:	../libcs50/mem.h
../libcs50/file.o:	../libcs50/file.h

.PHONY: all test valgrind clean

all:	querier	fuzzquery

test:	testing.sh 
		bash -v ./testing.sh

valgrind:	testing.sh
					$(VALGRIND) ./testing.sh

clean:
				rm -rf *.dSYM  # MacOS debugger info
				rm -f *~ *.o
				rm -f querier
				rm -f fuzzquery
				rm -f core
				rm -f vgcore*
