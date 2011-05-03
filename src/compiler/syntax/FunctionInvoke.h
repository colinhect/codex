#ifndef _FUNCTIONINVOKE_H_
#define _FUNCTIONINVOKE_H_

#include "Expr.h"

#include "Exprs.h"
#include "LowerIdent.h"

class FunctionInvoke : public Expr {
public:

    LowerIdent* ident;
    Exprs* args;

    FunctionInvoke(int lineNum, LowerIdent* ident, Exprs* args = 0);
    ~FunctionInvoke();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
