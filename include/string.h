#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

void* memcpy(void* destination, const void* source, size_t num);
void* memset(void* ptr, int value, size_t num);

size_t strlen(const char* str);
char* strcpy(char* destination, const char* source);
int strcmp(const char* str1, const char* str2);

#if defined(__cplusplus)
}
#endif

#endif