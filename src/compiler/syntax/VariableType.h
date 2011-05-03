#ifndef _VARIABLETYPE_H_
#define _VARIABLETYPE_H_

#include "Type.h"

#include "UpperIdent.h"

class VariableType : public Type {
public:

    UpperIdent* ident;

    VariableType(int lineNum, UpperIdent* ident);
    ~VariableType();
    
    Type* copy();
    std::string typeSig();
    void show(std::ostream& o, int i = 0);

};

#endif
