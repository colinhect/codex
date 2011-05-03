#ifndef _DECLS_H_
#define _DECLS_H_

#include "Node.h"

#include "Decl.h"
#include "Decls.h"
#include "Types.h"

class Decls : public Node {
public:

    Decl* decl;
    Decls* next;

    Decls(int lineNum, Decl* decl, Decls* next = 0);
    ~Decls();

    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    Types* copyTypes();
    void show(std::ostream& o, int i = 0);

};

#endif
