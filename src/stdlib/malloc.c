#include <stdlib.h>

size_t top = 0x100000000000;

void* malloc(size_t size) {
    void* ret = (void*)top;
    top += size;
    return ret;
}