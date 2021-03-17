#include <unistd.h>

#include <string.h>

char* getenv(const char* name) {
    char** env = environ;
    while (*env) {
        int correct = 1;
        int i;
        for (i = 0; (*env)[i] && (*env)[i] != '=' && name[i]; i++) {
            if (name[i] != (*env)[i]) {
                correct = 0;
                break;
            }
        }

        if (!correct) {
            env++;
            continue;
        }

        if ((*env)[i] != '=' && (*env)[i] != name[i]) {
            env++;
            continue;
        }

        if ((*env)[i] == 0)
            return *env + i;

        return *env + i + 1;
    }

    return NULL;
}