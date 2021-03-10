#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int atoi(const char* str);

void free(void* ptr);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);

void exit(int status);
void abort();
int atexit(void (*function)());

char* getenv(const char* name);

#if defined(__cplusplus)
}
#endif

#endif