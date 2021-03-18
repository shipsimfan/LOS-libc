#include <stdlib.h>

long strtol(const char* str, char** endptr, int base) {
    if (endptr != NULL)
        *endptr = (char*)str;

    if (str == NULL)
        return 0;

    while (*str == ' ')
        str++;

    long mult = 1;
    if (*str == '-') {
        mult = -1;
        str++;
    } else if (*str == '+')
        str++;

    if (base == 0) {
        base = 10;
        if (*str == '0') {
            base = 8;
            str++;

            if (*str == 'x' || *str == 'X') {
                base = 16;
                str++;
            }
        }
    } else if (base < 2 || base > 36)
        return 0;

    long ret = 0;

    char newChar;
    while (*str && *str != '\n') {
        if (*str == ' ' || *str == ',') {
            str++;
            continue;
        }

        if (base <= 10) {
            if (*str < '0' || *str >= '0' + base) {
                if (endptr != NULL)
                    *endptr = (char*)str;
                return ret * mult;
            }

            newChar = *str - '0';
        } else {
            if (*str >= '0' && *str <= '9')
                newChar = *str - '0';
            else if (*str >= 'a' && *str < 'a' + base - 10)
                newChar = *str - 'a' + 10;
            else if (*str >= 'A' && *str < 'A' + base - 10)
                newChar = *str - 'A' + 10;
            else {
                if (endptr != NULL)
                    *endptr = (char*)str;
                return ret * mult;
            }
        }

        ret *= base;
        ret += newChar;

        str++;
    }

    if (endptr != NULL)
        *endptr = (char*)str;

    return ret * mult;
}