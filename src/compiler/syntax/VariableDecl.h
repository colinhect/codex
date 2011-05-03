#ifndef _VARIABLEDECL_H_
#define _VARIABLEDECL_H_

#include "Decl.h"

#include "LowerIdent.h"
#include "VariableType.h"

class VariableDecl : public Decl {
public:

    VariableDecl(int lineNum, VariableType* type, LowerIdent* ident);
    ~VariableDecl();
    
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
