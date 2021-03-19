#include <stdio.h>

int ferror(FILE* stream) {
    if (stream == NULL)
        return 0;

    return stream->flags & FILE_FLAG_ERROR;
}