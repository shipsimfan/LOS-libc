#include <stdio.h>

void clearerr(FILE* stream) {
    if (stream != NULL)
        stream->flags = 0;
}