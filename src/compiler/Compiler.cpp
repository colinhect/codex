#include "Compiler.h"

#include "Context.h"

#include <stdio.h>
#include <stdexcept>
#include <sstream>

extern Node* root;
extern int lineNum;
extern FILE* yyin;
extern int yyparse();

Compiler::Compiler(const std::string& sourceFile, const std::string& targetFile) 
    : sourceFile(sourceFile), targetFile(targetFile), bytecode(0), context(0), syntax(0) {
}

Compiler::~Compiler() {
    if (syntax)
        delete syntax;

    if (bytecode)
        delete bytecode;
}

void Compiler::parse() {
    if ((yyin = fopen(sourceFile.c_str(), "r")) == NULL) {
        this->error("Could not open source file");
    }

    yyparse();
    
    syntax = root;
    context = new Context(syntax);
    syntax->analyze(context, this);
}

void Compiler::compile() {
    bytecode = new Bytecode();

    syntax->compile(bytecode, VarEnv::blank(), context, this);

    bytecode->analyze();
    bytecode->write(targetFile);
}
    
void Compiler::compileToCpp() {
    std::ostream& output = std::cout;

    output << "typedef int Nat;" << std::endl;
    output << "typedef int Int;" << std::endl;
    output << "typedef double Real;" << std::endl << std::endl;

    syntax->compileToCpp(std::cout, VarEnv::blank(), context, this);
}

void Compiler::warning(const std::string& message, int line) {
    if (line != -1)
        std::cout << "Warning: " << message << ": line " << line << std::endl;
    else    
        std::cout << "Warning: " << message << std::endl;
}

void Compiler::error(const std::string& message, int line) {
    std::stringstream ss;

    if (line != -1)
        ss << "Error: " << message << ": line " << line;
    else    
        ss << "Error: " << message;

    throw std::runtime_error(ss.str());
}

void Compiler::showSourceCode(std::ostream& out) {
    out << "Source: " << std::endl;
    syntax->show(out);
}

void Compiler::showTargetCode(std::ostream& out) {
    out << "Target: " << std::endl;
    bytecode->show(out);
}

