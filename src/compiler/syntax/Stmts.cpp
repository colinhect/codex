#include "Stmts.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Stmts::Stmts(int lineNum, Stmt* stmt, Stmts* next) 
    : Node(lineNum), stmt(stmt), next(next) {}

Stmts::~Stmts() {
    if (stmt)
        delete stmt;

    if (next)
        delete next;
}

void Stmts::analyze(Context* context, Compiler* comp) {
    stmt->analyze(context, comp);

    if (next)
        next->analyze(context, comp);
}

VarEnv* Stmts::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    env = stmt->compile(code, env, context, comp);

    if (next)
        return next->compile(code, env, context, comp);
    else
        return env;
}

VarEnv* Stmts::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    env = stmt->compileToCpp(output, env, context, comp);
    output << ";" << std::endl;

    if (next)
        return next->compileToCpp(output, env, context, comp);
    else
        return env;
}

void Stmts::show(std::ostream& o, int i) {
    o << indent(i);
    stmt->show(o, i);
    o << std::endl;

    if (next) 
        next->show(o, i);
}

