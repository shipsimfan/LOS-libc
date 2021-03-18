#include <stdlib.h>

#include <string.h>

long double strtold(const char* str, char** endptr) {
    if (endptr != NULL)
        *endptr = (char*)str;

    if (str == NULL)
        return 0;

    while (*str == ' ')
        str++;

    long double mult = 1;
    if (*str == '-') {
        mult = -1;
        str++;
    } else if (*str == '+')
        str++;

    long double ret = 0;

    while (*str && *str != '\n' && *str != '.') {
        if (*str == ' ' || *str == ',') {
            str++;
            continue;
        }

        if (*str < '0' || *str > '9') {
            if (endptr != NULL)
                *endptr = (char*)str;
            return ret * mult;
        }

        ret *= 10;
        ret += *str - '0';

        str++;
    }

    if (*str == '.') {
        str++;
        long double div = 0.1F;
        while (*str && *str != '\n') {
            if (*str == ' ' || *str == ',') {
                str++;
                continue;
            }

            if (*str < '0' || *str > '9') {
                if (endptr != NULL)
                    *endptr = (char*)str;
                return ret * mult;
            }

            ret += (*str - '0') * div;
            div /= 10.0F;

            str++;
        }
    }

    if (endptr != NULL)
        *endptr = (char*)str;

    return ret * mult;
}