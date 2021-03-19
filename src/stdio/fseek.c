#include <stdio.h>

#include "../defs.h"

int fseek(FILE* stream, long int offset, int origin) {
    stream->unc = 0;
    switch (stream->type) {
    case FILE_TYPE_FILE:
        return SystemCall(SYSTEM_CALL_FILE_SEEK, stream->descriptor, offset, origin, 0);

    default:
        return 0;
    }
}