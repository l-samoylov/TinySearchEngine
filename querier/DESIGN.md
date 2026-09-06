# Lisa Samoylov CS50 Spring 2025
# Querier Design 
--- 

## User Interface
---

## Inputs / Outputs 
---

## Major Data Structures 
--- 
* `index_t* index` is the index loaded out of indexFilename 
* `counters_t* scores` is a counterset containing each docID and its score for the query 

## Testing Plan 
--- 

We test `./querier` to ensure that it only accepts valid command line arguments 
* only accepts three arguments `./querier pageDirectory indexFilename` 
* `pageDirectory` is a valid pageDirectory (can be read AND contains a `./crawler`)
* `indexFilename` is a valid indexFilename (and can be read)

We also test `./querier` to ensure that it correctly validates queries according to the syntax outlined in 
https://github.com/CS50DartmouthSP25/home/blob/main/labs/tse/querier/REQUIREMENTS.md 
