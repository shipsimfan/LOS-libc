#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t;

int atoi(const char* str);

void free(void* ptr);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);

void exit(int status);
void abort();
int atexit(void (*function)());

char* getenv(const char* name);

int abs(int i);
long labs(long i);
long long llabs(long long i);

div_t div(int numer, int denom);
ldiv_t ldiv(long numer, long denom);
lldiv_t lldiv(long long numer, long long denom);

int rand();
void srand(unsigned seed);

#if defined(__cplusplus)
}
#endif

#endif