#ifndef _WHILE_H_
#define _WHILE_H_

#include "Stmt.h"

#include "Expr.h"
#include "Stmts.h"

class While : public Stmt {
public:

    Expr* condition;
    Stmts* stmts;

    While(int lineNum, Expr* condition, Stmts* stmts);
    ~While();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
