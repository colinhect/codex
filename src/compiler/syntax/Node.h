#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <typeinfo>

#include "../VarEnv.h"

class Bytecode;
class Compiler;
class Context;

class Node {
public:

    int lineNum; // The line number that the node appears in.

    Node(int lineNum = -1);
    virtual ~Node() {}

    virtual void analyze(Context* context, Compiler* comp) {}
    virtual VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {}
    virtual VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {}
    virtual void show(std::ostream& o, int i = 0) {}
    std::string indent(int i); 

};

#endif
