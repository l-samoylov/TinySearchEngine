// Lisa Samoylov CS50 Spring 2025 05/21/25
// Querier Module File 

#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include"pagedir.h"
#include"webpage.h"
#include"file.h"
#include"word.h"
#include"counters.h"
#include"index.h"

/**** FILE-LOCAL GLOBAL VARS ****/
/* none */

/**** LOCAL TYPES ****/
/* none */

/**** GLOBAL FUNCTIONS ****/ 
/* none */

/**** LOCAL FUNCTIONS ****/
// Big Helper Funcs
static void validateQuerier(int argc, char* argv[]); // debugged
static int isValidQuery(index_t* index, char* queryLine, char* pageDirectory); // 98% debugged 
static counters_t* getScores(index_t* index, char ** strings, int num_words);
static void rankScores(counters_t* scores, char* pageDirectory); 

// Little Helper Funcs
static void findMaxKeyID(void* arg, const int key, const int count); 
static void countNumWordMatch(void* arg, const int key, const int count); 
static void unionHelper(void* arg, const int key, const int count);
static void ctrsUNION(counters_t* ctrs1, counters_t* ctrs2); 
static void andHelper(void* arg, const int key, const int count);
static void ctrsAND(counters_t* ctrs1, counters_t* ctrs2); 
static int min(int A, int B); 



// START FUNCTIONS 

/**** MAIN() ****/
//================
/* 
* CALLER provides 
* ---------------
* three arguments : ./querier, char* pageDirectory, char* indexFilename 
* char* pageDirectory : pagedirectory containing output of crawler : ./crawler and docIds
* char* indexFilename : file containing the index in word : docID format 
* 
* WE DO : 
* ---------------
* Implement the querier according to REQUIREMENTS spec 
* 
* WE ASSUME :
* ---------------
* The assumptions outlined in the REQUIREMENTS spec
* 
* ERROR CODES: 
* -----------------
* 0 : success! 
* 1 : unable to make index
* 600 : incorrect number of args
* 601 : invalid pageDirectory 
* 602 : invalid indexFilename
* 603 : isValidQuery : bad malloc 
* 605 : can't make special counterset 
* 606 : can't find counterset @ word 
* 696 : querier : ctrsAND : couldn't make new counters
* 697 : querier : rankScores : couldn't load webpage
*/
int main(int argc, char* argv[])
{ 
    validateQuerier(argc, argv); 

    char* pageDirectory = argv[1]; 
    char* indexFilename = argv[2]; 

    index_t* index = index_load(indexFilename); 

    if (index == NULL) { // null check 
        return 1; 
    }

    char* line; 

    // Start: getting user input 
    printf("Query?: ");
    while((line = file_readLine(stdin)) != NULL) { // reading from stdin

        // checking for valid query 
        int result = isValidQuery(index, line, pageDirectory); 

        if (result == 0 || result == -1) { // empty query 
          printf("Query?: "); //next prompt
          continue; 
        }
         
        printf("Query?: "); //next prompt
        free(line); 
    }

    index_delete(index); 

    return 0; 
}

/*************** HELPER FUNCS ********************/
//================================================
/**** validateQuerier ****/
/* 
* CALLER PROVIDES : 
* -----------------
* int argc : number of command line args 
* char* argv[] : arguments past into the cmd line 
* 
* WE DO : 
* ----------------
* validate the command line arguments according to the README.md 
* free up any memory we allocate 
* 
* WE ASSUME : 
* ----------------
* Nothing
* 
*/
static void validateQuerier(int argc, char* argv[])
{ 
  if (argc != 3) { // checking correct number of inputs 
    fprintf(stderr, "error : querier : validateQuerier : number of arguments passed != 2\n"); 
    exit(600); 
  }

  char* pageDirectory = argv[1]; 
  char* indexFilename = argv[2]; 

  if (!pagedir_validate(pageDirectory)) { // validating pagedirectory 
    fprintf(stderr, "error : querier : validateQuerier : invalid pageDirectory\n"); 
    exit(601); 
  }

  if (!index_validate(indexFilename)) { // validating indexFilename 
    fprintf(stderr, "error : querier : validateQuerier : invalidIndexname\n"); 
    exit(602); 
  }
  return; 
}

