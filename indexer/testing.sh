#!/bin/bash

# Lisa Samoylov CS50 Spring 2025
# testing.sh - testing both indexer and indextest

echo "Setting up testing environment..."

# Make a directory to store outputs
mkdir testing

# Make a read-only directory
mkdir readonly-dir
chmod -w readonly-dir

# Make a read-only file
touch readonly-file
chmod -w readonly-file

echo ""
echo "Testing indexer with bad arguments..."

echo "Test 1: No arguments"
./indexer

echo "Test 2: Only one argument"
./indexer ../data/letters-0

echo "Test 3: Too many arguments"
./indexer ../data/letters-0 testing/index extra

echo "Test 4: Nonexistent page directory"
./indexer not-real-dir testing/index

echo "Test 5: Not a crawler-produced directory"
./indexer . testing/index

echo "Test 6: Index file in nonexistent directory"
./indexer ../data/letters-0 no-such-dir/index

echo "Test 7: Index file in read-only directory"
./indexer ../data/letters-0 readonly-dir/index

echo "Test 8: Index file is a read-only file"
./indexer ../data/letters-0 readonly-file

echo ""
echo "Running indexer and indextest on valid directories..."

echo "Testing with ../data/letters-0"
./indexer ../data/letters-0 testing/index-letters-0
./indextest testing/index-letters-0 testing/rebuild-letters-0

echo "Testing with ../data/letters-1"
./indexer ../data/letters-1 testing/index-letters-1
./indextest testing/index-letters-1 testing/rebuild-letters-1

echo "Testing with ../data/letters-10"
./indexer ../data/letters-10 testing/index-letters-10
./indextest testing/index-letters-10 testing/rebuild-letters-10

echo ""
echo "Checking memory with valgrind (indexer)..."

valgrind --leak-check=full ./indexer ../data/letters-0 testing/valgrind-index-letters-0
valgrind --leak-check=full ./indexer ../data/letters-1 testing/valgrind-index-letters-1
valgrind --leak-check=full ./indexer ../data/letters-10 testing/valgrind-index-letters-10

echo ""
echo "Checking memory with valgrind (indextest)..."

valgrind --leak-check=full ./indextest testing/valgrind-index-letters-0 testing/rebuild-valgrind-letters-0
valgrind --leak-check=full ./indextest testing/valgrind-index-letters-1 testing/rebuild-valgrind-letters-1
valgrind --leak-check=full ./indextest testing/valgrind-index-letters-10 testing/rebuild-valgrind-letters-10

echo ""
echo "Cleaning up..."

chmod +w readonly-dir
chmod +w readonly-file

rm -rf testing
rm -rf readonly-dir
rm -f readonly-file

echo "All done!"