#include <stdio.h>

int fgetc(FILE* stream) {
    char ret = 0;
    fread(&ret, 1, 1, stream);
    return ret;
}