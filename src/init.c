#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "defs.h"

FILE* stdout;
FILE* stderr;
FILE* stdin;

char** environ;
int environSize;

void initializeStandardLibrary(char* envp[]) {
    environ = envp;
    environSize = 1;

    while (*envp) {
        environSize++;
        envp++;
    }

    stdout = malloc(sizeof(FILE));
    stderr = malloc(sizeof(FILE));
    stdin = malloc(sizeof(FILE));

    stdout->type = FILE_TYPE_DEVICE;
    stdout->descriptor = 0;

    stderr->type = FILE_TYPE_DEVICE;
    stderr->descriptor = 0;

    stdin->type = FILE_TYPE_DEVICE;
    stdin->descriptor = 1;
}