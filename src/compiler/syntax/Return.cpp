#include "Return.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Return::Return(int lineNum, Expr* rhs) 
    : Stmt(lineNum), rhs(rhs) {}

Return::~Return() {
    if (rhs)
        delete rhs;
}

void Return::analyze(Context* context, Compiler* comp) {
    if (rhs)
        rhs->analyze(context, comp);
}

VarEnv* Return::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    if (rhs) {
        rhs->compile(code, env, context, comp);
        code->emitOp(RETVAL);
    } else {
        code->emitOp(RET);
    }

    return env;
}

VarEnv* Return::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << "return ";

    if (rhs)
        rhs->compileToCpp(output, env, context, comp);
}

void Return::show(std::ostream& o, int i) {
    o << "return ";
    
    if (rhs)
        rhs->show(o);
}

