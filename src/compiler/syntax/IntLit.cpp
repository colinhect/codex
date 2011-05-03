#include "IntLit.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

IntLit::IntLit(int lineNum, long long value) 
    : Expr(lineNum), value(value) {
    type = new VariableType(lineNum, new UpperIdent(lineNum, "Int"));
}

VarEnv* IntLit::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    code->emitOp(LDC);
    code->emitInt(value);

    return env;
}

VarEnv* IntLit::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << value;
}

void IntLit::show(std::ostream& o, int i) {
    o << value;
}
