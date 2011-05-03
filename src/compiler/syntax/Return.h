#ifndef _RETURN_H_
#define _RETURN_H_

#include "Stmt.h"

#include "Expr.h"

class Return : public Stmt {
public:

    Expr* rhs;

    Return(int lineNum, Expr* rhs = 0);
    ~Return();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
