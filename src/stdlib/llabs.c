#include <stdlib.h>

long long llabs(long long i) {
    if (i < 0)
        return -i;

    return i;
}