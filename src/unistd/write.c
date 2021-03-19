#include <unistd.h>

#include "../defs.h"

ssize_t write(int fildes, const void* buf, size_t nbyte) { return SystemCall(SYSTEM_CALL_FILE_WRITE, fildes, (uint64_t)buf, nbyte, 0); }