#include "RealLit.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

RealLit::RealLit(int lineNum, double value) 
    : Expr(lineNum), value(value) {
    type = new VariableType(lineNum, new UpperIdent(lineNum, "Real"));
}

VarEnv* RealLit::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    code->emitOp(LDC);
    code->emitReal(value);

    return env;
}

VarEnv* RealLit::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << value;
}

void RealLit::show(std::ostream& o, int i) {
    o << value;
}

