#ifndef _CONSTRUCTORDEF_H_
#define _CONSTRUCTORDEF_H_

#include "Def.h"

#include "Decls.h"
#include "UpperIdent.h"
#include "Stmts.h"

class ConstructorDef : public Def {
public:

    UpperIdent* ident;
    Stmts* stmts;
    Decls* arguments;

    ConstructorDef(int lineNum, UpperIdent* ident, Stmts* stmts, Decls* arguments = 0);
    ~ConstructorDef();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
