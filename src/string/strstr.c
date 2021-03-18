#include <string.h>

char* strstr(const char* s1, const char* s2) {
    size_t s2Len = strlen(s2);
    while (*s1) {
        if (memcmp(s1, s2, s2Len) == 0)
            return (char*)s1;

        s1++;
    }

    return NULL;
}