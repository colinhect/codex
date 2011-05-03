#ifndef _CLASSDEF_H_
#define _CLASSDEF_H_

#include "Def.h"

#include "Defs.h"
#include "UpperIdent.h"

class ClassDef : public Def {
public:

    UpperIdent* ident;
    Defs* defs;
    long long size;

    ClassDef(int lineNum, UpperIdent* ident, Defs* defs);
    ~ClassDef();

    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
