/* Lisa Samoylov CS50 Spring 2025 */ 
/* `word.c` featuring functions to normalize words */ 

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include"word.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
/* none */

/**************** global types ****************/
/* none */ 

/**************** global functions ****************/
/* see word.h for comments about exported functions */


/**************** local functions ****************/
/* not visible outside this file */
/* none */

/**** word_normalize() ****/
void word_normalize(char* word)
{     
    // go through each char in str
    int len = strlen(word); // getting the length of word
    
    for (int i = 0; i < len; i++) {
        // convert uppercase letters to lowercase
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] += 32; 
        }
    }
}


