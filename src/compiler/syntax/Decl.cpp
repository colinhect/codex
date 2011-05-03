#include "Decl.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Decl::Decl(int lineNum, Type* type, LowerIdent* ident) 
    : Stmt(lineNum), type(type), ident(ident) {}

Decl::~Decl() {
    if (type)
        delete type;
    
    if (ident)
        delete ident;
}

