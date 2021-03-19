#ifndef _UNISTD_H
#define _UNISTD_H 1

#if defined(__cplusplus)
extern "C" {
#endif

#define DIRENT_TYPE_FILE 0
#define DIRENT_TYPE_DIRECTORY 1

#define DIRENT_FLAG_READ_ONLY 1
#define DIRENT_FLAG_HIDDEN 2

typedef long long ssize_t;
typedef __SIZE_TYPE__ size_t;
typedef unsigned long long pid_t;

typedef struct {
    char name[128];
    unsigned char type;
    unsigned long long size;
    unsigned long long flags;
} dirent_t;

extern char** environ;
extern int environSize;

char* getenv(const char* name);
int setenv(const char* name, const char* value, int overwrite);

// Only here for libgcc, will remove when no longer reliant on gcc
// For now, simply do not use
pid_t fork();
int execv(const char* path, const char* argv[]);
int execvp(const char* file, const char* argv[]);
int execvpe(const char* file, const char* argv[], const char* envp[]);

// Instead use this if you want to create a new process
pid_t execute(const char* filepath, const char* argv[], const char* envp[]);

int wait(pid_t pid);

int getcwd(char* buf, unsigned long long size);
int setcwd(const char* path);
dirent_t* getdirent(unsigned long long* num);

ssize_t write(int fildes, const void* buf, size_t nbyte);

#if defined(__cplusplus)
}
#endif

#endif