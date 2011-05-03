#ifndef _DECL_H_
#define _DECL_H_

#include "Stmt.h"

#include "LowerIdent.h"
#include "Type.h"

class Decl : public Stmt {
public:

    Type* type;
    LowerIdent* ident;

    Decl(int lineNum, Type* type, LowerIdent* ident);
    virtual ~Decl();

};

#endif
