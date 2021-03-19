#include <stdio.h>

int fsetpos(FILE* stream, fpos_t* pos) {
    stream->unc = -1;
    return fseek(stream, *pos, SEEK_SET);
}