/**** isValidQuery ****/
/* 
* CALLER PROVIDES: 
* ----------------
* char* queryLine : unvalidated user query (potentially empty) 
* 
* WE DO : 
* ----------------
* validate the query according to the CS50 Lab6 Specs 
* also calls getScores to obtain the scores for each document 
* also calls rankScores to print out the scores and document in decreasing order 
* free any memory we call
*
* WE ASSUME :
* ----------------
* (naively) index, queryLine and pageDirectory are NOT NULL
* the CALLER frees index, queryLine, and pageDirectory outside of isValidQuery

* RETURN : 
* ---------------- 
* 0 : no words 
* - 1 : invalidQuery
* -2 : can't make counters_t* scores 
* int j : number of words 
*/
static int isValidQuery(index_t* index, char* queryLine, char* pageDirectory) 
{ 
    int num_slots = strlen(queryLine); 
    char** strings = malloc(num_slots * sizeof(char*)); // word pointer array 
    
    if (strings == NULL) { // null check 
      fprintf(stderr, "error : querier : isValidQuery : bad malloc/can't parse string\n"); 
      exit(603); // max 128 
    }

    // FINDING WORDS 
    int isWord = 0; 
    int j = 0; // num_words 
  
    for (int i = 0; i < num_slots; i++) { 
      char cur = queryLine[i]; 

      // HANDLING SPACES
      if (isspace(cur)) { // space handling 

        if (isWord == 0) { 
          continue; 
        
        // HANDLING END OF WORD 
        } else if (isWord == 1){ 
          isWord = 0; 

           queryLine[i] = '\0'; // adding string ending  
        }
      }
      // HANDLING WORDS 
      else if (isWord == 0 && queryLine[i] != '\0') { // new word 
        isWord = 1; 
        strings[j] = &queryLine[i]; // setting pointer to be current character 
        j++; // moving pointer
      } 

    }

    // !!! empty line check 
    if (j == 0) {
      printf("Query: \n");
      free(strings);
      return 0; 
    }
    // NORMALIZING WORDS  
    for (int i = 0; i < j; i++){  
      word_normalize(strings[i]); 
    }

    // 0) Non alphabet characters
    for (int i = 0; i < j; i++) { 
      int word_len = strlen(strings[i]); 
      for (int k = 0; k < word_len-1; k++) { // avoiding \0
        if (isalpha(strings[i][k]) == 0 && isspace(strings[i][k]) == 0){ 
          fprintf(stdout, "Error: bad character '%c' in query\n", strings[i][k]); 
          return -1; 
        }
      }
    }

    // 1) Begins w/ AND OR 
    if (strcmp(strings[0],"and") == 0) { 
      fprintf(stdout, "Error: 'and' cannot begin query\n"); 
      return -1; 
    } else if (strcmp(strings[0],"or") == 0) { 
      fprintf(stdout, "Error: 'or' cannot begin query\n"); 
      return -1; 
    }

    // 2) Ends w/ AND OR 
    if (strcmp(strings[j-1],"and") == 0) { 
      fprintf(stdout, "Error: 'and' cannot end query\n"); 
      return -1; 
    } else if (strcmp(strings[j-1],"or") == 0) { 
      fprintf(stdout, "Error: 'or' cannot end query\n"); 
      return -1; 
    }

    // 3) Adjacent AND OR
    bool isAnd = false;
    bool isOr = false;
    for (int i = 0; i < j; i++) {
      // i) AND/OR can begin the word 
      if (i == 0 && (strcmp(strings[i], "and") == 0 || strcmp(strings[i], "or") == 0)) {
          fprintf(stdout, "Error: 'and' or 'or' cannot be at the beginning\n");
          return -1;
      }

      // ii) no adjacent AND/OR 
      if (isAnd) {
          if (strcmp(strings[i], "and") == 0) {
              fprintf(stdout, "Error: 'and' and 'and' cannot be adjacent\n");
              return -1;
          } else if (strcmp(strings[i], "or") == 0) {
              fprintf(stdout, "Error: 'and' and 'or' cannot be adjacent\n");
              return -1;
          }
      } else if (isOr) {
          if (strcmp(strings[i], "or") == 0) {
              fprintf(stdout, "Error: 'or' and 'or' cannot be adjacent\n");
              return -1;
          } else if (strcmp(strings[i], "and") == 0) {
              fprintf(stdout, "Error: 'or' and 'and' cannot be adjacent\n");
              return -1;
          }
      }

      // flag updating 
      if (strcmp(strings[i], "and") == 0) {
          isAnd = true;
          isOr = false;
      } else if (strcmp(strings[i], "or") == 0) {
          isOr = true;
          isAnd = false;
      } else {
          isAnd = false;
          isOr = false;
      } // iii) no AND/OR ending query
      if (i == j - 1 && (strcmp(strings[i], "and") == 0 || strcmp(strings[i], "or") == 0)) {
          fprintf(stdout, "Error: 'and' or 'or' cannot be at the end\n");
          return -1;
      }
    }

  // printing the query
  printf("Query: ");
  for (int i = 0; i < j; i++) { 
    printf("%s ", strings[i]); 
  }

  printf("\n"); 

  
  // REST OF FUNCIONALITY 
  int num_words = j; 
  counters_t* scores = getScores(index, strings, num_words);  
  
  if (scores == NULL) { // null check 
    free(strings); 
    return -2; 
  }

  // RANKING THE SCORES 
  rankScores(scores, pageDirectory); 

  counters_delete(scores); 

  free(strings); 
  return j; 
}

