#include "Decls.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Decls::Decls(int lineNum, Decl* decl, Decls* next) 
    : Node(lineNum), decl(decl), next(next) {}

Decls::~Decls() {
    if (decl)
        delete decl;

    if (next)
        delete next;
}

VarEnv* Decls::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << "(";
    decl->compileToCpp(output, env, context, comp);

    if (next) {
        output << ", ";
        next->compileToCpp(output, env, context, comp);
    }
    output << ")";
}

Types* Decls::copyTypes() {
    if (next)
        return new Types(lineNum, decl->type->copy(), next->copyTypes());
    else
        return new Types(lineNum, decl->type->copy());
}

void Decls::show(std::ostream& o, int i) {
    decl->show(o);

    if (next) {
        o << ", ";
        next->show(o);
    }
}

