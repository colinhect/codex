#include "machine.h"

#include "thread.h"

#include <stdlib.h>

void execute(byte_t* code, int_t debug) {
    word* heap = (word*)malloc(sizeof(word) * 4096);
    
    thread* th = thcreate();

    while(thexec(th, heap, code, debug))
        ;
    
    free(th->st->data);
    free(th->st);
    free(th);

    free(heap);
}
