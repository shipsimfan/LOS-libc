#include <stdio.h>

int fprintf(FILE* stream, const char* format, ...) {
    va_list arg;
    va_start(arg, format);
    const int ret = vfprintf(stream, format, arg);
    va_end(arg);
    return ret;
}