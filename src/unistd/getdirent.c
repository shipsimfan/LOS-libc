#include <unistd.h>

#include <stdlib.h>

#include "../defs.h"

dirent_t* getdirent(unsigned long long* num) {
    *num = SystemCall(SYSTEM_CALL_GET_DIR_ENT_NUM, 0, 0, 0, 0);
    dirent_t* dirents = (dirent_t*)malloc(sizeof(dirent_t) * *num);
    SystemCall(SYSTEM_CALL_GET_DIR_ENT, (uint64_t)dirents, sizeof(dirent_t) * *num, 0, 0);
    return dirents;
}