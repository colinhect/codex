#ifndef _VARIABLEDEF_H_
#define _VARIABLEDEF_H_

#include "Def.h"

#include "Decl.h"

class VariableDef : public Def {
public:

    Decl* decl;

    VariableDef(int lineNum, Decl* decl);
    ~VariableDef();

    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
