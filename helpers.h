#ifndef HELPERS_H_   /* Include guard */
#define HELPERS_H_

#include "uthash.h"

typedef struct {
    char * word;               /* key */
    uint32_t count;
    UT_hash_handle hh;         /* makes this structure hashable */
} word_count_t;

void remove_nonalpha(char *);

#endif // HELPERS_H_