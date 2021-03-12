#include <stdio.h>

int puts(const char* str) {
    int ret = fputs(str, stdout);
    fputc('\n', stdout);
    return ret + 1;
}