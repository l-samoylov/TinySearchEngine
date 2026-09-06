#!/bin/bash

# Lisa Samoylov
# `testing.sh` file for `crawler.c` and `pagedir.c`
# Lab4 05/05/25
# For the sake of space, only one valgrind is outputted (see letters-2)

# SET UP
# TEST 1: wrong number of arguments
echo "TEST: number of cmd args"
echo "==================="

echo "3 ARGS"
./crawler notAURL notADIR

echo "-------"

echo "5 ARGS"
./crawler notAURL notADIR notANUM notIDK

# TEST2: proper cmd line args
echo 
echo "TEST 1: valid cmd line args" 
echo "==================="
echo "maxDepth NOT AN INT"
echo "--------"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data hf38r

echo
echo "maxDepth OUT OF RANGE"
echo "--------"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data -1
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data 11

echo
echo "seedURL NOT A URL"
echo "--------"
./crawler hthahahaah.cs.dartmouth.edu/tse/letters/ ../data/letters 0 
echo
echo "seedURL EXTERNAL"
echo "--------"
./crawler https://en.wikipedia.org/wiki/Algorithm ../data/letters 0

echo
echo "pageDirectory NOT INIT"
echo "--------"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../letters_data 0


# TEST3: crawler testing 
echo
echo "TEST 2.000: letters 0"
echo "======================"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-0 0


# echo
# echo "VALGRIND letters 0"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-0 0

echo
echo "TEST 2.001: letters 1"
echo "======================"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-1 1


# echo
# echo "VALGRIND letters 1"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-1 1

echo
echo "TEST 2.002: letters 2"
echo "======================"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-2 2


echo
echo "VALGRIND letters 2"
echo "--------------------"
valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-2 2


echo
echo "TEST 2.003: letters 3"
echo "======================"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-3 3


# echo
# echo "VALGRIND letters 3"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-3 3

echo
echo "TEST 2.010: letters 10"
echo "======================"
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-10 10 

# echo
# echo "VALGRIND letters 10"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../data/letters-10 10 

echo
echo "TEST 3.000: toscrape 0"
echo "======================" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape-0 0

# echo
# echo "VALGRIND toscrape 0"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../toscrape-0 0

echo 
echo "TEST 3.001: toscrape 1"
echo "======================" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape-1 1

# echo 
# echo "VALGRIND toscrape 1"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape-1 1

echo 
echo "TEST 3.002: toscrape 2"
echo "======================" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape-2 2

# echo 
# echo "VALGRIND toscrape 2"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../data/toscrape-2 2


echo
echo "TEST 4.000: wiki 0"
echo "==================" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wiki-0 0

# echo 
# echo "VALGRIND wiki 0"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wiki-0 0

echo
echo "TEST 4.001: wiki 1"
echo "==================" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wiki-1 1

# echo 
# echo "VALGRIND wiki 1"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wiki-1 1

echo
echo "TEST 4.002: wiki 2"
echo "==================" 
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wiki-2 2

# echo 
# echo "VALGRIND wiki 2"
# echo "--------------------
# valgrind ./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../data/wiki-2 2




