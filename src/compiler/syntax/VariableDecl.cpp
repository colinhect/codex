#include "VariableDecl.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

VariableDecl::VariableDecl(int lineNum, VariableType* type, LowerIdent* ident) 
    : Decl(lineNum, type, ident) {}

VariableDecl::~VariableDecl() {
}

VarEnv* VariableDecl::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    
    // It is assumed that variable declarations appear at the top of a
    // function body.  Therefore all that is needed to instantiate the
    // variable is for it to be pushed on the stack.
    
    std::string typeSig = type->typeSig();

    if (typeSig == "Int") {
        code->emitOp(LDC);
        code->emitInt(0);
    } else if (typeSig == "Nat") {
        code->emitOp(LDC);
        code->emitInt(0);
    } else if (typeSig == "Real") {
        code->emitOp(LDC);
        code->emitReal(0.0);
    } else {
        comp->error("Unknown type '" + typeSig + "'", lineNum);
    }

    return new VarEnv(ident, type, env->offset+1, env);
}

VarEnv* VariableDecl::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    std::string typeSig = type->typeSig();

    if (typeSig == "Int" || typeSig == "Real" || typeSig == "Nat") {
        output << typeSig << " " << ident->name;
    } else {
        output << typeSig << "* " << ident->name;
    }

    return new VarEnv(ident, type, env->offset+1, env);
}

void VariableDecl::show(std::ostream& o, int i) {
    ident->show(o);

    o << ": ";

    type->show(o);
}

