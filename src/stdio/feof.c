#include <stdio.h>

int feof(FILE* stream) {
    if (stream == NULL)
        return 0;

    return stream->flags & FILE_FLAG_EOF;
}