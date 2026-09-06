/* Lisa Samoylov CS50 Spring 2025 */ 
/* indexer.c */ 

#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include"webpage.h" 
#include"pagedir.h"
#include"index.h"
#include"word.h" 

/**** file-local global variables ****/
/* none */

/**** local types ****/
/* none */

/**** global functions ****/ 
/* see indexer.h  for more info */ 

/**** local functions ****/
static void validateArgs(int argc, char* argv[]); 
static index_t* indexBuild(char* pageDirectory); 
static void indexPage(webpage_t* page, index_t* index, int docID);

/**** MAIN ****/
//-------------
/*  CALLER provides: 
 *  ----------------
 *  @ char* pageDirectory : 
 *  @ char* indexFilename : 
 *
 *  WE ASSUME: 
 *  -----------
 *  @ pageDirectory already exists in the path
 *  @ pageDirectory has files named 1, 2, 3, ..., without gaps.
 *  @ The content of files in pageDirectory follow the format as defined in the specs
 *  @ indexFilename : is a path to the file (e.g. ../data/letters.index instead of letters.index) 
 *  
 *  WE DO: 
 *  ------------
 *  @ implement indexer as outlined in the specs
 *
 *  ERRORS:
 *  ----------
 *  return 0 : success
 *  exit 10 : wrong number of args
 *  exit 11 : invalid pagedirectory 
 *  exit 12 : invalid indexFilename 
 */
int main(int argc, char* argv[])
{
  validateArgs(argc, argv);
  
  char* pageDirectory = argv[1];
  char* indexFilename = argv[2]; 

  index_t* index = indexBuild(pageDirectory); 
  index_print(index, indexFilename); 
  index_delete(index);  

  return 0; 
}

/**** validateArgs() ****/ 
static void validateArgs(int argc, char* argv[])
{
  // !!! checking correct num args
  if (argc != 3) {
    fprintf(stderr, "error: main takes 3 args\n"); 
    exit(10); 
  }

  char* pageDirectory = argv[1];

  // !!! checking that pageDirectory exists
  bool exists = pagedir_validate(pageDirectory);
  if (!exists){ 
    fprintf(stderr, "error : indexer : invalid pageDirectory\n"); 
    exit(11); 
  }

  // !!! checking that indexFilename exists 
  char* indexFilename = argv[2];

  FILE *fptr = fopen(indexFilename, "r");
  if (fptr == NULL){ 
    fprintf(stderr, "error : indexer : validateArgs : invalid indexFilename\n"); 
    exit(12);
  }

   // closing file
  if (fclose(fptr) != 0){ 
    fprintf(stderr, "error : indexer : validateArgs : couldn't close file \n"); 
    exit(100); 
  }

  return; 
} 
/**** indexBuild() ****/
/* CALLER PROVIDES: 
 * ----------------
 * @ char* pageDirectory
 *
 * WE ASSUME: 
 * ----------------
 * @ ALL docIDs are present with no gaps (valid)
 * @    valid : pageDirectory/ 1 2 3 4 5
 * @    invalid : pageDirectory/ 1 2  4 5 
 * @ Caller later deletes the index with index_delete()
 *
 * WE DO: 
 * ----------------
 * implement indexBuild according to the specs 
 * return an index 
 * avoid any memory leaks/errors
 */

static index_t* indexBuild(char* pageDirectory)
{ 
  index_t* idx = index_new(); 

  // looping over docID nums; starting from 1
  int docID = 1; 
  int invalidFlag = 0; 
  
  // making the index 
  while(invalidFlag == 0){
    // loading webpage from `pageDirectory/id`
    webpage_t* page = pagedir_load(pageDirectory, docID); 
    
    // debugging 
    if (page == NULL){ // couldn't load page
      printf("NULL PAGE\n"); 
      fflush(stdout); 
      invalidFlag = 1; 
    } else { // successfully loaded page
      indexPage(page, idx,docID); // calling indexPage 
      webpage_delete(page);  
      docID ++; 
    } 
  } 
  return idx; 
}


/**** indexPage() ****/
static void indexPage(webpage_t* page, index_t* index, int docID)
{
  // for each word in webpage
  char* w; 
  int pos = 0; 
  while ((w = webpage_getNextWord(page, &pos)) != NULL){ 
    // if |word| < 3 skip 
    if (strlen(w)<3) { 
      continue; 
    }

    // normalizing the word 
    word_normalize(w);
    
    // looking up word / inserting / incrementing word in index 
    index_insert(index, w, docID); 
    free(w); 
  }
  return; 
} 