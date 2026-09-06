# Lisa Samoylov CS50 Spring 2025 05/13/25
# Lab5 `/indexer/` ReadMe File

# INDEXER
`indexer.c` implements the `indexer` function as specified in the given Design Specs 

## ASSUMPTIONS 
If the indexFilename given to `indexer` doesn't exist, `indexer` WON'T create the file, but throws an error. 

## DEVIATIONS 
`indexPage` according to Design Specs is supposed to take inputs `webpage_t* page, int docID`.  
We modify `indexPage` so that it takes inputs `webpage_t* page, index_t* index` because docID is stored in the `webapge_t*` struct and `indexPage` requires access to `index_t* index`. 

## RUNNING 
* Run `make indexer` to make ONLY the indexer * executable
* Run `./indexer pageDirectory indexFilename` 

## ERROR CODES
* 0 : Success
* 10 : indexer : main : wrong number of args (takes 3) 
* 11 : indexer : pageDirectory is invalid (doesn't exist, can't read ./crawler)
* 12 : indexer : invalid indexFilename
* 100: indexer : can't close indexFilename

# INDEXTEST 
`indextest.c` tests the `index_load()` and `index_print()` functions in `indexer.c` 

## RUNNING 
* Run `make indextest` to make ONLY the indextest executable 
* Run `./indextest oldIndexFilename newIndexFilename` 

## ASSUMPTIONS
The oldIndexFilename is formatted as specified in the Design Specs. 
Both oldIndexFilename and newIndexFilename already exist. `indextest` return an error otherwise. 

## ERROR CODES 
* 0 : Success
* 101 : indextest : invalid oldIndexFilename
* 100 : indextest : can't close oldIndexFilename
* 101 : indextest : invalid newIndexFilename
* 100 : indextest : can't close newIndexFilename

# KNOWN ERRORS
`make` only compiles `indexer` and not `indextest`. In order to compile both at the same time, run `make all`.

(Running `make` appears to compile common.a from scratch. I added that feature thinking it would be included in `make all`, but apparently it only works for `make`...) 
 
UPDATE 05/13/25: fixed `pagedir_save` so that it prints `int` instead of `DEPTH: int` when running crawler.

`indexer` is very leaky : not all memory freed when exit early... (~ 71 bytes when running `valgrind ./indexer ../data/letters-3 ../data/letters-3.index`) 
# FILES 
* -> indexer.c // main file 
* -> indextest.c // file with series of tests
* -> testing.sh // testing indexer inputs
* -> testing.out 
* -> .gitignore
* -> Makefile
