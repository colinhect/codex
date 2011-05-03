#include "Variable.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Variable::Variable(int lineNum, LowerIdent* ident) 
    : Expr(lineNum), ident(ident) {}

Variable::~Variable() {
    if (ident)
        delete ident;
}

VarEnv* Variable::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    VarEnv* varEnv = env->find(ident);
    
    if (!varEnv)
        comp->error("Undefined variable '" + ident->name + "'", lineNum);

    type = varEnv->type;

    code->emitOp(LOAD);
    code->emitInt(varEnv->offset);
    
    return env;
}
    
VarEnv* Variable::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    VarEnv* varEnv = env->find(ident);
    
    //if (!varEnv)
    //    comp->error("Undefined variable '" + ident->name + "'", lineNum);

    output << ident->name;
    
    return env;
}

void Variable::show(std::ostream& o, int i) {
    ident->show(o);
}

