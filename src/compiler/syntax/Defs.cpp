#include "Defs.h"

Defs::Defs(int lineNum, Def* def, Defs* next) 
    : Node(lineNum), def(def), next(next) {}

Defs::~Defs() {
    if (def)
        delete def;

    if (next)
        delete next;
}
    
void Defs::setParentClass(ClassDef* classDef) {
    def->parentClass = classDef;
    
    if (next)
        next->setParentClass(classDef);
}

void Defs::analyze(Context* context, Compiler* comp) {
    def->analyze(context, comp);
    
    if (next)
        next->analyze(context, comp);
}

VarEnv* Defs::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    def->compile(code, env, context, comp);

    if (next)
        return next->compile(code, env, context, comp);
    else
        return env;
}

VarEnv* Defs::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    def->compileToCpp(output, env, context, comp);

    if (next)
        return next->compileToCpp(output, env, context, comp);
    else
        return env;
}

void Defs::show(std::ostream& o, int i) {
    def->show(o, i);

    o << std::endl;

    if (next)
        next->show(o, i);
}

