#include <stdlib.h>

lldiv_t lldiv(long long numer, long long denom) {
    lldiv_t ret;
    ret.quot = numer / denom;
    ret.rem = numer % denom;
    return ret;
}