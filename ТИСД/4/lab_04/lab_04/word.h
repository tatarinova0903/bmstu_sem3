#ifndef word_h
#define word_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN_MAX 21

typedef char word_t[WORD_LEN_MAX];

int input(word_t word);
void output(FILE *f, word_t word);
void reverse(word_t src, word_t dst);

#endif
