/* Lisa Samoylov CS50 Spring 2025 */ 
/* `index.c` file implementing `index` data structure */ 

#include<stdio.h> 
#include<stdlib.h>
#include<string.h> 
#include"hashtable.h"
#include"file.h"
#include"counters.h"
#include"hash.h"
#include"mem.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
static void special_ctrs_print(void* arg, const int key, const int item); // custom itemfunc function for counterset_iterate()
static void special_set_print(void* arg, const char* key, void* item); // custom itemfunc function for set_iterate()
void countersDelete(void* counters); // special delete function for index_delete()
/**************** global types ****************/
typedef struct index{
  hashtable_t* id_table; 
  char* indexFilename; 
}index_t;


/**************** global functions ****************/
/* see index.h for comments about exported functions */


/**************** local functions ****************/
/* not visible outside this file */
/* none */

/***************** index_new() ***********************/
index_t* index_new(void)
{ 
  int num_words = 900; // assume need max 900 slots for words

  index_t* idx = mem_malloc(sizeof(index_t)); // making empty index

  idx->id_table = hashtable_new(num_words); // making empty index table 

  return idx; 
} 

/***************** index_insert()***********************/
bool index_insert(index_t* idx, const char* word, const int docID)
{ 
  // valid index 
  if (idx != NULL && word != NULL) { 
    counters_t* word_counts = hashtable_find(idx->id_table, word); 

    // word isn't in the hashtable
    if (word_counts == NULL) { 

      // making a new countersset 
      counters_t* word_counts = counters_new(); // assuming NOT NULL  

      if (word_counts == NULL) { 
        fprintf(stderr, "error : index : index_insert : couldn't make counterset\n"); 
        return false; 
      }

      counters_add(word_counts, docID); // assuming it works 

      // inserting counterset to id_table 
      return hashtable_insert(idx->id_table, word, word_counts); // keyed by word 

    } else {
      // updating the counters
      counters_add(word_counts,docID); 
      return true; 
    }
  } 

  // null pointer
  else { 
    return false; 
  } 
} 

/***************** index_add()**************************/
bool index_add(index_t* idx, const char* word, const int docID, const int count)
{ 
  counters_t* word_counts = hashtable_find(idx->id_table, word); 

  // word isn't in the hashtable
  if (word_counts == NULL) {
    free(word_counts); 

    // making a new countersset 
    counters_t* word_counts = counters_new(); // assuming NOT NULL  
    counters_set(word_counts, docID, count); // assuming it works 

    // inserting counterset to id_table 
    hashtable_insert(idx->id_table, word, word_counts); // keyed by word 
  }

  // updating the counters
  int cur_count = counters_get(word_counts, docID); 
  cur_count += count; 

  counters_set(word_counts,docID, cur_count); 
  return true; 

}

/***************** index_delete()***********************/
void index_delete(index_t* idx)
{ 
  if (idx != NULL){
    // deleting the counters inside the hashtable 

    // delete the id_table
    hashtable_delete(idx->id_table, countersDelete);
  }

  mem_free(idx); 
  return; 
} 

/***************** countersDelete() *******************/
void countersDelete(void* counters) 
{ 
  counters_delete(counters); 
}
/***************** index_print()***********************/
void index_print(index_t* idx, char* indexFilePath)
{  
  // assume indexFilePath is good 
  FILE *fptr = fopen(indexFilePath, "w"); // getting the pointer 

  if (idx != NULL && fptr != NULL){  // null check  
    // idea is to iterate through the index_table 
    hashtable_iterate(idx->id_table, fptr, special_set_print); 
  }

  fclose(fptr); 
}

/***************** index_load()***********************/
index_t* index_load(char* indexFilePath) 
{   
  // null check
  if (indexFilePath == NULL) { 
    fprintf(stderr, "error: index : index_load : null index file\n"); 
    return NULL;  
  } 

  FILE* fptr; 
  fptr = fopen(indexFilePath, "r"); 
  
  // null check 
  if (fptr == NULL) { 
    fprintf(stderr, "error: index_load : couldn't open file\n"); 
    return NULL; 
  } 
  
  // initializing everything 

  index_t* idx = index_new(); 

  int docID; 
  int count; 
  int offset;

  char* wptr; // word ptr
  // read the word first
  while ((wptr = file_readWord(fptr)) != NULL){ 
    char* lptr; // line ptr

    // read rest of the line 
    char* line = file_readLine(fptr); 
    lptr = line;  
    
    // reading the line 
    while (sscanf(lptr, "%d %d %n", &docID, &count, &offset) == 2){
      bool result = index_add(idx, wptr, docID, count); 
      if (result == false){ 
        fprintf(stderr, "error : index : index.load : failed to add word/docID/count into index\n"); 
      }
      lptr += offset; 
    }
    free(wptr); 
    free(line); 
  } 
  // closing file
  if (fclose(fptr) != 0){ 
      fprintf(stderr, "error : index : pagedir_load : couldn't close file \n"); 
  }
  return idx;
}
/***************** index_validate() **************************/
bool index_validate(char* indexFilepath) 
{ 
  FILE *fptr = fopen(indexFilepath, "r");
  if (fptr == NULL){ 
    return false; 
  }

   // closing file
  if (fclose(fptr) != 0){ 
    false; 
  }
  return true; 
}

/***************** index_find() **************************/
void* index_find(index_t* index, char* key) 
{ 
  return hashtable_find(index->id_table, key); 
}

/***************** special_ctrs_print()***********************/
/* 
 * CALLER provides: 
 * ---------------
 * @ void* arg : implicitly a pointer to a file. This is a file pointer.
 * @ int key : docID 
 * @ int item : count
 * 
 * WE DO: 
 * ---------------
 * We print "docID count" to the file
 * 
 * WE ASSUME: 
 * ---------------
 * fptr is a FILE* ptr. 
 * fptr is already initialized and open. The caller already opened fptr and will later close it. 
*/
static void special_ctrs_print(void* arg, const int key, const int item)
{
  // prints the "docID count"
  fprintf(arg, "%d %d ", key, item); 
}

/***************** special_set_print()***********************/
/* 
* CALLER PROVIDES: 
* ----------------
* void * arg : (implied to be a file pointer) 
* const char* key : (implied to be the docID) 
* void* item : (implied to be a counters_t*)
*/
static void special_set_print(void* arg, const char* key, void* item)
{ 
  fprintf(arg, "%s ", key); //printing the word 
  counters_iterate(item, arg, special_ctrs_print); // printing [docID count] 
  fprintf(arg, "\n"); 
}

/* 
* BAD CODE
if (idx->id_table != NULL){  // null check 
      if (idx->id_table->slot_arr != NULL){  // null check

        // iterating through the slots 
        for (int i = 0; i < idx->id_table->num_slots; i++){ 

          // null check 
          if (idx->id_table->slot_arr[i] != NULL){ 

            fprintf(fptr, "%s ", idx->id_table->slot_arr[i]->key); // printing word 
        
            // printing the newline
            counters_iterate(idx->id_table->slot_arr[i]->item, fptr, word_count_print);  
          }
        }
      }
    }  
*/