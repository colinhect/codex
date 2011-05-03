#ifndef _CAST_H_
#define _CAST_H_

#include "Expr.h"

class Cast : public Expr {
public:

    Expr* expr;

    Cast(int lineNum, Expr* expr, Type* type);
    ~Cast();

    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
