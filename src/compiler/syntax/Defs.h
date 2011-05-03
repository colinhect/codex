#ifndef _DEFS_H_
#define _DEFS_H_

#include "Node.h"

#include "Def.h"

class ClassDef;

class Defs : public Node {
public:

    Def* def;
    Defs* next;

    Defs(int lineNum, Def* def, Defs* next = 0);
    ~Defs();
    
    void setParentClass(ClassDef* classDef);
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
