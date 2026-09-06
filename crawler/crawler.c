/* Lisa Samoylov CS50 Spring 2025 */ 
/* crawler.c */

#include<stdio.h>
#include<stdlib.h>
#include"hashtable.h"
#include"webpage.h"
#include"bag.h"
#include"set.h"
#include"pagedir.h"

/**** file-local global variables ****/ 
/* none */ 

/**** local types ****/ 
/* none */ 

/**** local functions ****/ 
static void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth); 

static void crawl(char* seedURL, char* pageDirectory, const int maxDepth); 

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen); 

static void logr(const char *word, const int depth, const char *url); // for nice printing, courtesy of https://github.com/CS50DartmouthSP25/home/blob/6ac6474d89089f102b482106fb59de4fdda1de78/knowledge/units/crawler-logging.md



/**** MAIN  ****/
/* driver for crawl + parseargs */ 
/* CALLER provides: 
 * @ seedURL: starting URL for the crawler
 * @ pageDirectory: dir to store output files
 * @ maxDepth: max depth of webpages to crawl; IS A VALID INT 
 * 
 * ASSUME: 
 * @ pageDirectory does not contain any files whose name is an integer (i.e., 1, 2, ...).
 * @ Caller made the pagedirectories before calling them
 *
 * WE DO: 
 * @ guarantee no memory leaks 
 *
 * ERRORS: 
 *  return 0 : success
 *  return 10 : wrong number args
 * */
int main(int argc, char *argv[])
{
  // !!! checking for correct number of args
  if (argc != 4) { 
    fprintf(stdout, "error: main takes 4 args\n"); 
    return 10; 
  }

  // var declarations
  char** seedURL = &argv[1]; 
  char** pageDirectory = &argv[2]; 
  
  //converting char* maxDepth to base10 int 
  int maxDepth =atoi(argv[3]); 
  
  // validting/initializing args 
  parseArgs(argc, argv, seedURL, pageDirectory, &maxDepth); 

  // crawling 
  crawl(*seedURL, *pageDirectory, maxDepth); 
 
  return 0; 
} 

/**** parseArgs() ****/
/* CALLER provides: 
 * @argc: number of cmd line args
 * @argv[]: arr of cmd line args
 * @seedURL: ptr to seedURL arg in argv[]
 * @pageDirectory: ptr to pageDirectory arg in argv[]
 * @maxDepth: int ptr to maxDepth arg in argv[] (int* maxDepth points to int(argv[3]))
 *
 * ASSUME: 
 * 1. the maxDepth arg represents valid integer (e.g. not "12@%TIgj93") 
 * 2. Correct number of args passed into cmd line 
 * 
 * WE DO: 
 * char** seedURL: convert it to char* 
 * char** pageDirectory: convert it to char* 
 * int* maxDepth: convert it to const int 
 *
 * EXIT CODES: 
 *  1 : failed to normalize seedURL arg (argv[1])
 *  2 : seedURL IS NOT INTERNAL (is null, external)
 *  3 : pagedir_init() failed to initialize argv[2]
 *  4 : maxDepth out of range (not in [0,10])
 */

static void parseArgs(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth)
{ 
  // normalizing the URL
  *seedURL = normalizeURL(argv[1]); // mem error? 
  
  if (seedURL == NULL){ // failed to normalize/parse URL
    fprintf(stderr, "error: parseArgs: argv[1] failed to normalize/parse\n"); 
    exit(1);
  } 
  // printf("seed url: %s\n", *seedURL);
  // printf("is inderntal?: %d\n", isInternalURL(*seedURL)); 

  // validating seedURL is internal 
  if (!isInternalURL(*seedURL)) {
    fprintf(stderr, "error: parseArgs: argv[1] is NOT INTERNAL\n"); 
    exit(2); 
  } 

  // calling pagedir_init
  printf("pagedir: %d\n", pagedir_init(argv[2])); 
  if (!pagedir_init(argv[2])){
    fprintf(stderr, "error: parseArgs: pagedir failed to initialize page for seedURL\n"); 
    exit(3); 
  } 
   
  pageDirectory = &argv[2]; 

  // checking max depth is in range 
  if (*maxDepth < 0 || *maxDepth > 10){ 
    fprintf(stderr, "error: parseArgs: maxDepth out of range\n"); 
    exit(4); 
  } 
  return; 
} 

