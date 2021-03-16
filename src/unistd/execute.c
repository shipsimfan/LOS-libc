#include <unistd.h>

#include "../defs.h"

pid_t execute(const char* filepath, const char* argv[], const char* envp[]) { return SystemCall(SYSTEM_CALL_EXECUTE, (uint64_t)filepath, (uint64_t)argv, (uint64_t)envp, 0); }