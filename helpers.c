#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "helpers.h"

/*
 * Function: new_word_count
 * ----------------------------
 *   Initializes a new instance of a struct to count a word
 *
 *   word: the word to count
 *   count: initial count of the word
 *
 *   returns: the initialized struct
 */
 
word_count_t* new_word_count(char* word, uint32_t count){
  word_count_t* word_count;
  word_count = malloc(sizeof(word_count_t));
  word_count->word = malloc(strlen(word)+1);
  strcpy(word_count->word, word);
  word_count->count = count;
  return word_count;
}

/*
 * Function: remove_nonalpha
 * ----------------------------
 *   Removes non-alphabetic characters from a given string.
 *
 *   str: the string to process
 *
 *   returns: the processed string
 */

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

/*
 * Function: increase_word_count
 * ----------------------------
 *   Increases the word count for a given word.
 *
 *   word_counters: the hashtable to store the words in
 *   word: the word to increase the count for
 *
 */

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

/*
 * Function: get_word_count
 * ----------------------------
 *   Gets the total count of distinct words.
 *
 *   word_counters: the hashtable, the words are stored in
 *
 *   returns: total count of distinct words
 */

uint32_t get_word_count(word_count_t ** word_counters){
  return HASH_COUNT(*word_counters);
}

/*
 * Function: clear_word_counts
 * ----------------------------
 *   Clears a given hashtable and all its elements.
 *
 *   word_counters: the hashtable to clear
 *
 */

void clear_word_counts(word_count_t ** word_counters){
  word_count_t *current_word, *tmp;

  HASH_ITER(hh, *word_counters, current_word, tmp) {
    HASH_DEL(*word_counters, current_word);
    free(current_word->word);
    free(current_word);
  }
}
