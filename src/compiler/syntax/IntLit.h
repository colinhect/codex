#ifndef _INTLIT_H_
#define _INTLIT_H_

#include "Expr.h"

class IntLit : public Expr {
public:

    long long value;

    IntLit(int lineNum, long long value);

    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
