#include "Expr.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Expr::Expr(int lineNum) 
    : Stmt(lineNum) {}  

Expr::~Expr() {
    if (type)
        delete type;
}

