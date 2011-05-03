#include "InternalInvoke.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

InternalInvoke::InternalInvoke(int lineNum, long long func) 
    : Expr(lineNum), func(func) {
    type = new VariableType(lineNum, new UpperIdent(lineNum, "Object"));
}

VarEnv* InternalInvoke::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    code->emitOp(INTRNL);
    code->emitInt(func);

    return env;
}

void InternalInvoke::show(std::ostream& o, int i) {
    o << "_internal(" << func << ")";
}

