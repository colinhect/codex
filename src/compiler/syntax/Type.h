#ifndef _TYPE_H_
#define _TYPE_H_

#include "Node.h"

class Type : public Node {
public:

    Type(int lineNum);
    virtual ~Type() {}
    
    virtual Type* copy() = 0;
    virtual std::string typeSig() = 0;
    void castTo(Type* type, Bytecode* code, Compiler* comp);

};

#endif
