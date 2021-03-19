#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "../defs.h"

#define OPEN_READ 1
#define OPEN_WRITE 2

FILE* fopen(const char* filename, const char* mode) {
    int flags = 0;
    size_t modeLen = strlen(mode);
    if (modeLen > 0) {
        if (mode[0] == 'r')
            flags |= OPEN_READ;
        else if (mode[0] == 'w' || mode[0] == 'a')
            flags |= OPEN_WRITE;

        if (modeLen > 1) {
            if (mode[1] == '+')
                flags |= OPEN_READ | OPEN_WRITE;
        }
    }

    int descriptor = SystemCall(SYSTEM_CALL_FILE_OPEN, (uint64_t)filename, flags, 0, 0);
    if (descriptor < 0)
        return NULL;

    FILE* file = (FILE*)malloc(sizeof(FILE));
    file->type = FILE_TYPE_FILE;
    file->descriptor = descriptor;
    file->flags = 0;
    file->unc = -1;

    return file;
}