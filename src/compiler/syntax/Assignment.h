#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include "Stmt.h"

#include "Variable.h"

class Assignment : public Stmt {
public:

    Variable* var;
    Expr* rhs;

    Assignment(int lineNum, Variable* var, Expr* rhs);
    ~Assignment();

    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
