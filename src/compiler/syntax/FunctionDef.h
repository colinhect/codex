#ifndef _FUNCTIONDEF_H_
#define _FUNCTIONDEF_H_

#include "Def.h"

#include "Decls.h"
#include "FunctionDecl.h"
#include "Stmts.h"

class FunctionDef : public Def {
public:

    FunctionDecl* decl;
    Stmts* stmts;
    Decls* arguments;

    FunctionDef(int lineNum, FunctionDecl* decl, Stmts* stmts, Decls* arguments = 0);
    ~FunctionDef();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
