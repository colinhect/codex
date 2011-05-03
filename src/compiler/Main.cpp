#include "Compiler.h"

#include <iostream>
#include <stdexcept>

int main(int argc, const char* argv[]) {
    std::string sourceInput, targetOutput = "out.cxe";
    bool verbose = false, cpp = false;

    for (int i = 0; i < argc; ++i) {
        std::string arg(argv[i]);

        if (arg == "-v")
            verbose = true;
        else if (arg == "-c")
            cpp = true;
        else if (arg == "-o")
            targetOutput = argv[++i];
        else
            sourceInput = arg;
    }    

    try {
        Compiler* compiler = new Compiler(sourceInput, targetOutput);
    
        compiler->parse();
        
        if (verbose)
            compiler->showSourceCode(std::cout);
        
        if (cpp)
            compiler->compileToCpp();
        else
            compiler->compile();

        if (verbose)
            compiler->showTargetCode(std::cout);

        delete compiler;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
