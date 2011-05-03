#ifndef _FUNCTIONDECL_H_
#define _FUNCTIONDECL_H_

#include "Decl.h"

#include "FunctionType.h"
#include "LowerIdent.h"

class FunctionDecl : public Decl {
public:

    FunctionDecl(int lineNum, FunctionType* type, LowerIdent* ident);
    ~FunctionDecl();
    
    void show(std::ostream& o, int i = 0);

};

#endif
