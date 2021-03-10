#include <stdlib.h>

#include "../defs.h"

void abort() { SystemCall(SYSTEM_CALL_EXIT, EXIT_FAILURE, 0, 0, 0); }