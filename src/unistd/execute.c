#include <unistd.h>

#include "../defs.h"

pid_t execute(const char* filepath) { return SystemCall(SYSTEM_CALL_EXECUTE, (uint64_t)filepath, 0, 0, 0); }