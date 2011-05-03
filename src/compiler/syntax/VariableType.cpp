#include "VariableType.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

VariableType::VariableType(int lineNum, UpperIdent* ident) 
    : Type(lineNum), ident(ident) {}

VariableType::~VariableType() {
    if (ident)
        delete ident;
}

Type* VariableType::copy() {
    return new VariableType(lineNum, new UpperIdent(ident->lineNum, ident->name));
}

std::string VariableType::typeSig() {
    return ident->name;
}

void VariableType::show(std::ostream& o, int i) {
    o << typeSig();
}

