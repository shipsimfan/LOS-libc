#include <stdlib.h>

void* bsearch(const void* key, const void* base, size_t nel, size_t width, int (*compar)(const void*, const void*)) {
    for (int i = 0; i < nel; i++, base += width)
        if (compar(base, key) == 0)
            return (void*)base;

    return NULL;
}