#ifndef _MODULE_H_
#define _MODULE_H_

#include "Node.h"

#include "Defs.h"
#include "UpperIdent.h"

class Module : public Node {
public:

    UpperIdent* ident;
    Defs* defs;

    Module(int lineNum, UpperIdent* ident, Defs* defs);
    ~Module();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
