#include <stdio.h>

int vprintf(const char* format, va_list arg) { vfprintf(stdout, format, arg); }