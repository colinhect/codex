#include "Cast.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Cast::Cast(int lineNum, Expr* expr, Type* type) 
    : Expr(lineNum), expr(expr) {
    this->type = type;
}

Cast::~Cast() {
    if (expr)
        delete expr;
    
    if (type)
        delete type;
}

void Cast::analyze(Context* context, Compiler* comp) {
    expr->analyze(context, comp);
}

VarEnv* Cast::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    expr->compile(code, env, context, comp);
    expr->type->castTo(type, code, comp);

    return env;
}

VarEnv* Cast::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << "(";
    expr->compileToCpp(output, env, context, comp);
    output << ")";
}

void Cast::show(std::ostream& o, int i) {
    o << "(";
    expr->show(o);
    o << ": ";
    type->show(o);
    o << ")";
}

