#ifndef _STACK_H_
#define _STACK_H_

#include "word.h"

/*
 * Stack type.
 */
typedef struct {
    word* data;
    int_t size;
    int_t top;
} stack;

/*
 * Creates a new stack with the given size.
 */
stack* stcreate(int size);

/*
 * Pushes the given word on the given stack.
 */
void stpush(stack* s, word w);

/*
 * Pops a word off the given stack.
 */
word stpop(stack* s);

/*
 * Prints the stack (left to right.
 */
void stprint(stack* s);

#endif
