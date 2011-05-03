#ifndef _FILE_H_
#define _FILE_H_

#include "types.h"

/*
 * Loads a Codex executable bytecode returning an array of bytecode.
 */
byte_t* load_bytecode(const char* filename);

/*
 * Saves the bytecode in the given array to a file.
 */
int save_bytecode(const char* filename, byte_t* code, int_t len);

#endif
