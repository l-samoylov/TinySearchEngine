# Lisa Samoylov CS50 Spring 2025 05/05/25
# Lab4/Lab5 `/common/` ReadMe File

`common` contains modules to support Crawler, Indexer, and Querier. 

# PAGEDIR
`pagedir.c` implements helper functions (like initializing a crawler in a directory and saving html from pages) used in `../crawler/crawler.c`. See `pagedir.h` for more information. 

# WORD 
`word.c` implements helper functions like word normalization. See `word.h` for more information. 

## KNOWN ERRORS 
* word_normalize doesn't normalize all the characters in a word. Sometimes the last word is missed. 
(E.g. TSE turns into tsE, eniac becomes eniaC)

# INDEX
`index.c` implements the `index` struct. See `index.h` for more information.  

# FILES 
* -> pagedir.c
* -> pagedir.h
* -> word.c
* -> word.h
* -> index.c
* -> index.h
* -> .gitignore
* -> Makefile
