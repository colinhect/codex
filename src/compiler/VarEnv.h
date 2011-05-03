#ifndef _VARENV_H_
#define _VARENV_H_

class LowerIdent;
class Type;

class VarEnv {
public:

    LowerIdent* ident;
    Type* type;
    int offset;

    VarEnv* next;

    VarEnv(LowerIdent* ident, Type* type, int offset, VarEnv* next = 0);
    ~VarEnv();

    VarEnv* find(LowerIdent* ident);

    static VarEnv* blank();

};

#endif
