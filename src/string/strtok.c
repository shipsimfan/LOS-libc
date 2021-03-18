#include <string.h>

#include "defs.h"

char* strtok(char* s, const char* sep) {
    if (s != NULL) {
        strtokState = NULL;

        size_t i;
        int validChar = 1;
        for (i = 0; s[i]; i++) {
            validChar = 0;
            for (size_t j = 0; sep[j]; j++) {
                if (s[i] == sep[j]) {
                    validChar = 1;
                    break;
                }
            }

            if (!validChar)
                break;
        }

        if (validChar)
            return NULL;

        strtokState = s + i;
    }

    if (strtokState == NULL)
        return NULL;

    char* ret = strtokState;

    while (*strtokState) {
        for (size_t i = 0; sep[i]; i++) {
            if (*strtokState == sep[i]) {
                *strtokState = 0;
                strtokState++;
                return ret;
            }
        }
    }

    strtokState = NULL;
    return NULL;
}