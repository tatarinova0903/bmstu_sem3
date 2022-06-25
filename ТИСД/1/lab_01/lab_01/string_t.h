#ifndef string_t_h
#define string_t_h

#include <stdio.h>

#define STR_LEN_MAX 38
#define WORD_LEN_MAX 30
#define WORDS_COUNT_MAX 2

typedef char string_t[STR_LEN_MAX];
typedef string_t strings_t[WORDS_COUNT_MAX];

char *my_fgets(string_t s, FILE *f);
int is_number(string_t s);
int char_to_int(char c);
int get_index(const char *str, int c);

#endif
