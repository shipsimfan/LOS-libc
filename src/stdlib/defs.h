#ifndef _STDLIB_DEFS_H
#define _STDLIB_DEFS_H 1

typedef struct Node_t {
    struct Node_t* next;
    void (*function)();
} Node;

extern Node* head;

#endif
