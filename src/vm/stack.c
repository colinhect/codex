#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

stack* stcreate(int size) {
    stack* s = (stack*)malloc(sizeof(stack));
    s->data = (word*)malloc(sizeof(word) * size);
    s->size = size;
    s->top = 0;

    return s;
}

void stpush(stack* s, word w) {
    s->data[s->top++] = w;
}

word stpop(stack* s) {
    return s->data[--s->top];
}

void stprint(stack* s) {
    int_t i;

    printf("----+-----+\n");
    for (i = 0; i < s->top; ++i) {
        printf("%3lld | %3lld |\n", i, s->data[i].i);
    }
    printf("----+-----+\n");

}
