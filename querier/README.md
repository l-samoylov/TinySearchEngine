# Lisa Samoylov CS50 Spring 2025
# Querier README.md 
--- 

See IMPLEMENTATION.md for more information on how querier is implemented. 
See DESIGN.md for more information on the querier design. 

# FUNCTIONALITY: 
--- 
Querier meets the full specs. It implements all the functionality outlined in the rubric, specifically
* It prints the set of documents that contain all the words in the query in decreasing order 
* It supports `and` and `or` operators with `and` having precedence over `or`

# COMPILING : 
---
Run `make` to compile querier 
Run `make all` to compile querier, fuzzquery, and test 
Run `make clean` to remove all compiled files  

# MISC UPDATES:  
--- 
1. Added `index_validate` to `index` since Querier and Indexer both need to validate the indexFilename
2. Fixed linking errors in `common` (`pagedir.h` now includes `webpage.h` header) 

# ASSUMPTIONS: 
---
* pageDirectory has files named 1, 2, 3, ..., without gaps.
* The content of files in pageDirectory follow the format as defined in the specs; thus your code (to read the files) need not have extensive error checking.
* The content of the file named by indexFilename follows our index file format (as defined in Lab 5); thus your code (to recreate an index structure by reading a file) need not have extensive error checking.
* The provided index file corresponds to the provided pageDirectory, that is, was built by indexer from the files in that directory.

# TESTING: 
--- 
Run 'make test' to run a series of tests outlined in `testing.sh` for querier. 

As per the REQUIREMENTS.md specs, we ensure 
* exit(0) when EOF is reached on stdin
* exit(nonzero) w/ error to stderr on encountering an unrecoverable error such as
* *  out of memory
* * invalid command-line arguments
* * unable to read a file named pageDirectory/.crawler
* * unable to read a file named pageDirectory/1
* * unable to read a file named indexFilename

We also implement fuzz testing for querier in `testing.sh`. Run below to use fuz only. 

./fuzzquery ~/cs50-dev/shared/tse/output/indexer/index-letters-10 1000 5 | ./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-10 ~/cs50-dev/shared/tse/output/indexer/index-letters-10

# KNOWN BUGS: 
--- 
1. When inputting queries, `isValidQuery` misses inputs consisting of a single invalid character. 
E.g. `;`, `3`, and `%` aren't filtered by isValidQuery. However, getScores ignores single invalid characters when scoring the documents. 

# FILES: 
--- 
* `fuzzquery.c` : a copy of CS50's fuzzquery tester for querier
* `Makefile`
* `.gitignore`
* `testing.sh` 
* `testing.out` : out put from `testing.sh`
* `DESIGN.md` : design spec
* `IMPLEMENTATION.md` : implementation spec 


# NICE LINKS (SELF): 
--- 
CS50 Lab6 Querier Outline : https://github.com/CS50DartmouthSP25/home/tree/main/labs/tse/querier

CS50 TJP Lab6 Querier Outline (!!!) : https://www.cs.dartmouth.edu/~tjp/cs50/labs/lab6/REQUIREMENTS 

CS50 Querier REQUIREMENDS.md : https://github.com/CS50DartmouthSP25/home/blob/main/labs/tse/querier/REQUIREMENTS.md

CS50 Querier Arithmetic : https://github.com/CS50DartmouthSP25/home/blob/main/knowledge/units/querier-expressions.md

CS50 Fuzz Testing : https://github.com/CS50DartmouthSP25/home/blob/main/knowledge/units/querier-testing.md
