#include <string.h>

#include <stdlib.h>

void* memmove(void* s1, const void* s2, size_t n) {
    char* buf = malloc(n);
    const char* str2 = s2;

    for (int i = 0; i < n; i++)
        buf[i] = str2[i];

    char* str1 = s1;
    for (int i = 0; i < n; i++)
        str1[i] = buf[i];

    return s1;
}