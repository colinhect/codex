#ifndef _STMTS_H_
#define _STMTS_H_

#include "Node.h"

#include "Stmt.h"
#include "Stmts.h"

class Stmts : public Node {
public:

    Stmt* stmt;
    Stmts* next;

    Stmts(int lineNum, Stmt* stmt, Stmts* next = 0);
    ~Stmts();
    
    void analyze(Context* context, Compiler* comp);
    VarEnv* compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp);
    VarEnv* compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp);
    void show(std::ostream& o, int i = 0);

};

#endif
