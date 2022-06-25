#include <string.h>
#include <ctype.h>
#include "string_t.h"

char *my_fgets(string_t str, FILE *f)
{
    char buf[STR_LEN_MAX + 1];
    if (!fgets(buf, STR_LEN_MAX + 1, f))
        return NULL;
    if ((strlen(buf) >= STR_LEN_MAX) && buf[STR_LEN_MAX - 1] != '\n')
        return NULL;
    
    char *pos = strrchr(buf, '\n');
    if (pos)
        *pos = '\0';
    strcpy(str, buf);
    return str;
}

int is_number(string_t s)
{
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++)
        if (!isdigit(s[i]))
            return 0;
    return 1;
}

int char_to_int(char c)
{
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            break;
    }
    return -1;
}

int get_index(const char *str, int c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return i;
        i++;
    }
    return  -1;
}
