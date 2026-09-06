#!/bin/bash

# Lisa Samoylov CS50 Spring 2025
# querier - testing.sh file
# is there a way to make this shorter

# Testing Querier Inputs  
echo "TEST CMD LINE ARGS" 
echo "-------------"
echo "TEST 001: no arguments" 
./querier 

echo 
echo "TEST 002: one argument" 
./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1

echo 
echo "TEST 003: three arguments" 
./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 ~/cs50-dev/shared/tse/output/indexer/index-letters-1 fooArg

echo
echo "Test 011: invalid pagedirectory" 
./querier somePageDirectory ~/cs50-dev/shared/tse/output/indexer/index-letters-1

echo
echo "Test 012: invalid indexFilename" 
./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-1 someIndexFilename

# Testing query syntax 
echo 
echo "TEST QUERY SYNTAX" 
echo "-------------"
echo "MAKING TEST FILE" 
touch test.txt

# test : skipping two-letter word
echo "eh Hello" >> test.txt

# test : skipping one-letter word 
echo "a Hello" >> test.txt

# ERROR : this is a known indexer failure 
echo ";" >> test.txt 

# test : skipping two char bad symbols 
echo ";;" >> test.txt 

# test : start and 
echo "and blue" >> test.txt 

# test : start or 
echo "or blue" >> test.txt

# test : double adjacent and 
echo "blue and and red" >> test.txt

# test : double adjacent or
echo "red or or red" >> test.txt

# test: adjacent and or
echo "green and or red" >> test.txt

# test adjacent or and 
echo "green or and red" >> test.txt

# running valgrind on it
echo 
echo "VALGRIND test.txt" 
valgrind ./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-10 ~/cs50-dev/shared/tse/output/indexer/index-letters-10 < test.txt

# Memory Leak Testing 
echo 
echo "TEST VALGRIND" 
echo "-------------"
echo "VALGRIND: fuzzquery.c + checking for leaks" 
valgrind ./fuzzquery ~/cs50-dev/shared/tse/output/indexer/index-letters-10 20 5 | ./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-10 ~/cs50-dev/shared/tse/output/indexer/index-letters-10

# Clean up 
echo 
echo "Removing created files" 
rm -f test.txt
echo "All done!" 

# CS39 Tian Xia Guest Lecture 
# --------------------
# Q1 : 
# for quantum computers, apparently the qubits are super sensitive. 
# They're so sensitive to their external envioronment that 
# you have to recalibrate all the qubits after restarting the computer. 
# But if your qubits are so sensitive
# what if someone else tries to view your qubits while you're using them? to mess with you...
# How do people handle that if its an issue? 
