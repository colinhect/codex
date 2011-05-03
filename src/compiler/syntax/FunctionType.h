#ifndef _FUNCTIONTYPE_H_
#define _FUNCTIONTYPE_H_

#include "Type.h"

#include "Types.h"
#include "VariableType.h"

class FunctionType : public Type {
public:

    VariableType* returnType;
    Types* argumentTypes;

    FunctionType(int lineNum, VariableType* returnType, Types* argumentTypes = 0);
    ~FunctionType();

    Type* copy();
    std::string typeSig();
    void show(std::ostream& o, int i = 0);

};

#endif
