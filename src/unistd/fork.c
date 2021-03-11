#include <unistd.h>

#include "../defs.h"

pid_t fork() { return SystemCall(SYSTEM_CALL_FORK, 0, 0, 0, 0); }