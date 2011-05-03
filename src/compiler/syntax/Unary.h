#ifndef _UNARY_H_
#define _UNARY_H_

#include "Expr.h"

enum UnaryOp {
    OP_NEG,
    OP_NOT,
};

class Unary : public Expr {
public:

    UnaryOp op;
    Expr* expr;

    Unary(int lineNum, const UnaryOp op, Expr* expr);
    ~Unary();

    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
