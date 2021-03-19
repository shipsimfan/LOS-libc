#include <stdio.h>
#include <string.h>

#include "../defs.h"

size_t fread(void* ptr, size_t size, size_t count, FILE* stream) {
    size_t ret;
    size_t inc = 0;

    if (stream->unc != -1) {
        ((unsigned char*)ptr)[0] = stream->unc;
        inc = 1;
        stream->unc = -1;
    }

    switch (stream->type) {
    case FILE_TYPE_DEVICE:
        ret = SystemCall(SYSTEM_CALL_DEVICE_READ_STREAM, stream->descriptor, 0, (uint64_t)ptr, size * count);

    case FILE_TYPE_FILE:
        ret = SystemCall(SYSTEM_CALL_FILE_READ, stream->descriptor, (uint64_t)ptr, size * count, 0);

    default:
        return -1;
    }

    if (ret == ~0)
        stream->flags |= FILE_FLAG_ERROR;

    if (*(char*)(ptr + ret) == 0)
        stream->flags |= FILE_FLAG_EOF;

    return ret + inc;
}