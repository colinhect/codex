#ifndef _HEAP_H_
#define _HEAP_H_

#include "word.h"

/*
 * Heap type.
 */
typedef struct {
    word* data;
    int_t size;
    int_t top;
} heap;

/*
 * Creates a new heap with the given size.
 */
heap* hpcreate(int size);

#endif
