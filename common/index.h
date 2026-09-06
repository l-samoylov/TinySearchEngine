// Lisa Samoylov CS50 Spring 2025
// `index.h` header file
//  Functions related to `index` struct 

#ifndef __INDEX_H
#define __INDEX_H

#include<stdio.h>
#include<stdbool.h> 

/**************** global types ****************/
typedef struct index index_t;  // opaque to users of the module

/**************** functions ****************/

/***************** index_new() ***********************/
/* 
* CALLER provides: Nothing 
* ----------------
*
* WE DO: 
* ----------------
* initialize a new index
* 
* WE ASSUME: 
* ----------------
* Caller later calls index_delete on the index to free the memory 
* Index will contain up to 900 words. (It contains slots to store max 900 words.) 
*/
index_t* index_new(void); 

/***************** index_insert()***********************/
/* 
* CALLER provides: 
* ----------------
* @ index_t* idx : 
* @ char* word : 
* @ int docID : 
* 
* WE DO: 
* ----------------
* return TRUE : if we can look up the word in index, and the docID in counterset, and increment the number of 
* times the word appears in docID by 1
* 
* return FALSE : if encounter any errors
*  
* WE ASSUME: 
* ----------------
* Caller provides a non-null pointer. 
* 
*/
bool index_insert(index_t* idx, const char* word, const int docID);

/***************** index_mass_add()**************************/
/* 
* CALLER provides: 
* ----------------
* WE DO: 
* ----------------
* WE ASSUME: 
* ----------------
*/
bool index_add(index_t* idx, const char* word, const int docID, const int count); 

/***************** index_delete()***********************/
/* 
* CALLER provides: 
* ----------------
* @ index_t* idx: to-be-deleted index  
*
* WE DO: 
* ----------------
* If the index is non-null, we delete the index and free the memory 
* 
* WE ASSUME: Nothing
* ----------------
*/
void index_delete(index_t* idx); 

/***************** index_print()***********************/
/* 
* CALLER provides: 
* ----------------
* @ index_t* idx : struct index 
* @ char* indexFilePath : char* file-path-to-index-file
*
* WE DO: 
* ----------------
* Iterate through the index and print it to the file located by indexFilePath
* 
* WE ASSUME: 
* ----------------
* The caller already validated indexFilePath and provides an index with a hashtable that's full / NO NULL ptrs
*/
void index_print(index_t* idx, char* indexFilePath); 

/***************** index_load()***********************/
/* 
* CALLER PROVIDES: 
* -----------------
* @ char* indexFilePath : where index_load reads from
*
* WE DO: 
* -----------------
* read the indexFilePath, generate an index from the given file, and return the index 
* 
* ASSUME that CALLER:
* -----------------
* @ ALREADY VALIDATES indexFilePath
*   indexFilePath is structued according to the specs : word [docID, count]
* @ frees idx outside of index_load() 
* @ handles NULL ptrs outside of index_load()
*/
index_t* index_load(char* indexFilePath);

/***************** index_validate() **************************/
/* 
* CALLER provides : 
* char* indexFilepath : file path to index file to-be-validated
* 
* WE DO : 
* open indexFilepath to read. If we can successfully open/close the file, return True 
* else return False. 
*/
bool index_validate(char* indexFilepath); 


/***************** index_find() **************************/
void* index_find(index_t* index, char* key);

#endif // __INDEX_H
