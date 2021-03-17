#include <string.h>

char* strcpy(char* destination, const char* source) {
    char* ptr = destination;
    while (*source) {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = 0;

    return ptr;
}
