#include <string.h>

unsigned int strnlen(const char* str, size_t maxsize) {
    const char* s;
    for (s = str; *s && maxsize--; s++)
        ;

    return (unsigned int)(s - str);
}