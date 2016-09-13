#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "helpers.h"

word_count_t *word_counts = NULL;


void remove_nonalpha(char *str)
{
    unsigned long i = 0;
    unsigned long j = 0;
    char c;

    while ((c = str[i++]) != '\0')
    {
        if (isalpha(c) || c == ' ')
        {
            str[j++] = c;
        }
    }
    str[j] = '\0';
}

void increase_word_count(char *word){
    word_count_t *word_count;
    HASH_FIND_STR(word_counts, word, word_count);  /* word already in the table? */
    if (word_count == NULL) {
      word_count = (word_count_t*)malloc(sizeof(word_count_t));
      strcpy(word_count->word, word);
      word_count->count = 1;
      HASH_ADD_STR(word_counts, word, word_count);  /* add new word */
    }else{
        word_count->count++;  /* increase word count */
    }
}