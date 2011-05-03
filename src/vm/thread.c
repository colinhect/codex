#include "bytecode.h"
#include "thread.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

thread* thcreate() {
    thread* th = (thread*)malloc(sizeof(thread));
    th->st = stcreate(512);
    th->pc = th->bp = 0;
    th->vp = 3;

    return th;
}

int thexec(thread* th, word* heap, byte_t* code, int_t debug) {
    byte_t op = code[th->pc++];
    word p;

    if (debug) {
        printf("--------------------------------------\n");
        thprint(th);
        printf("\nnext: ");
    }

    switch(op) {

        /* Memory access operations. */
        case LDC: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                stpush(th->st, p);

                if (debug) printf("ldc %lld\n", p.i);
            } break;
        case LOAD: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                stpush(th->st, th->st->data[th->vp+p.i]);
                
                if (debug) printf("load %lld\n", p.i);
            } break;
        case STORE: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                th->st->data[th->vp+p.i] = stpop(th->st);
                
                if (debug) printf("store %lld\n", p.i);
            } break;

        /* Arithmetic operations */
        case ADDI: {
                stpush(th->st, (word)(stpop(th->st).i + stpop(th->st).i));
                
                if (debug) printf("addi\n");
            } break;
        case ADDR: {
                stpush(th->st, (word)(stpop(th->st).r + stpop(th->st).r));
                
                if (debug) printf("addr\n");
            } break;
        case SUBI: {
                int_t r = stpop(th->st).i;
                int_t l = stpop(th->st).i;
                stpush(th->st, (word)(l - r));
                
                if (debug) printf("subi\n");
            } break;
        case SUBR: {
                real_t r = stpop(th->st).r;
                real_t l = stpop(th->st).r;
                stpush(th->st, (word)(l - r));
                
                if (debug) printf("subr\n");
            } break;
        case MULI: {
                stpush(th->st, (word)(stpop(th->st).i * stpop(th->st).i));
                    
                if (debug) printf("muli\n");
            } break;
        case MULR: {
                stpush(th->st, (word)(stpop(th->st).r * stpop(th->st).r));
                
                if (debug) printf("mulr\n");
            } break;
        case DIVI: {
                int_t r = stpop(th->st).i;
                int_t l = stpop(th->st).i;
                stpush(th->st, (word)(l / r));
                
                if (debug) printf("divi\n");
            } break;
        case DIVR: {
                real_t r = stpop(th->st).r;
                real_t l = stpop(th->st).r;
                stpush(th->st, (word)(l / r));
                
                if (debug) printf("divr\n");
            } break;

        /* Type Conversion */
        case ITON: {
                if (th->st->data[th->st->top-1].i < 0) {
                    printf("Exception: Cannot convert negative Int to a Nat\n");
                    return 0;    
                }

                if (debug) printf("iton\n");
            } break;
        case ITOR: {
                word aux;
                aux.r = (real_t)stpop(th->st).i;
                
                stpush(th->st, aux); 
 
                if (debug) printf("itor\n");
            } break;
        case RTOI: {
                word aux;
                aux.i = (int_t)stpop(th->st).r;
                
                stpush(th->st, aux); 
 
                if (debug) printf("rtoi\n");
            } break;

        /* Logic */
        case NOT: {
                if (stpop(th->st).i)
                    stpush(th->st, (word)((int_t)0));
                else
                    stpush(th->st, (word)((int_t)1));
                
                if (debug) printf("not\n");
            } break;
        case AND: {
                if (stpop(th->st).i && stpop(th->st).i)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("and\n");
            } break;
        case OR: {
                if (stpop(th->st).i || stpop(th->st).i)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("or\n");
            } break;

        /* Compare */
        case EQI: {
                int_t r = stpop(th->st).i;
                int_t l = stpop(th->st).i;
 
                if(l == r)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("eqi\n");
            } break;
        case EQR: {
                real_t r = stpop(th->st).r;
                real_t l = stpop(th->st).r;
 
                if(l == r)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("eqr\n");
            } break;
        case LTI: {
                int_t r = stpop(th->st).i;
                int_t l = stpop(th->st).i;
 
                if(l < r)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("lti\n");
            } break;
        case LTR: {
                real_t r = stpop(th->st).r;
                real_t l = stpop(th->st).r;
 
                if(l < r)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("ltr\n");
            } break;
        case GTI: {
                int_t r = stpop(th->st).i;
                int_t l = stpop(th->st).i;
 
                if(l > r)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("gti\n");
            } break;
        case GTR: {
                real_t r = stpop(th->st).r;
                real_t l = stpop(th->st).r;
 
                if(l > r)
                    stpush(th->st, (word)((int_t)1));
                else
                    stpush(th->st, (word)((int_t)0));
                
                if (debug) printf("gtr\n");
            } break;
                
        /* Conditional jumps */
        case IFT: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;

                if(stpop(th->st).i)
                    th->pc = p.i;
                
                if (debug) printf("ift %lld\n", p.i);
            } break;
        case IFF: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;

                if(!stpop(th->st).i)
                    th->pc = p.i;
                
                if (debug) printf("iff %lld\n", p.i);
            } break;
        
        /* Flow */
        case GOTO: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                th->pc = p.i;
                
                if (debug) printf("goto %lld\n", p.i);
            } break;
        case FRAME: {
                word aux;
                
                /* Don't know return address until call instruction. */
                aux.i = -1;
                stpush(th->st, aux);
                
                /* Push base pointer. */
                aux.i = th->bp;
                stpush(th->st, aux);

                /* Push var pointer. */
                aux.i = th->vp;
                stpush(th->st, aux);

                /* Set new base pointer. */
                th->bp = th->st->top-3;
                
                if (debug) printf("frame\n");
            } break;
        case INVK: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                th->st->data[th->bp].i = th->pc;
                th->pc = p.i;
                th->vp = th->bp+3;

                if (debug) printf("invk %lld\n", p.i);
            } break;
        case RET: {
                th->st->top = th->bp;

                th->pc = th->st->data[th->st->top].i;
                th->bp = th->st->data[th->st->top+1].i;
                th->vp = th->st->data[th->st->top+2].i;
                
                if (debug) printf("ret\n");
            } break;
        case RETVAL: {
                word ret = stpop(th->st);
                th->st->top = th->bp;

                th->pc = th->st->data[th->st->top].i;
                th->bp = th->st->data[th->st->top+1].i;
                th->vp = th->st->data[th->st->top+2].i;

                /* Push return value */
                stpush(th->st, ret);
                
                if (debug) printf("ret\n");
            } break;
        case INTRNL: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                
                if (!thexecintrnl(th, heap, code, p.i))
                    return 0;
            } break;

        /* Objects */
        case NEW: {
                memcpy(&p, &code[th->pc], 8); th->pc += 8;
                memcpy(&p, &code[p.i+1], 8);
                
            } break;        

        /* Exit */
        case EXIT:
            printf("returning %lld\n", stpop(th->st).i);
            return 0;
            break;

        default:
            printf("Exception: Invalid instruction\n");
            return 0;
            break;
    }
 
    if (debug) {
        getchar();
    }

    return 1;
} 

int thexecintrnl(thread* th, word* heap, byte_t* code, int_t func) {
    switch (func) {
        case READINT: {
            char c, buff[13];
            int result;
            int valid = fgets(buff, sizeof buff, stdin) && !isspace(*buff) && sscanf(buff, "%d%c", &result, &c) == 2 && (c == '\n' || c == '\0');

            if (!valid) {
                printf("Exception: Invalid Int\n");
                return 0;
            }
            
            word val;
            val.i = result;
            
            stpush(th->st, val);

            } break;
        case WRITEINT: {
                printf("%lld\n", stpop(th->st).i);
            }
    }

    return 1;
}

void thprint(thread* th) {
    printf("pc = %lld, bp = %lld\n", th->pc, th->bp);
    stprint(th->st);
}
