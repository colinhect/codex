#include "Context.h"

#include <typeinfo>
#include <iostream>

Context::Context(Node* root) 
    : root(root) {}

VariableType* Context::functionReturnType(const std::string& functionName) {
    Defs* defs = ((Module*)root)->defs;

    while (defs) {
        Def* def = defs->def;
        
        if (typeid(*def) == typeid(FunctionDef)) {
            if (((FunctionDef*)def)->decl->ident->name == functionName) {
                return ((FunctionType*)((FunctionDef*)def)->decl->type)->returnType;
            }
        }

        defs = defs->next;
    }

    return 0;
}

