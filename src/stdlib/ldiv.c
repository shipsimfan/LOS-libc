#include <stdlib.h>

ldiv_t ldiv(long numer, long denom) {
    ldiv_t ret;
    ret.quot = numer / denom;
    ret.rem = numer % denom;
    return ret;
}