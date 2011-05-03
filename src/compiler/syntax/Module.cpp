#include "Module.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

#include <typeinfo>

Module::Module(int lineNum, UpperIdent* ident, Defs* defs)
    : Node(lineNum), ident(ident), defs(defs) {}

Module::~Module() {
    if (ident)
        delete ident;
   
    // Seg fault when attempting to delete. 
    //if (defs)
    //    delete defs;
}

void Module::analyze(Context* context, Compiler* comp) {
    defs->analyze(context, comp);
}

VarEnv* Module::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    defs->compile(code, env, context, comp);
}

VarEnv* Module::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    Defs* next = defs;
    while (next) {
        if (typeid(*next->def) == typeid(FunctionDef)) {
            FunctionDef* def = (FunctionDef*)next->def;
    

            std::string typeSig = ((FunctionType*)((FunctionDecl*)def->decl)->type)->returnType->ident->name;

            if (typeSig == "Int" || typeSig == "Real" || typeSig == "Nat") {
                output << typeSig ;
            } else {
                output << typeSig << "*";
            }

            output << " " << ((FunctionDef*)next->def)->decl->ident->name;

            if (def->arguments)
                def->arguments->compileToCpp(output, env, context, comp);
            else
                output << "()";

            output << ";" << std::endl;
        }        

        else if (typeid(*next->def) == typeid(ClassDef)) {
            ClassDef* def = (ClassDef*)next->def;

            output << "class " << def->ident->name << ";" << std::endl;
        }

        next = next->next;
    }

    output << std::endl;

    defs->compileToCpp(output, env, context, comp);
}

void Module::show(std::ostream& o, int i) {
    o << "module ";
    ident->show(o);
    o << std::endl << std::endl;

    defs->show(o);
}