/**** crawl() ****/  
/* 
 * CALLER provides: 
 * @ seedURL: (see above)
 * @ pageDirectory : (see above) 
 * @ maxDepth: (see above)
 *
 * ASSUME: 
 * @ seedURL is a normalized internal seed URL 
 * @ pageDirectory is already initialized 
 * @ maxDepth is in range 
 * Caller frees any memory passed into crawl 
 *
 * WE DO: 
 * @ all the functionality of crawl as specified in DesignSpecs 
 * @ i.e. pulling webpages and saving them to pageDirectory 
 * !!! free any memory allocated in crawl
 */
static void crawl(char* seedURL, char* pageDirectory, const int maxDepth) 
{ 
  // initializing the hashtable w/ seedURL
  hashtable_t* ht = hashtable_new(200); 
  hashtable_insert(ht, seedURL, "");

  // initializing bag and adding webpage w/ seedURL @ depth = 0
  bag_t* bag = bag_new();  
  webpage_t* webpage = webpage_new(seedURL, 0, NULL); 
  bag_insert(bag, webpage); 

  int docID = 1; // init the docID 

  // pulling webpages from the bag
  webpage_t* page; 

  while ((page = bag_extract(bag)) != NULL) { 
    // save if successfully get HTML
    if (webpage_fetch(page)) {
      logr("Fetched",webpage_getDepth(page), webpage_getURL(page)); // fancy printing
      pagedir_save(page, pageDirectory, docID); 

      // pageScan if not @ maxDepth 
      if (webpage_getDepth(page) < maxDepth) {
        pageScan(page, bag, ht); 
      } 
      docID ++; 

    } 
    webpage_delete(page); // deleting the webpage
  } 
  
  // deleting hashtable, bag 
  hashtable_delete(ht, NULL); 
  bag_delete(bag, NULL); 

  return; 
} 

/**** pageScan() ****/
/*
 * CALLER provides: 
 * @ webpage_t* page : current webpage being scanned
 * @ bag_t* pagesToCrawl : bag 
 * @ hashtable_t* pagesSeen : ht
 *
 * ASSUME: 
 * @ page : NOT NULL; 
 * @ pagesToCrawl : NOT NULL; 
 * @ pagesSeen : NOT NULL; 
 * Caller frees any memory passed into pageScan()
 *
 * WE DO: 
 * @ scan page for any unvisited URLS 
 * @ if unvisited, internal, and can be added to pagesSeen
 * @ init a webpage w/ URL and add to bag 
 * !!! free any alloc memory 
 */ 

static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen)
{ 
  int pos = 0;
  int curDepth = webpage_getDepth(page);  
  char* URL;

  logr("Scanning",curDepth,webpage_getURL(page)); 

  // while there is another URL in the page
  while ((URL = webpage_getNextURL(page, &pos)) != NULL) {
    char* curURL = normalizeURL(URL); 
    // if URL is internal 
    if (isInternalURL(curURL)){ 
      // if haven't visited URL (and can add to ht)
      if (hashtable_insert(pagesSeen, curURL, "")){ 
        logr("Found",curDepth+1,curURL); //fancy printing
        webpage_t* nxtPage = webpage_new(curURL, curDepth+1, NULL); // make a new page; might be an error later
        bag_insert(pagesToCrawl, nxtPage); // insert into bag 
        
        logr("Added",curDepth+1,curURL); //fancy printing 
        //webpage_delete(nxtPage); // mem free  
      } else { 
        logr("IgnDupl",curDepth+1,curURL); // fancy printing 
        free(curURL); 
      }        
    } else{
      logr("IgnExtrn",curDepth+1,curURL); //fancy printing
      free(curURL); 
    }  
    free(URL); // mem free
  }
  return; 
}

/**** logr() ****/
/* CALLER provides: 
 * @ *word : what code did to URL (Fetched, Scanning, Found, Added, IgnExtrn) 
 * @ depth : depth of crawl
 * @ *url : URL in question 
 *
 * WE ASSUME : 
 * @ NO ERRORS w/ what caller provides
 * 
 * WE DO: 
 * @ fancy print statements
 */
static void logr(const char *word, const int depth, const char *url)
{
#ifdef APPTEST
  printf("%2d %*s%9s: %s\n", depth, depth, "", word, url);
#else
  ;
#endif
}


