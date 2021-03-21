#include <string.h>

void* memset(void* ptr, int value, size_t num) {
    char* p = ptr;
    for (size_t i = 0; i < num; i++)
        p[i] = value;

    return ptr;
}