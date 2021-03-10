#include <string.h>

void* memcpy(void* destination, const void* source, size_t num) {
    for (size_t i = 0; i < num; i++)
        ((char*)destination)[i] = ((const char*)source)[i];

    return destination;
}