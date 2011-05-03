#include "Types.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Types::Types(int lineNum, Type* type, Types* next) 
    : Node(lineNum), type(type), next(next) {}

Types::~Types() {
    if (type)
        delete type;

    if (next)
        delete next;
}

Types* Types::copy() {
    if (next)
        return new Types(lineNum, type->copy(), next->copy());
    else
        return new Types(lineNum, type->copy());
}

std::string Types::typeSig() {
    std::string sig = type->typeSig();

    if (next) {
        sig += ", ";
        sig += next->typeSig();
    }

    return sig;
}

void Types::show(std::ostream& o, int i) {
    o << typeSig();
}

