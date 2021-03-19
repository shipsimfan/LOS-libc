#include <stdio.h>

FILE* freopen(const char* pathname, const char* mode, FILE* stream) {
    if (pathname == NULL || mode == NULL)
        return NULL;

    if (stream != NULL)
        fclose(stream);

    return fopen(pathname, mode);
}