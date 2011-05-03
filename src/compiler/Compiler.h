#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "Bytecode.h"
#include "Syntax.h"

#include <iostream>
#include <string>

class Context;

class Compiler {

public:

    Compiler(const std::string& sourceFile, const std::string& targetFile);
    ~Compiler();

    void parse();
    void compile();
    void compileToCpp();

    void warning(const std::string& message, int line = -1);
    void error(const std::string& message, int line = -1);

    void showSourceCode(std::ostream& out);
    void showTargetCode(std::ostream& out);

private:

    std::string sourceFile, targetFile;

    Node* syntax;
    Context* context;
    Bytecode* bytecode;

};

#endif
