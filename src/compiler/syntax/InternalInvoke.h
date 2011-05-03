#ifndef _INTERNALINVOKE_H_
#define _INTERNALINVOKE_H_ 

#include "Expr.h" 

class InternalInvoke : public Expr {
public:

    long long func;

    InternalInvoke(int lineNum, long long func);

    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
