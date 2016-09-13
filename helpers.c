#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "helpers.h"

word_count_t *fuu = NULL;

word_count_t* new_word_count(char* word, uint32_t count){
    word_count_t* word_count;
    word_count = malloc(sizeof(word_count_t));
    word_count->word = malloc(strlen(word)+1);
    strcpy(word_count->word, word);
    word_count->count = count;
    return word_count;
}


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

void increase_word_count(word_count_t ** word_counters, char *word){
    word_count_t *word_count;
    HASH_FIND_STR(*word_counters, word, word_count);  /* word already in the table? */
    if (word_count == NULL) {
        word_count = new_word_count(word, 1);
        HASH_ADD_KEYPTR(hh, *word_counters, word_count->word, strlen(word_count->word), word_count);
    }else{
        word_count->count++;  /* increase word count */
    }
}

void print_word_counts(word_count_t ** word_counters) {
    word_count_t *w;

    for(w = *word_counters; w != NULL; w = w->hh.next) {
        printf("word %s: %d\n", w->word, w->count);
    }
}

uint32_t get_word_count(word_count_t ** word_counters){
    return HASH_COUNT(*word_counters);
}

void clear_word_counts(word_count_t ** word_counters){

}
