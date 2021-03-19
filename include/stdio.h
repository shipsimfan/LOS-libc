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

#define FILE_FLAG_ERROR 1
#define FILE_FLAG_EOF 2

typedef struct {
    unsigned char type;
    unsigned long long descriptor;
    int flags;
    int unc;
} FILE;

typedef unsigned long long fpos_t;

extern FILE* stdin;
extern FILE* stderr;
extern FILE* stdout;

FILE* fopen(const char* filename, const char* mode);
FILE* freopen(const char* pathname, const char* mode, FILE* stream);
int fclose(FILE* stream);

size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);

int fseek(FILE* stream, long int offset, int origin);
long int ftell(FILE* stream);

int fflush(FILE* stream);

int putchar(int character);
int putc(int character, FILE* stream);
int puts(const char* str);
int fputs(const char* str, FILE* stream);
int fputc(int character, FILE* stream);

int getchar();
int getc(FILE* stream);
int fgetc(FILE* stream);
char* fgets(char* s, int n, FILE* stream);

int ungetc(int c, FILE* stream);

int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
int sprintf(char* s, const char* format, ...);
int vprintf(const char* format, va_list arg);
int vfprintf(FILE* stream, const char* format, va_list arg);
int vsprintf(char* s, const char* format, va_list arg);

int scanf(const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
int sscanf(const char* s, const char* format, ...);

void setbuf(FILE* stream, char* buf);
int setvbuf(FILE* stream, char* buf, int type, size_t size);

void clearerr(FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);

int fgetpos(FILE* stream, fpos_t* pos);
int fsetpos(FILE* stream, fpos_t* pos);

void rewind(FILE* stream);

void perror(const char* s);

#if defined(__cplusplus)
}
#endif

#endif