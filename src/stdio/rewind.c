#include <stdio.h>

void rewind(FILE* stream) {
    stream->unc = -1;
    fseek(stream, 0, SEEK_SET);
    stream->flags &= ~(FILE_FLAG_ERROR);
}