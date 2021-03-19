#include <stdio.h>

char* fgets(char* s, int n, FILE* stream) {
    for (int i = 0; i < n; i++) {
        s[i] = fgetc(stream);
        if (s[i] == '\n' || s[i] == EOF)
            return s;
    }

    return s;
}