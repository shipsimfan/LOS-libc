#include <string.h>

char* strncat(char* s1, const char* s2, size_t n) {
    char* ptr = s1 + strlen(s1);
    size_t i;
    for (i = 0; i < n && s2[i]; i++)
        ptr[i] = s2[i];

    if (i < n)
        ptr[i] = 0;

    return s1;
}