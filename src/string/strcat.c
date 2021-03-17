#include <string.h>

char* strcat(char* destination, const char* source) {
    char* ptr = destination + strlen(destination);
    while (*source)
        *ptr++ = *source++;

    *ptr = 0;

    return destination;
}