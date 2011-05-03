#ifndef _LOWERIDENT_H_
#define _LOWERIDENT_H_

#include "Node.h"

class LowerIdent : public Node {
public:

    std::string name;

    LowerIdent(int lineNum, const std::string& name);
    
    void show(std::ostream& o, int i = 0);

};

#endif
