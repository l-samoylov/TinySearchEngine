# Lisa Samoylov CS50 Spring 2025 
# `indexer` Implementation Spec
--- 

This implementation spec is modeled off of `crawler.c`'s implementation spec. Here we outline the following: 
* Data Structures Used
* Control Flow 
* Modules Created
* Function Prototypes
* Error Handling 
* Testing 

## Data Structures 
--- 
We create a new `struct index` to store the inverse-indexed words. `index` contains a `struct hashtable` of (word, (docID, count)) pairs, where (docID, count) captures the number of times word appears in the document with that docID. The set of (docID, count) pairs is contained in a `struct counterset`. 

We additionally utilize the `struct webpage` in the `libcs50` library. 

## Control Flow 
---
The indexer is implemented in `indexer.c` with the following functions

### main : 
---


### indexBuild : 
---

### validateArgs : 
---

### indexPage :
---

## Function Prototypes : 
--- 
### indexer.c :  
---
Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in indexer.c and is not repeated here.

`
int main(int argc, char* argv[]);
static void validateArgs(int argc, char* argv[]);
static void indexBuild(char* pageDirectory);
static void indexPage(webpage_t* page, index_t* index, int docID); 
`

### index.c : 
---
Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in index.h and is not repeated here.

`
typedef struct index;
index_t* index_new(void);
bool index_insert(index_t* idx, const char* word, const int docID); 
void index_print(index_t* idx, char* indexFilePath);
void index_delete(index_t* idx);
index_t* index_load(char* indexFilePath); 
`


### pagedir.c : 
---
Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in pagedir.h and is not repeated here.

`
bool pagedir_validate(char* pageDirectory); 
webpage_t* pagedir_load(char* pageDirectory, const int docID);
char* pagedir_make_path(char* pageDirectory, char* fileName); 

`

### word.c : 
---
Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in word.h and is not repeated here.

`
void word_normalize(char* word);
`

### indextest.c : 
--- 
Detailed descriptions of each function's interface is provided as a paragraph comment prior to each function's implementation in indextest.c and is not repeated here.

`
`

## Modules 
--- 
We created an

We leveraged the modules in the `libcs50` and `common` libraries. 
## Function Prototypes 
--- 

## Testing 
--- 

