#ifndef _REALLIT_H_
#define _REALLIT_H_

#include "Expr.h"

class RealLit : public Expr {
public:

    double value;

    RealLit(int lineNum, double value);
    
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
