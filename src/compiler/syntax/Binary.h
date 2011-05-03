#ifndef _BINARY_H_
#define _BINARY_H_

#include "Expr.h"

enum BinaryOp {
    OP_ASSIGN,

    OP_AND,
    OP_OR,
    
    OP_PLUS,
    OP_MINUS,
    OP_MUL,
    OP_DIV,

    OP_EQ,
    OP_NE,
    OP_GT,
    OP_LT,
    OP_GE,
    OP_LE
};

class Binary : public Expr {
public:

    BinaryOp op;
    Expr* lhs;
    Expr* rhs;

    Binary(int lineNum, const BinaryOp op, Expr* lhs, Expr* rhs);
    ~Binary();

    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
