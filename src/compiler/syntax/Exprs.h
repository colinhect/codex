#ifndef _EXPRS_H_
#define _EXPRS_H_

#include "Node.h"

#include "Expr.h"

class Exprs : public Node {
public:

    Expr* expr;
    Exprs* next;

    Exprs(int lineNum, Expr* expr, Exprs* next = 0);
    ~Exprs();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
