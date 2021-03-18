#include <time.h>

#include "../defs.h"

unsigned long long systime() { return SystemCall(SYSTEM_CALL_GET_CURRENT_TIME, 0, 0, 0, 0); }