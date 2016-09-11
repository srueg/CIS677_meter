#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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