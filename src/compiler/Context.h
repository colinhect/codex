#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include "Syntax.h"

#include <iostream>
#include <string>

class Context {
public:

    Node* root;
    
    Context(Node* root);

    VariableType* functionReturnType(const std::string& functionName);

};

#endif
