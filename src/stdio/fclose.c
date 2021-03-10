#include <stdio.h>

#include <stdlib.h>

#include "../defs.h"

int fclose(FILE* stream) {
    switch (stream->type) {
    case FILE_TYPE_FILE:
        SystemCall(SYSTEM_CALL_FILE_CLOSE, stream->descriptor, 0, 0, 0);
        free(stream);
        return 0;

    default:
        return -1;
    }
}