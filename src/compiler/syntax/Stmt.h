#ifndef _STMT_H_
#define _STMT_H_

#include "Node.h"

class Stmt : public Node {
public:

    Stmt(int lineNum);
    virtual ~Stmt() {};

};

#endif
