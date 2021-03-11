#include <unistd.h>

#include "../defs.h"

int getcwd(char* buf, unsigned long long size) { return SystemCall(SYSTEM_CALL_GET_CWD, (uint64_t)buf, size, 0, 0); }