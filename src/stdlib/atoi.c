#include <stdlib.h>

int atoi(const char* str) {
    if (str == NULL)
        return 0;

    int ret = 0;
    int base = 10;

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
                return ret;

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
                return ret;

            break;
        }

        ret *= base;
        ret += newChar;

        str++;
    }

    return ret;
}