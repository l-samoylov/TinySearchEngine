// Lisa Samoylov CS50 Spring 2025
// `pagedir.h` header file 

#ifndef __PAGEDIR_H
#define __PAGEDIR_H 

#include<stdio.h> 
#include<webpage.h>

/**** pagedir_init() ****/
/* CALLER provides:
 * @ char* pageDirectory : a char*
 *
 * ASSUME:
 * @pageDirectory: is a valid pageDirectory
 *
 * WE DO:
 * @ return true : made directory /pageDirectory containing ./crawler
 * @ return false : error init ./crawler
 * !!! free any memory alloced in pagedir_init()
 */
bool pagedir_init(const char* pageDirectory);

/**** pagedir_save() ****/
/* CALLER provides:
 *  ---------------
 * @ webpage_t* page :
 * @ char* pageDirectory :
 * @ int docID :
 *
 * WE DO: 
 * ---------------
 
 * WE ASSUME:
 * ---------------
 * @webpage_t*
 *    - page->html NOT NULL
 *    - page->url NOT NULL
 *    - page->depth
 *    - page DELETED OUTSIDE pagedir_save()
 *
 * EXIT CODES:
 * ---------------
 *  20 : constructed file did not open
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/**** pagedir_validate() ****/
/* CALLER provides:
 * @ char* pageDirectory :
 *
 * WE DO: 
 * Open the pagedirectory/.crawler file for reading 
 * If file opens, then it exists (and we have a valid directory for querier/indexer) (RETURN TRUE)
 * If it doesn't open, then we have an invalid directory (RETURN FALSE) 
 *
 * Avoid any excessive/extra memory leaks
 */

bool pagedir_validate(char* pageDirectory);

/**** pagedir_load() ****/ 
/* CALLER provides: 
*  ----------------
*  @ char* pageDirectory : contains .crawler (?) with crawled files 
*  @ int docID : id of the document we're going to load 
* 
*  WE DO: 
*  ----------------
*  Open the pageDirectory and find the file with docID = const int docID
*  We create a webpage_t* page struct containing the contents of the file 
*  We return the file 
* 
*  WE ASSUME: 
*  ----------------
*  docID is SMALL int; when converted to a string, docID fits in char* arr w/ 100,000 slots 
*/
webpage_t* pagedir_load(char* pageDirectory, const int docID);

/**** pagedir_make_path() ****/
/* CALLER provides: 
*  ----------------
*  WE DO: 
*  ----------------
*  WE ASSUME: 
*  ----------------
*/
char* pagedir_make_path(char* pageDirectory, char* fileName);
 
#endif // __PAGEDIR_H
