#include "ClassDef.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

ClassDef::ClassDef(int lineNum, UpperIdent* ident, Defs* defs)
    : Def(lineNum), ident(ident), defs(defs), size(0) {

    /*
    Stmts* stmts = new Stmts(lineNum, new Return(lineNum, new IntLit(lineNum, 1)));

    // Default constructor.
    FunctionDef* constructor = new FunctionDef(lineNum, new FunctionDecl(lineNum, new FunctionType(lineNum, new VariableType(lineNum, new UpperIdent(lineNum, ident->name))), new LowerIdent(lineNum, "constructor0")), stmts);

    this->defs = new Defs(lineNum, constructor, defs);
    */

}

ClassDef::~ClassDef() {
    if (ident)
        delete ident;

    if (defs)
        delete defs;
}

void ClassDef::analyze(Context* context, Compiler* comp) {
    //defs->setParentClass(this);

    defs->analyze(context, comp);

    Defs* next = defs;

    while (next) {
        if (typeid(*next->def) == typeid(VariableDef))
            size++;

        next = next->next;
    }
}

VarEnv* ClassDef::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    code->emitLabel(code->getLabel(ident->name));
    code->emitOp(SIZE);
    code->emitInt(size);

    defs->compile(code, env, context, comp);
}

VarEnv* ClassDef::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {

    // Add members to var environment.
    Defs* next = defs;

    while (next) {
        if (typeid(*next->def) == typeid(VariableDef)) {
            VariableDef* varDef = ((VariableDef*)next->def);
            env = new VarEnv(varDef->decl->ident, varDef->decl->type, 0, env);
        }

        next = next->next;
    }

    output << "class " << ident->name << "{" << std::endl;    
    output << "public: " << std::endl << std::endl;    

    defs->compileToCpp(output, env, context, comp);

    output << "};" << std::endl << std::endl;
}

void ClassDef::show(std::ostream& o, int i) {
    ident->show(o);
    o << std::endl << std::endl;
    defs->show(o, i+1);
    o << "end" << std::endl;
}

