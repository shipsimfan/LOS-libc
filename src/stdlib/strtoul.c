#include <stdlib.h>

unsigned long strtoul(const char* restrict str, char** restrict endptr, int base) {
    if (endptr != NULL)
        *endptr = (char*)str;

    if (str == NULL)
        return 0;

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

    unsigned long ret = 0;

    while (*str == ' ')
        str++;

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
                return ret;
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
                return ret;
            }
        }

        ret *= base;
        ret += newChar;

        str++;
    }

    if (endptr != NULL)
        *endptr = (char*)str;

    return ret;
}