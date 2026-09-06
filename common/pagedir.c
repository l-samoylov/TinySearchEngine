// Lisa Samoylov CS50 Spring 2025
// `pagedir.c` module

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include"webpage.h"
#include"pagedir.h"
#include"file.h"

// got help from 
// https://www.geeksforgeeks.org/memcpy-in-cc/
// https://www.geeksforgeeks.org/snprintf-c-library/

/**** file-local global variables ****/ 
/* none */ 

/**** global types ****/ 
/* none */ 

/**** local types ****/ 
/* none */ 

/***** global functions ****/ 
/* see pagedir.h */ 

/**** local functions ****/ 
/* none */ 

//==============================

/**** pagedir_init() ****/

bool pagedir_init(const char* pageDirectory)
{
  FILE *fptr; 

  // CONSTRUCTING PATHNAME for ./crawler in pageDirectory

  // getting lens 
  int totalLen = strlen(pageDirectory) + strlen("/.crawler") + 1; //extra space as a buffer 

  // alloc memory for path
  char* pathname = malloc(totalLen);  

  if (pathname == NULL){ 
    fprintf(stderr, "error: pagedir.c: pagedir_init: malloc failed\n"); 
    return false; 
  }

  //building path string 
  strcpy(pathname, pageDirectory); 
  strcat(pathname, "/.crawler"); 

  // printf("pathname PAGEDIR: %s\n",pathname); 
  // fflush(stdout);

  // opening file for writing 
  fptr = fopen(pathname, "w"); 

  // see error; return false
  if (fptr == NULL){
    free(pathname);
    fprintf(stderr, "error: null pathname\n"); 
    fflush(stderr);  
    return false; 
  }

  // closing the file 
  fclose(fptr);
  
  free(pathname);  

  return true; 
} 

/**** pagedir_save() ****/
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID)
{
  FILE* fptr; 
  // constructing the pathname
  int totalLen = snprintf(NULL,0,"%s %d", pageDirectory, docID);
  char* pathname = (char*)malloc((totalLen+1) * sizeof(char));

  // copyiny the pathname
  snprintf(pathname,totalLen+1, "%s/%d", pageDirectory,docID); 

  // opening the file for writing 
  fptr = fopen(pathname, "w"); 

  if (fptr == NULL){  
    fprintf(stderr, "error: pagedir_save(): constructed file did not open)\n"); 
    exit(20); 
  } 
  
  // printing the url 
  char* pageURL = webpage_getURL(page); 
  fprintf(fptr,"%s\n",pageURL); 

  // printing the depth 
  int pageDepth = webpage_getDepth(page); 
  fprintf(fptr, "%d\n", pageDepth); 

  // printing the contents 
  char* pageHTML = webpage_getHTML(page);  
  fprintf(fptr, "%s\n",pageHTML); 
 
  // closing the file  
  fclose(fptr); 
  free(pathname); 
  return; 
}

/**** pagedir_validate() ****/ 
bool pagedir_validate(char* pageDirectory)
{
  FILE *fptr; 

  // CONSTRUCTING PATHNAME for ./crawler in pageDirectory

  // getting lens 
  int totalLen = strlen(pageDirectory) + strlen("/.crawler") + 1; //extra space as a buffer 

  // alloc memory for path
  char* pathname = malloc(totalLen);  

  if (pathname == NULL){ 
    fprintf(stderr, "error: pagedir.c: pagedir_validate: malloc failed\n"); 
    return false; 
  }

  //building path string 
  strcpy(pathname, pageDirectory); 
  strcat(pathname, "/.crawler");

   // opening file for reading - to avoid accidentally creating a new file
  fptr = fopen(pathname, "r"); 

  // see error; return false
  if (fptr == NULL){
    fprintf(stderr, "error: pagedir.c: pagedir_validate: invalid .crawler/directory\n"); 
    free(pathname);   
    return false; 
  }

  // closing the file 
  fclose(fptr);
  
  free(pathname);  

  return true; 
} 

/**** pagedir_load() ****/ 
webpage_t* pagedir_load(char* pageDirectory, const int docID)
{ 
 // converting docID from int to str
 char docID_str[32]; 
 sprintf(docID_str, "%d", docID); 
 
 // getting the pathname
 char* pathname = pagedir_make_path(pageDirectory,docID_str); 
 
 // null check 
 if (pathname == NULL) { 
   fprintf(stderr, "error : pagedir : pagedir_load : invalid path\n"); 
   return NULL; 
 } 

 // opening the file 
 FILE* fptr = fopen(pathname, "r"); 
 
 // null check 
 if (fptr == NULL) { 
   free(pathname); 
   return NULL;  
 }
 
// file reading 
char* url = file_readLine(fptr); // getting "URL"

if (url == NULL) { // error check 
  free(pathname); 
  fclose(fptr); 
  free(url); 
  fprintf(stderr, "error : pagedir : pagedir_load : couldn't get URL\n"); 
  return NULL; 
}

char* depthChar = file_readLine(fptr); // getting "INT" depth 

if (depthChar == NULL){  // error check 
  free(pathname); 
  free(url); 
  fclose(fptr); 
  fprintf(stderr, "error : pagedir : pagedir_load : couldn't get depth\n"); 
  return NULL; 
}

// printf("PATH: %s\nURL: %s, \nDEPTH: %s\n\n", pathname, url, depthChar); 

int depth; 
sscanf(depthChar, "%d", &depth); 
free(depthChar); 

// making the webpage 
webpage_t* page = webpage_new(url, depth, NULL); 

if (page == NULL) { // error check 
  free(pathname); 
  free(url); 
  fclose(fptr); 
  fprintf(stderr, "error : pagedir : pagedir_load : couldn't make a page\n"); 
  return NULL; 
}

// filling the html
bool result = webpage_fetch(page); 

if (result == false) { // error check 
  free(pathname); 
  free(url); 
  fclose(fptr); 
  webpage_delete(page); 
  fprintf(stderr, "error : pagedir : pagedir_load : couldn't fetch HTML\n"); 
  return NULL; 
}

fclose(fptr); 
free(pathname); 
return page; 
} 

/**** pagedir_make_path() ****/
char* pagedir_make_path(char* pageDirectory, char* fileName)
{ 
  // getting lens 
  int totalLen = strlen(pageDirectory) + strlen(fileName) + 3; //extra space as a buffer 

  // alloc memory for path
  char* pathname = malloc(totalLen);  

  if (pathname == NULL){ 
    fprintf(stderr, "error: pagedir.c: pagedir_make_path: malloc failed\n"); 
    return NULL; 
  }

  //building path string 
  strcpy(pathname, pageDirectory); 
  strcat(pathname, "/");
  strcat(pathname, fileName); 

  return pathname; // assume this gets freed later
}