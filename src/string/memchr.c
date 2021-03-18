#include <string.h>

void* memchr(const void* s, int c, size_t n) {
    const unsigned char* ptr = s;
    unsigned char ch = c;

    for (size_t i = 0; i < n; i++)
        if (ptr[i] == ch)
            return (void*)s + i;

    return NULL;
}