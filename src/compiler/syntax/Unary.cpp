#include "Unary.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Unary::Unary(int lineNum, const UnaryOp op, Expr* expr) 
    : Expr(lineNum), op(op), expr(expr) {}

Unary::~Unary() {
    if (expr)
        delete expr;
}

void Unary::analyze(Context* context, Compiler* comp) {
    expr->analyze(context, comp);    
}

VarEnv* Unary::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    expr->compile(code, env, context, comp);

    switch (op) {
        case OP_NOT:
            code->emitOp(NOT); break;
    }

    return env;
}

VarEnv* Unary::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    switch (op) {
        case OP_NOT:
            output << "!";
    }
    
    return expr->compileToCpp(output, env, context, comp);
}

void Unary::show(std::ostream& o, int i) {
    switch (op) {
        case OP_NOT:
            o << "!";
            expr->show(o); break;
    }
}

