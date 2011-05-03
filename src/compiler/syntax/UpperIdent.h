#ifndef _UPPERIDENT_H_
#define _UPPERIDENT_H_

#include "Node.h"

class UpperIdent : public Node {
public:

    std::string name;

    UpperIdent(int lineNum, const std::string& name);
    
    void show(std::ostream& o, int i = 0);

};

#endif
