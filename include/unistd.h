#ifndef _UNISTD_H
#define _UNISTD_H 1

#if defined(__cplusplus)
extern "C" {
#endif

#define DIRENT_TYPE_FILE 0
#define DIRENT_TYPE_DIRECTORY 1

typedef unsigned long long pid_t;

typedef struct {
    char name[128];
    unsigned char type;
    unsigned long long size;
} dirent_t;

// Only here for libgcc, will remove when no longer reliant on gcc
// For now, simply do not use
pid_t fork();
int execv(const char* path, const char* argv[]);
int execvp(const char* file, const char* argv[]);
int execvpe(const char* file, const char* argv[], const char* envp[]);

// Instead use this if you want to create a new process
pid_t execute(const char* filepath);

int wait(pid_t pid);

int getcwd(char* buf, unsigned long long size);
int setcwd(const char* path);
dirent_t* getdirent(unsigned long long* num);

#if defined(__cplusplus)
}
#endif

#endif