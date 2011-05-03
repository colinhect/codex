#include "FunctionInvoke.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

FunctionInvoke::FunctionInvoke(int lineNum, LowerIdent* ident, Exprs* args) 
    : Expr(lineNum), ident(ident), args(args) {}

FunctionInvoke::~FunctionInvoke() {
    if (ident)
        delete ident;

    if (args)
        delete args;
}

void FunctionInvoke::analyze(Context* context, Compiler* comp) {
    if (args)
        args->analyze(context, comp);

    type = context->functionReturnType(ident->name);

    if (!type)
        comp->error("Undefined function '" + ident->name + "'", lineNum);
}

VarEnv* FunctionInvoke::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    code->emitOp(FRAME);

    if (args)
        args->compile(code, env, context, comp);

    code->emitOp(INVK);
    code->emitReference(code->getLabel(ident->name));

    return env;
}

VarEnv* FunctionInvoke::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << ident->name << "(";

    if (args)
        args->compileToCpp(output, env, context, comp);

    output << ")";
}

void FunctionInvoke::show(std::ostream& o, int i) {
    ident->show(o);
    o << "(";

    if (args)
        args->show(o);

    o << ")";
}

