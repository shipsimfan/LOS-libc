#include <stdio.h>

int ungetc(int c, FILE* stream) {
    stream->unc = c;
    return 0;
}