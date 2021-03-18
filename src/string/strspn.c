#include <string.h>

size_t strspn(const char* s1, const char* s2) {
    size_t i;

    for (i = 0; s1[i]; i++)
        for (int j = 0; s2[j]; j++)
            if (s1[i] != s2[j])
                return i;

    return i;
}