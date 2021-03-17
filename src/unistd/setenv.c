#include <unistd.h>

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

int setenv(const char* name, const char* value, int overwrite) {
    char* env = getenv(name);

    if (env == NULL) {
        int newEnv = environSize - 1;
        environSize++;

        char** newEnviron = malloc(sizeof(char*) * environSize);
        memcpy(newEnviron, environ, sizeof(char*) * (environSize - 1));

        char* newEntry = malloc(strlen(name) + strlen(value) + 2);
        strcpy(newEntry, name);
        strcat(newEntry, "=");
        strcat(newEntry, value);

        newEnviron[newEnv] = newEntry;
        newEnviron[newEnv + 1] = NULL;

        free(environ);
        environ = newEnviron;
    } else {
        env -= strlen(name) + 1;

        int i;
        while (environ[i] != env)
            i++;

        char* newEntry = malloc(strlen(name) + strlen(value) + 2);
        strcpy(newEntry, name);
        strcat(newEntry, "=");
        strcat(newEntry, value);

        free(environ[i]);
        environ[i] = newEntry;
    }

    return 0;
}