#ifndef _THREAD_H_
#define _THREAD_H_

#include "stack.h"
#include "word.h"

/*
 * Thread type.
 */
typedef struct {
    stack* st;
    int_t pc;
    int_t bp;
    int_t vp;
} thread;

/*
 * Creates a new thread.
 */
thread* thcreate();

/*
 * Executes one cycle on the given code.
 */
int thexec(thread* th, word* heap, byte_t* code, int_t debug);

/*
 * Executes internal function.
 */
int thexecintrnl(thread* th, word* heap, byte_t* code, int_t func);

/*
 * Prints the thread to standard output.
 */
void thprint(thread* th);

#endif
