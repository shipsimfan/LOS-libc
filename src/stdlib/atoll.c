#include <stdlib.h>

long long atoll(const char* str) {
    if (str == NULL)
        return 0;

    long long ret = 0;
    int base = 10;
    long long mult = 1;

    while (*str == ' ')
        str++;

    if (*str == '-') {
        mult = -1;
        str++;
    } else if (*str == '+')
        str++;

    if (*str == '0') {
        str++;

        if (*str == 'x' || *str == 'X')
            base = 16;
        else if (*str == 'o' || *str == 'O')
            base = 8;
        else if (*str == 'b' || *str == 'B')
            base = 2;

        if (base != 10)
            str++;
    }

    char newChar;
    while (*str && *str != '\n') {
        if (*str == ' ' || *str == ',') {
            str++;
            continue;
        }

        switch (base) {
        case 2:
        case 8:
        case 10:
            if (*str < '0' || *str >= '0' + base)
                return ret * mult;

            newChar = *str - '0';
            break;

        case 16:
            if (*str >= '0' && *str <= '9')
                newChar = *str - '0';
            else if (*str >= 'a' && *str <= 'f')
                newChar = *str - 'a' + 10;
            else if (*str >= 'A' && *str <= 'F')
                newChar = *str - 'A' + 10;
            else
                return ret * mult;

            break;
        }

        ret *= base;
        ret += newChar;

        str++;
    }

    return ret * mult;
}