#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

int atoi(const char* str);

void free(void* ptr);
void* malloc(size_t size);

void abort();
int atexit(void (*function)());

char* getenv(const char* name);

#if defined(__cplusplus)
}
#endif

#endif