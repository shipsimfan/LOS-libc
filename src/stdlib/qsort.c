#include <stdlib.h>

#define SWAP(a, b, size)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
    do {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
        size_t _size = size;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
        char* _a = a;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        char* _b = b;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  \
        do {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
            char _tmp = *_a;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
            *_a++ = *_b;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
            *_b++ = _tmp;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
        } while (--_size > 0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         \
    } while (0)

#define PUSH(lo, hi) ((void)((top->low = lo), (top->high = hi), top++))
#define POP(lo, hi) ((void)(top--, (lo = top->low), (hi = top->high)))

#define MAX_THRESH 4

#define min(x, y) ((x < y) ? x : y)

typedef struct {
    char* low;
    char* high;
} node_t;

void qsort(void* base, size_t nel, size_t width, int (*compar)(const void*, const void*)) {
    if (nel == 0)
        return;

    const size_t maxThresh = MAX_THRESH * width;

    if (nel > MAX_THRESH) {
        char* low = base;
        char* high = &low[width * (nel - 1)];
        node_t stack[__CHAR_BIT__ * sizeof(size_t)];
        node_t* top = stack;
        PUSH(NULL, NULL);

        while (stack < top) {
            char* leftPtr;
            char* rightPtr;

            char* mid = low + width * ((high - low) / width >> 1);

            if (compar(mid, low) < 0)
                SWAP(mid, low, width);
            if (compar(high, mid) < 0)
                SWAP(high, mid, width);
            else
                goto jumpOver;

            if (compar(mid, low) < 0)
                SWAP(mid, low, width);

        jumpOver:
            leftPtr = low + width;
            rightPtr = high - width;

            do {
                while (compar(leftPtr, mid) < 0)
                    leftPtr += width;

                while (compar(mid, rightPtr) < 0)
                    rightPtr -= width;

                if (leftPtr < rightPtr) {
                    SWAP(leftPtr, rightPtr, width);
                    if (mid == leftPtr)
                        mid = rightPtr;
                    else if (mid == rightPtr)
                        mid = leftPtr;

                    leftPtr += width;
                    rightPtr -= width;
                } else if (leftPtr == rightPtr) {
                    leftPtr += width;
                    rightPtr -= width;
                    break;
                }
            } while (leftPtr <= rightPtr);

            if ((size_t)(rightPtr - low) <= maxThresh) {
                if ((size_t)(high - leftPtr) <= maxThresh)
                    POP(low, high);
                else
                    low = leftPtr;
            } else if ((size_t)(high - leftPtr) <= maxThresh)
                high = rightPtr;
            else if ((rightPtr - low) > (high - leftPtr)) {
                PUSH(low, rightPtr);
                low = leftPtr;
            } else {
                PUSH(leftPtr, high);
                high = rightPtr;
            }
        }
    }

    {
        const char* endPtr = &((char*)base)[width * (nel - 1)];
        char* tmpPtr = base;
        char* thresh = (char*)min(endPtr, (char*)base + maxThresh);
        char* runPtr;

        for (runPtr = tmpPtr + width; runPtr <= thresh; runPtr += width)
            if (compar(runPtr, tmpPtr) < 0)
                tmpPtr = runPtr;

        if (tmpPtr != base)
            SWAP(tmpPtr, base, width);

        runPtr = base + width;
        while ((runPtr += width) <= endPtr) {
            tmpPtr = runPtr - width;
            while (compar(runPtr, tmpPtr) < 0)
                tmpPtr -= width;

            tmpPtr += width;
            if (tmpPtr != runPtr) {
                char* trav;
                trav = runPtr + width;

                while (--trav >= runPtr) {
                    char c = *trav;
                    char* high;
                    char* low;

                    for (high = low = trav; (low -= width) >= tmpPtr; high = low)
                        *high = *low;

                    *high = c;
                }
            }
        }
    }
}