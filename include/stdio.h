#ifndef _STDIO_H
#define _STDIO_H 1

#include <stdarg.h>
#include <stddef.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define EOF 0

typedef struct {
    unsigned char type;
    unsigned long long descriptor;
} FILE;

extern FILE* stdin;
extern FILE* stderr;
extern FILE* stdout;

FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);

size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

int fseek(FILE* stream, long int offset, int origin);
long int ftell(FILE* stream);

int fflush(FILE* stream);

int putchar(int character);
int puts(const char* str);
int fputs(const char* str, FILE* stream);
int fputc(int character, FILE* stream);

int fgetc(FILE* stream);

int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
int vfprintf(FILE* stream, const char* format, va_list arg);

int scanf(const char* format, ...);

void setbuf(FILE* stream, char* buf);

#if defined(__cplusplus)
}
#endif

#endif