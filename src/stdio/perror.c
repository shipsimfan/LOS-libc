#include <stdio.h>

#include <errno.h>
#include <string.h>

void perror(const char* s) {
    if (s != NULL)
        fprintf(stderr, "%s: ", s);

    fprintf(stderr, "%s\n", strerror(errno));
}