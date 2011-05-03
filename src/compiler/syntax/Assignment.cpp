#include "Assignment.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

#include <typeinfo>

Assignment::Assignment(int lineNum, Variable* var, Expr* rhs) 
    : Stmt(lineNum), var(var), rhs(rhs) {}

Assignment::~Assignment() {
    if (var)
        delete var;
    
    if (rhs)
        delete rhs;
}

void Assignment::analyze(Context* context, Compiler* comp) {
    rhs->analyze(context, comp);
}

VarEnv* Assignment::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    return env;
}

VarEnv* Assignment::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    VarEnv* varEnv = env->find(var->ident);
   
    if (!varEnv) {
        std::string typeSig;
        
        if (typeid(*rhs->type) == typeid(VariableType)) {
            typeSig = rhs->type->typeSig();
        } else if (typeid(*rhs->type) == typeid(FunctionType)) {
            typeSig = ((FunctionType*)rhs->type)->returnType->typeSig();
        }

        if (typeSig == "Int" || typeSig == "Nat" || typeSig == "Real") {
            output << typeSig << " ";
        } else {
            output << typeSig << "* ";
        }
    }

    output << var->ident->name << " = ";

    rhs->compileToCpp(output, env, context, comp);

    return env;
}

void Assignment::show(std::ostream& o, int i) {
    o << "";
    var->show(o);

    o << " = ";

    rhs->show(o);
}

