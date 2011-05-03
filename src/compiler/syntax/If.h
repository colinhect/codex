#ifndef _IF_H_
#define _IF_H_

#include "Stmt.h"

#include "Expr.h"
#include "Stmts.h"

class If : public Stmt {
public:

    Expr* condition;
    Stmts* stmts, *elseStmts;

    If(int lineNum, Expr* condition, Stmts* stmts, Stmts* elseStmts = 0);
    ~If();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
