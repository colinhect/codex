#ifndef _MACHINE_H_
#define _MACHINE_H_

#include "types.h"

/*
 * Executes the given array of bytecode from the begining.
 */
void execute(byte_t* code, int_t debug);

#endif
