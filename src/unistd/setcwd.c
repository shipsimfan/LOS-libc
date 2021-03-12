#include <unistd.h>

#include "../defs.h"

int setcwd(const char* path) { return SystemCall(SYSTEM_CALL_CHANGE_DIRECTORY, (uint64_t)path, 0, 0, 0); }