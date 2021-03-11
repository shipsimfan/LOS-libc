#ifndef _DEFS_H
#define _DEFS_H

#include <stdint.h>

#define SYSTEM_CALL_EXIT 0
#define SYSTEM_CALL_DEVICE_WRITE_STREAM 1
#define SYSTEM_CALL_DEVICE_READ_STREAM 2
#define SYSTEM_CALL_EXECUTE 3
#define SYSTEM_CALL_WAIT 4
#define SYSTEM_CALL_FILE_OPEN 5
#define SYSTEM_CALL_FILE_CLOSE 6
#define SYSTEM_CALL_FILE_READ 7
#define SYSTEM_CALL_FILE_SEEK 8
#define SYSTEM_CALL_FILE_TELL 9
#define SYSTEM_CALL_FILE_WRITE 10
#define SYSTEM_CALL_FORK 11

#define FILE_TYPE_DEVICE 0
#define FILE_TYPE_FILE 1

uint64_t SystemCall(uint64_t num, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4);

#endif