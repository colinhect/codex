#ifndef _DEF_H_
#define _DEF_H_

#include "Node.h"

class ClassDef;

class Def : public Node {
public:

    ClassDef* parentClass;

    Def(int lineNum);
    virtual ~Def() {};

};

#endif
