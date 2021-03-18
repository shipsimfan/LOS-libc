#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

void* memchr(const void* s, int c, size_t n);
int memcmp(const void* str1, const void* str2, size_t n);
void* memcpy(void* destination, const void* source, size_t num);
void* memmove(void* s1, const void* s2, size_t n);
void* memset(void* ptr, int value, size_t num);

char* strcat(char* destination, const char* source);
char* strchr(const char* s, int c);
int strcmp(const char* str1, const char* str2);
int strcoll(const char* s1, const char* s2);
size_t strcspn(const char* s1, const char* s2);
char* strerror(int errnum);
char* strcpy(char* destination, const char* source);
size_t strcspn(const char* s1, const char* s2);
size_t strlen(const char* str);
char* strncat(char* s1, const char* s2, size_t n);
int strncmp(const char* s1, const char* s2, size_t n);
char* strncpy(char* s1, const char* s2, size_t n);
unsigned int strnlen(const char* str, size_t maxsize);
char* strtok(char* s, const char* sep);
char* strpbrk(const char* s1, const char* s2);
char* strrchr(const char* s, int c);
char* strstr(const char* s1, const char* s2);
size_t strxfrm(char* s1, const char* s2, size_t n);

#if defined(__cplusplus)
}
#endif

#endif