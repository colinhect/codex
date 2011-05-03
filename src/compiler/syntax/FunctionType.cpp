#include "FunctionType.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

FunctionType::FunctionType(int lineNum, VariableType* returnType, Types* argumentTypes) 
    : Type(lineNum), returnType(returnType), argumentTypes(argumentTypes) {}

FunctionType::~FunctionType() {
    if (returnType)
        delete returnType;

    if (argumentTypes)
        delete argumentTypes;   
}

Type* FunctionType::copy() {
    if (argumentTypes)
        return new FunctionType(lineNum, (VariableType*)returnType->copy(), argumentTypes->copy());
    else
        return new FunctionType(lineNum, (VariableType*)returnType->copy());
}

std::string FunctionType::typeSig() {
    std::string sig = "(";

    if (argumentTypes)
        sig += argumentTypes->typeSig();

    sig += ") -> ";
    sig += returnType->typeSig();

    return sig;
}

void FunctionType::show(std::ostream& o, int i) {
    o << typeSig();
}

