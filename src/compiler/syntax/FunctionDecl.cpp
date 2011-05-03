#include "FunctionDecl.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

FunctionDecl::FunctionDecl(int lineNum, FunctionType* type, LowerIdent* ident) 
    : Decl(lineNum, type, ident) {}

FunctionDecl::~FunctionDecl() {
}

void FunctionDecl::show(std::ostream& o, int i) {
    ident->show(o);

    o << " ";

    type->show(o);
}

