#include <stdlib.h>

#include "defs.h"

Node* head = NULL;

int atexit(void (*function)()) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->function = function;
    newNode->next = head;
    head = newNode;
}