/**** getScores() ****/
/* 
* CALLER PROVIDES : 
*--------------------
* index_t* index : index with word ctrset((docID, count)) pairs
* char ** strings : arr of str pointers (each ptr points to a word) 
* int num_words : number of words strings
* 
* WE DO : 
* 
* 
* ASSUME : 
*-----------
* (naively) neither index nor strings nor num_words are NULL 
* the CALLER frees index and strings outside the call to getScores 
* 
*/
static counters_t* getScores(index_t* index, char ** strings, int num_words) 
{ 
  counters_t* ctrs_result = counters_new(); // cumulative docID scores

  counters_t* ctrs_temp = counters_new(); 

  if (ctrs_result == NULL || ctrs_temp == NULL) { // null check 
    fprintf(stderr, "error : querier : can't make special counterset\n"); 
    exit(605); 
  }

  bool flag = true;
  bool non_exist = false;

  // One bug is what if it's all ANDs? 
  for (int i = 0; i < num_words; i++) { // going through each word
    char* word = strings[i]; 

    // Check 1: Ignore !OR words w/ Length < 3
    if (strcmp(word, "or") != 0 && strlen(word) < 3) { 
      continue; 
    }

    // Case 1: read 'and' 
    else if (strcmp(word, "and") == 0) { 
      continue; 
    }

    // Case 2: read a word (assuming valid query )
    else if (strcmp(word, "or") != 0) { 
      counters_t* ctrs_w = index_find(index, word); 
      if (ctrs_w == NULL) { // null check 
        non_exist = true;
        flag = false;
        counters_delete(ctrs_temp); 
        ctrs_temp = counters_new(); 
        continue; 
      }
            
      if (flag) { // special case : empty scores 

        ctrsUNION(ctrs_temp, ctrs_w); 

        flag = false;
      }

      else { // accumulating temp &s 
        if (!non_exist){
          ctrsAND(ctrs_temp, ctrs_w); 
        }
      }
    } 

    // Case 3: read 'or' or none of the above
    else { // reading an OR
        ctrsUNION(ctrs_result, ctrs_temp); 
        counters_delete(ctrs_temp); 
        ctrs_temp = counters_new(); 
        flag = true;
        non_exist = false;

        if (ctrs_temp == NULL) { // null check 
        fprintf(stderr, "error : querier : can't find counterset\n"); 
        exit(606); 
      }
    }    
  }

  ctrsUNION(ctrs_result, ctrs_temp); 

  // free
  if (ctrs_temp != NULL ) { 
    counters_delete(ctrs_temp); 
  }

  fflush(stdout); 
  return ctrs_result; 
}

