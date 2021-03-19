#include <stdio.h>

#include <stdlib.h>

#include "../defs.h"

FILE* fopen(const char* filename, const char* mode) {
    int descriptor = SystemCall(SYSTEM_CALL_FILE_OPEN, (uint64_t)filename, 0, 0, 0);
    if (descriptor < 0)
        return NULL;

    FILE* file = (FILE*)malloc(sizeof(FILE));
    file->type = FILE_TYPE_FILE;
    file->descriptor = descriptor;
    file->flags = 0;
    file->unc = -1;

    return file;
}