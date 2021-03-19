#include <stdio.h>

#include <errno.h>

int fgetpos(FILE* stream, fpos_t* pos) {
    if (stream == NULL) {
        errno = EBADF;
        return 1;
    }

    *pos = ftell(stream);
    return 0;
}