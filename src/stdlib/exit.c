#include <stdlib.h>

#include "../defs.h"
#include "defs.h"

void exit(int status) {
    for (Node* node = head; node; node = node->next)
        node->function();

    SystemCall(SYSTEM_CALL_EXIT, status, 0, 0, 0);
}