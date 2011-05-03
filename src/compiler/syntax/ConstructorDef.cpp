#include "ConstructorDef.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

ConstructorDef::ConstructorDef(int lineNum, UpperIdent* ident, Stmts* stmts, Decls* arguments) 
    : Def(lineNum), ident(ident), stmts(stmts), arguments(arguments) {}

ConstructorDef::~ConstructorDef() {
    if (stmts)
        delete stmts;

    if (arguments)
        delete arguments;
}

void ConstructorDef::analyze(Context* context, Compiler* comp) {
    if (stmts)
        stmts->analyze(context, comp);

    if (arguments)
        arguments->analyze(context, comp);

    /*
    if (parentClass) {
        decl->ident->name = parentClass->ident->name + "_" + decl->ident->name;

        arguments = new Decls(lineNum, new VariableDecl(lineNum, new VariableType(lineNum, new UpperIdent(lineNum, parentClass->ident->name)), new LowerIdent(lineNum, "this")), arguments);
    }
    */
}

VarEnv* ConstructorDef::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    return env;
}

VarEnv* ConstructorDef::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {

    // Add arguments to var environment.
    if (arguments) {
        int offset = 0;
        Decls* decls = arguments;

        while (decls) {
            VarEnv* newEnv = new VarEnv(decls->decl->ident, decls->decl->type, offset++, env);
            env = newEnv;
            decls = decls->next;
        }
    }

    output << ident->name;
    
    if (arguments) {
        arguments->compileToCpp(output, env, context, comp); 
    } else {
        output << "()";
    }

    output << " {" << std::endl;

    stmts->compileToCpp(output, env, context, comp);

    output << "}" << std::endl << std::endl;
    return env;
}

void ConstructorDef::show(std::ostream& o, int i) {
    o << indent(i);
    ident->show(o);
    o << " (";

    if (arguments)
        arguments->show(o);

    o << ")" << std::endl;

    if (stmts)
        stmts->show(o, i+1);

    o << indent(i);
    o << "end" << std::endl;
}

