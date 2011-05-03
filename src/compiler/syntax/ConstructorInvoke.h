#ifndef _CONSTRUCTORINVOKE_H_
#define _CONSTRUCTORINVOKE_H_

#include "Expr.h"

#include "Exprs.h"
#include "UpperIdent.h"

class ConstructorInvoke : public Expr {
public:

    UpperIdent* ident;
    Exprs* args;

    ConstructorInvoke(int lineNum, UpperIdent* ident, Exprs* args = 0);
    ~ConstructorInvoke();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
