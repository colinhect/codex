#ifndef _WORD_H_
#define _WORD_H_

#include "types.h"

/*
 * Union for word type.
 */
typedef union {
    byte_t  b[8];
    int_t   i;
    real_t  r;
} word;

#endif
