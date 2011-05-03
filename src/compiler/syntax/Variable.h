#ifndef _VARIABLE_H_
#define _VARIABLE_H_ 

#include "Expr.h"

#include "LowerIdent.h"

class Variable : public Expr {
public:

    LowerIdent* ident;

    Variable(int lineNum, LowerIdent* ident);
    ~Variable();
    
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
