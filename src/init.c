#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "defs.h"
#include "string/defs.h"

FILE* stdout;
FILE* stderr;
FILE* stdin;

char** environ;
int environSize;

char* strtokState;

void initializeStandardLibrary(char* envp[]) {
    environ = envp;
    environSize = 1;

    srand(systime());

    strtokState = NULL;

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