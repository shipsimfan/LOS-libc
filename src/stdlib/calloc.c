#include <stdlib.h>

#include <string.h>

void* calloc(size_t nelem, size_t elsize) {
    size_t size = nelem * elsize;
    void* ret = malloc(size);
    memset(ret, 0, size);
    return ret;
}