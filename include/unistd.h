#ifndef _UNISTD_H
#define _UNISTD_H 1

#if defined(__cplusplus)
extern "C" {
#endif

typedef unsigned long long pid_t;

pid_t fork();

int execv(const char* path, const char* argv[]);
int execvp(const char* file, const char* argv[]);
int execvpe(const char* file, const char* argv[], const char* envp[]);

pid_t execute(const char* filepath);

int wait(pid_t pid);

#if defined(__cplusplus)
}
#endif

#endif