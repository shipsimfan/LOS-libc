#include <stdlib.h>

long labs(long i) {
    if (i < 0)
        return -i;

    return i;
}