#include <stdlib.h>

#include <stdio.h>

int system(const char* command) {
    fprintf(stderr, "system() currently not supported!\n");
    return EXIT_FAILURE;
}