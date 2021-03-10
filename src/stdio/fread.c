#include <stdio.h>
#include <string.h>

#include "../defs.h"

size_t fread(void* ptr, size_t size, size_t count, FILE* stream) {
    switch (stream->type) {
    case FILE_TYPE_DEVICE:
        return SystemCall(SYSTEM_CALL_DEVICE_READ_STREAM, stream->descriptor, 0, (uint64_t)ptr, size * count);

    case FILE_TYPE_FILE:
        return SystemCall(SYSTEM_CALL_FILE_READ, stream->descriptor, (uint64_t)ptr, size * count, 0);

    default:
        return -1;
    }
}