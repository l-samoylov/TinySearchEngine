# Lisa Samoylov CS50 Spring 2025
# Querier Implementation
--- 

Querier was implemented via a single module, `querier.c`. The main functions used are outlined below. See `querier.c` for more information on any helper functions used. 

## BIG FUNCTIONS 
--- 
`main` Wrapper :  
* `main` takes `./querier pageDirectory indexFilename`, parses and validates the arguments, 
and then starts taking input from stdin
* Then `main` calls on `isValidQuery` to parse the query input while there is a query != EOF 

`isValidQuery` : 
* parses the query into words 
* checks if query meets the input syntax requirements as described in https://github.com/CS50DartmouthSP25/home/blob/main/labs/tse/querier/REQUIREMENTS.md
* if the input syntax is met `isValidQuery` calls `getScores` to get a `counters_t* scores` struct that stores `(docID, word_count)` pairs. `docID` is the page that the word appears in, and `word_count` is the number 

`getScores` : 
* Implements the arithmetic outlined in https://github.com/CS50DartmouthSP25/home/blob/main/knowledge/units/querier-expressions.md to score the docIDs and store them in a `counters_t*` structure 

`rankScores` : 
* Ranks the scores by iterating through `counters_t* scores`, finding the maxDocId with the maxVal score, and printing them out. Then maxDocID's score is set to 0, and the process is repeated until every docID in `counters_t* scores` has a score of 0. 

## LITTLE HELPER FUNCTIONS 
--- 
See `querier.c` for more information. 