#include "UpperIdent.h"

UpperIdent::UpperIdent(int lineNum, const std::string& name) 
    : Node(lineNum), name(name) {}

void UpperIdent::show(std::ostream& o, int i) {
    o << name;
}

