# Lisa Samoylov CS50 Spring 2025 05/05/25
# Lab4 `/crawler/` ReadMe File

# CRAWLER IDEA
`crawler.c` implements a webpage crawler that given a valid URL (see `../common/webpage.h` for more info on valid URLs), it extracts the HTML from the webpage, stores it in a file in the appropriate page directory. Then it scans the file for more URLS and repeats the process until it hits maxDepth.

# CRAWLER IMPLEMENTATION  
## Data Structures 
* URLS : stored in URL struct (see `../common/webpage.h`)
* Webpages : stored in webpage\_t* struct (see `../common/webpage.h`) 
* bag\_t* pagesSeen : stores webpages that the crawler has seen
* hashtable\_t* pagesToScan : stores URLS of webpages that the crawler has yet to search 

## Algorithm 
Crawler implements a crude bfs/dfs search to scan the webpages. If it sees a webpage that it's already seen, then it ignores the webpage (allowing cycles to be ignored).

## Testing 
`crawler.c` is tested on  
* http://cs50tse.cs.dartmouth.edu/tse/letters/
* http://cs50tse.cs.dartmouth.edu/tse/toscrape/
* http://cs50tse.cs.dartmouth.edu/tse/wikipedia/

* letters: @ maxDepth (to be searched) 0,1,2,10
* toscrape: @ maxDepth 0,1
* wiki: @ maxDepth 0,1

## Makefile
`Makefile` includes the flag `-DAPPTEST` in the `CFLAGS` section, which, when included, includes nicely formatted print statements that indicate what the crawler is doing.  

## Running
Run `./crawler urlToCrawl pageDirectoryToStorePages maxDepth` to run crawler

# FILES 
* -> crawler.c 
* -> .gitignore
* -> Makefile
* -> testing.sh : stores crawler.c tests
* -> testing.out : stores output 