/**** rankScores() ****/
/* 
* CALLER PROVIDES : 
*-------------------
* counters_t* scores : counterset of docID and scores for a given query 
* 
* WE DO : 
*-------------------
* print the number of docIDs that match part of the query (if at all!) 
* print the docId and score and url of the webpage the docID links to (in decreasing order)
* clean up the memory 
* 
* ASSUME : 
*-------------------
* (naively) neither scores nor pageDirectory are NULL 
* the CALLER frees scores and pageDirectory outside rankScores 
*/
static void rankScores(counters_t* scores, char* pageDirectory) 
{ 
  int numMatch = 0; 

  counters_iterate(scores, &numMatch, countNumWordMatch); 

  if (numMatch == 0) { // checking if no matches 
    printf("no documents matched\n"); 
    return; 
  }

  printf("Matched %d documents : \n", numMatch); 

  int arr[2]; // (key, count)  

  arr[1] = -1; 
  
  while (arr[1] != 0) { 
    arr[0] = 0;   arr[1] = -1;
    
    counters_iterate(scores, arr, findMaxKeyID); 

    webpage_t* page = pagedir_load(pageDirectory, arr[0]); // getting the page

    if (page == NULL) { // null check 
      fprintf(stderr, "error : querier : rankScores : couldn't load webpage\n"); 
      exit(697); 
    }

    char* url = webpage_getURL(page); // getting the URL 

    //printing 
    if (arr[1] != 0){
      printf("score %d doc %d : %s\n", arr[1], arr[0], url); 
    }
    // resetting 
    counters_set(scores, arr[0], 0);

    webpage_delete(page); 
  }
}
/***************** LITTLE HELPER FUNCS **********************/
//===========================================================

/**** findMaxKeyID() ****/
/*-----------------------*/
/* counters_iterate helper computes the docID (and its score) with the max score */
static void findMaxKeyID(void* arg, const int key, const int count) 
{ 
  int* arr = arg; 
  if (count > arr[1]) { 
    arr[1] = count; 
    arr[0] = key; 
  }
}

/**** countNumWordMatch() ****/
//----------------------------
/* counts the number of docs that contain the word */ 
static void countNumWordMatch(void* arg, const int key, const int count) 
{ 
  int* numMatch = arg; 
  
  if (count > 0) { 
    (*numMatch) ++; 
  }
}
/**************** andHelper() *******************/
//-----------------------------------------------
/* counterset iterator function. Helper function for ctrsAND */
/* arg is implicit counters_t*; updates docID-> count for arg */
static void andHelper(void* arg, const int key, const int count)
{ 
    counters_t* ctrs = arg; 
    int val = counters_get(ctrs, key); 
    counters_set(ctrs, key, min(val, count)); 

}

/*************** ctrsAnd() **********************/
//-----------------------------------------------
/* wrapper function for andHelper;; updates ctrs1 docID and count with AND*/
static void ctrsAND(counters_t* ctrs1, counters_t* ctrs2) 
{
  counters_t* temp = counters_new(); 
  
  if (temp == NULL) { //null  
    fprintf(stderr, "error: querier : ctrsAND : couldn't make new counters\n"); 
    exit(696); 
  }

  ctrsUNION(temp, ctrs2); 

  counters_iterate(ctrs1, temp, andHelper); 

  counters_iterate(temp, ctrs1, andHelper); 

  counters_delete(temp); 
}

/**** unionHelper() ****/
//-----------------------
/* counterset iterator function. Helper function for ctrsUNION */
/* arg is implicit counters_t*; updates docID-> count for arg */
static void unionHelper(void* arg, const int key, const int count)
{ 
    counters_t* ctrs = arg;
    int val = counters_get(ctrs, key); 
    counters_set(ctrs, key, val + count); 
}

/**** ctrsUNION() ****/
//---------------------
/* wrapper function for union; updates ctrs1 docID and count with Union */
static void ctrsUNION(counters_t* ctrs1, counters_t* ctrs2) 
{ 
  counters_iterate(ctrs2, ctrs1, unionHelper); 
}
/**** min ****/
//---------------------
/* takes the min of two ints */
static int min(int A, int B) 
{ 
  if (A < B) { return A; }
  else {return B; }
}



// Ahmed's debugging tips: 
// gdb ./file 
// run args 
// -bt 
// tells you what line its on