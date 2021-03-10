#include <stdio.h>

#include "../defs.h"

long int ftell(FILE* stream) {
    switch (stream->type) {
    case FILE_TYPE_FILE:
        return SystemCall(SYSTEM_CALL_FILE_TELL, stream->descriptor, 0, 0, 0);

    default:
        return 0;
    }
}