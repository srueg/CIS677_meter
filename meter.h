#ifndef MAIN_H_   /* Include guard */
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "helpers.h"

int process_file(char *, uint32_t);
void remove_nonalpha(char *);

#endif // MAIN_H_