#include "VariableDef.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

VariableDef::VariableDef(int lineNum, Decl* decl)
    : Def(lineNum), decl(decl) {}

VariableDef::~VariableDef() {
    if (decl)
        delete decl;
}

VarEnv* VariableDef::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
}

VarEnv* VariableDef::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << ((VariableType*)((VariableDecl*)decl)->type)->ident->name << " " <<  decl->ident->name << ";" << std::endl;
}

void VariableDef::show(std::ostream& o, int i) {
    o << indent(i);
    decl->show(o);
    o << std::endl;
}

