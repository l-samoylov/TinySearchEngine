/* Lisa Samoylov CS50 Spring 2025 */ 
/* `indextest.c` file to convert index file formats */ 

#include<stdio.h>
#include<stdlib.h>
#include"index.h"

/**** file-local global variables ****/
/* none */

/**** local types ****/
/* none */

/**** local functions ****/
static void indextest_validate(int argc, char* argv[]); 

/**** global functions ****/ 

/**** MAIN ****/ 
//==============
int main(int argc, char* argv[])
{ 
  indextest_validate(argc, argv); 
  char* oldIndexFilename = argv[1]; 
  char* newIndexFilename = argv[2]; 

  index_t* index = index_load(oldIndexFilename); 
  index_print(index, newIndexFilename); 
  return 0; 
} 

/**** index_validate ****/
//=======================/
/* 
* CALLER PROVIDES: 
* ---------------
* @ argv[] = {./indextest oldIndexFilename newIndexFilename} where
* char* oldIndexFilename : index file written by indexer
* char* newIndexFilename : new file location to be written to by indextest.c
* 
* WE DO: 
* ---------------
* check if the parameters are valid 
* 
* ERRORS: 
* exit(100) = file close error
* exit(101) = invalid oldIndexFilename
* exit(102) = invalid newIndexFilename
*/
static void indextest_validate(int argc, char* argv[])
{ 
  // checking correct number of args 
  if (argc != 3) { 
    fprintf(stderr, "error : indextest : wrong num args\n");    exit(100); 
  } 

  // checking valid paths 
  char* oldIndexFilename = argv[1]; 
  char* newIndexFilename = argv[2];

  FILE* fptr = fopen(oldIndexFilename, "r"); 
  if (fptr == NULL) { // no indexer index file to read from 
    fprintf(stderr, "error : indextest : invalid oldIndexFilename\n"); 
    exit(101); 
  } 
  
  // closing file
  if (fclose(fptr) != 0){ 
    fprintf(stderr, "error : indextest : index_validate : couldn't close file \n"); 
    exit(100); 
  }

  fptr = fopen(newIndexFilename, "r"); 

  if (fptr == NULL) { // no indexer index file to read from 
    fprintf(stderr, "error : indextest : invalid newIndexFilename\n"); 
    exit(101); 
  } 
  
  // closing file
  if (fclose(fptr) != 0){ 
    fprintf(stderr, "error : indextest : index_validate : couldn't close file \n"); 
    exit(100); 
  }

  return; 
} 
