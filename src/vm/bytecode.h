#ifndef _BYTECODE_H_
#define _BYTECODE_H_

/* Memory access */
#define LDC     0x00
#define LOAD    0x01
#define STORE   0x02

/* Arithmetic */
#define ADDI    0x10
#define ADDR    0x11
#define SUBI    0x20
#define SUBR    0x21
#define MULI    0x30
#define MULR    0x31
#define DIVI    0x40
#define DIVR    0x41

/* Type Conversion */
#define ITON    0x50
#define ITOR    0x51
#define RTOI    0x52

/* Logic */
#define NOT     0x70
#define AND     0x71
#define OR      0x72

/* Compare */ 
#define EQI     0x80
#define EQR     0x81
#define LTI     0x82
#define LTR     0x83
#define GTI     0x84
#define GTR     0x85

/* Conditional */
#define IFT     0x90
#define IFF     0x91

/* Flow */
#define GOTO    0xe0
#define FRAME   0xe1
#define INVK    0xe2
#define RET     0xe3
#define RETVAL  0xe4
#define INTRNL  0xe5

/* Objects */
#define SIZE    0xa0
#define NEW     0xa1

/* Exit */
#define EXIT    0xff

/* Internal function codes */
#define READINT     10
#define READREAL    11
#define WRITEINT    20
#define WRITEREAL   21

#endif
