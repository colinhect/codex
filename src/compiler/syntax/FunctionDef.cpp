#include "FunctionDef.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

FunctionDef::FunctionDef(int lineNum, FunctionDecl* decl, Stmts* stmts, Decls* arguments) 
    : Def(lineNum), decl(decl), stmts(stmts), arguments(arguments) {}

FunctionDef::~FunctionDef() {
    if (decl)
        delete decl;

    if (stmts)
        delete stmts;

    if (arguments)
        delete arguments;
}

void FunctionDef::analyze(Context* context, Compiler* comp) {
    if (stmts)
        stmts->analyze(context, comp);

    if (arguments)
        arguments->analyze(context, comp);

    if (parentClass) {
        decl->ident->name = parentClass->ident->name + "_" + decl->ident->name;

        arguments = new Decls(lineNum, new VariableDecl(lineNum, new VariableType(lineNum, new UpperIdent(lineNum, parentClass->ident->name)), new LowerIdent(lineNum, "this")), arguments);
    }
}

VarEnv* FunctionDef::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {

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

    code->emitLabel(code->getLabel(decl->ident->name));
    stmts->compile(code, env, context, comp);

    return env;
}

VarEnv* FunctionDef::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {

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

    std::string typeSig = ((FunctionType*)decl->type)->returnType->ident->name;

    if (typeSig == "Int" || typeSig == "Real" || typeSig == "Nat") {
        output << typeSig ;
    } else {
        output << typeSig << "*";
    }

    output << " " << decl->ident->name;
    
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

void FunctionDef::show(std::ostream& o, int i) {
    o << indent(i);
    decl->ident->show(o);
    o << " (";

    if (arguments)
        arguments->show(o);

    o << ") -> ";

    ((FunctionType*)decl->type)->returnType->show(o);

    o << std::endl;

    if (stmts)
        stmts->show(o, i+1);

    o << indent(i);
    o << "end" << std::endl;
}

