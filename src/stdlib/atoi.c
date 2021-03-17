#include <stdlib.h>

int atoi(const char* str) {
    int ret = 0;

    while (*str) {
        if (*str < '0' || *str > '9')
            break;

        ret *= 10;
        ret += *str - '0';

        str++;
    }

    return ret;
}