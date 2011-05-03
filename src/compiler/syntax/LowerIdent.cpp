#include "LowerIdent.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

LowerIdent::LowerIdent(int lineNum, const std::string& name) 
    : Node(lineNum), name(name) {}

void LowerIdent::show(std::ostream& o, int i) {
    o << name;
}

