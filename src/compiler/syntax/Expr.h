#ifndef _EXPR_H_
#define _EXPR_H_

#include "Stmt.h"

#include "Type.h"

class Expr : public Stmt {
public:

    Type* type;

    Expr(int lineNum);
    virtual ~Expr();

};

#endif
