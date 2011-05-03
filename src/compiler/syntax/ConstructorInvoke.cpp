#include "ConstructorInvoke.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

ConstructorInvoke::ConstructorInvoke(int lineNum, UpperIdent* ident, Exprs* args) 
    : Expr(lineNum), ident(ident), args(args) {}

ConstructorInvoke::~ConstructorInvoke() {
    if (ident)
        delete ident;

    if (args)
        delete args;
}

void ConstructorInvoke::analyze(Context* context, Compiler* comp) {
    if (args)
        args->analyze(context, comp);

    Types* types;
    Exprs* next = args;

    while (next) {
        types = new Types(lineNum, next->expr->type, types);       

        next = next->next;
    }

    type = new FunctionType(lineNum, new VariableType(lineNum, ident), types);
}

VarEnv* ConstructorInvoke::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    return env;
}

VarEnv* ConstructorInvoke::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << "new " << ident->name << "(";

    if (args)
        args->compileToCpp(output, env, context, comp);

    output << ")";
}

void ConstructorInvoke::show(std::ostream& o, int i) {
    ident->show(o);
    o << "(";

    if (args)
        args->show(o);

    o << ")";
}

