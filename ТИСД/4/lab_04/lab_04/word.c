#include "word.h"

int input(word_t word)
{
    if (scanf("%s", word) != 1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void output(FILE *f, word_t word)
{
    fprintf(f, "%s", word);
}

void reverse(word_t src, word_t dst)
{
    long len = strlen(src);
    for (long i = len - 1; i >= 0; i--)
        dst[len - i - 1] = src[i];
    dst[len] = '\0';
}
