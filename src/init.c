#include <stdio.h>
#include <stdlib.h>

#include "defs.h"

FILE* stdout;
FILE* stderr;
FILE* stdin;

void initializeStandardLibrary() {
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