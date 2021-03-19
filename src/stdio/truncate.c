#include <stdio.h>

#include "../defs.h"

int truncate(FILE* file, long newSize) {
    if (file == NULL)
        return -1;

    if (file->type != FILE_TYPE_FILE)
        return -1;

    return SystemCall(SYSTEM_CALL_TRUNCATE, file->descriptor, newSize, 0, 0);
}