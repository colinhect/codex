#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

heap* hpcreate(int size) {
    heap* h = (heap*)malloc(sizeof(heap));
    h->data = (word*)malloc(sizeof(word) * size);
    h->size = size;
    h->top = 0;

    return h;
}

