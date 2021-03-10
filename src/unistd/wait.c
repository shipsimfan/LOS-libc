#include <unistd.h>

#include "../defs.h"

int wait(pid_t pid) { return SystemCall(SYSTEM_CALL_WAIT, pid, 0, 0, 0); }