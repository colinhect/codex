#ifndef _TYPES_H_
#define _TYPES_H_

#include "Node.h"

#include "Type.h"
#include "Types.h"

class Types : public Node {
public:

    Type* type;
    Types* next;

    Types(int lineNum, Type* type, Types* next = 0);
    ~Types();
    
    Types* copy();
    std::string typeSig();
    void show(std::ostream& o, int i = 0);

};

#endif
