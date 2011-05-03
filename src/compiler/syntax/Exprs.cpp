#include "Exprs.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Exprs::Exprs(int lineNum, Expr* expr, Exprs* next) 
    : Node(lineNum), expr(expr), next(next) {}

Exprs::~Exprs() {
    if (expr)
        delete expr;

    if (next)
        delete next;
}

void Exprs::analyze(Context* context, Compiler* comp) {
    expr->analyze(context, comp);

    if (next)
        next->analyze(context, comp);
}

VarEnv* Exprs::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    env = expr->compile(code, env, context, comp);

    if (next)
        return next->compile(code, env, context, comp);
    else
        return env;
}

VarEnv* Exprs::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    env = expr->compileToCpp(output, env, context, comp);

    if (next)
        return next->compileToCpp(output, env, context, comp);
    else
        return env;
}

void Exprs::show(std::ostream& o, int i) {
    expr->show(o);

    if (next) {
        o << ", ";
        next->show(o);
    }
}

