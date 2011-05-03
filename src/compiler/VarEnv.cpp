#include "VarEnv.h"

#include "Syntax.h"

VarEnv::VarEnv(LowerIdent* ident, Type* type, int offset, VarEnv* next) : ident(ident), type(type), offset(offset), next(next) {}

VarEnv::~VarEnv() {
    if (next)
        delete next; 
}

VarEnv* VarEnv::find(LowerIdent* ident) {
    if (ident->name == this->ident->name)
        return this;
    else if (next)
        return next->find(ident);
    else
        return 0;
}

VarEnv* VarEnv::blank() {
    return new VarEnv(new LowerIdent(-1, "Env"), new VariableType(-1, new UpperIdent(-1, "Void")), -1);
}

