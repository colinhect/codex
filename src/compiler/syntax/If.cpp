#include "If.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

If::If(int lineNum, Expr* condition, Stmts* stmts, Stmts* elseStmts) 
    : Stmt(lineNum), condition(condition), stmts(stmts), elseStmts(elseStmts) {}

If::~If() {
    if (condition)
        delete condition;
    
    if (stmts)
        delete stmts;

    if (elseStmts)
        delete elseStmts;
}

void If::analyze(Context* context, Compiler* comp) {
    stmts->analyze(context, comp);
    
    if (elseStmts)
        elseStmts->analyze(context, comp);
}

VarEnv* If::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    Label* elseLabel = code->getUniqueLabel("ifElse");
    Label* endLabel = code->getUniqueLabel("ifEnd");
    
    condition->compile(code, env, context, comp);
    code->emitOp(IFF);

    if (elseStmts) {
        code->emitReference(elseLabel);
    } else { 
        code->emitReference(endLabel);
    }    

    stmts->compile(code, env, context, comp);

    if (elseStmts) {
        code->emitOp(GOTO);
        code->emitReference(endLabel);

        code->emitLabel(elseLabel);
        elseStmts->compile(code, env, context, comp);
    }

    code->emitLabel(endLabel);
    
    return env;
}

VarEnv* If::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << "if (";
    condition->compileToCpp(output, env, context, comp);
    output << ") {" << std::endl;

    stmts->compileToCpp(output, env, context, comp);

    output << "}" << std::endl;

    if (elseStmts) {
        output << "else {" << std::endl;
        elseStmts->compileToCpp(output, env, context, comp);
        output << "}" << std::endl;
    }

    return env;
}

void If::show(std::ostream& o, int i) {
    o << std::endl;
    
    o << indent(i) << "if ";
    condition->show(o);
    o << std::endl;

    stmts->show(o, i+1);

    if (elseStmts) {
        o << indent(i) << "else" << std::endl;
        elseStmts->show(o, i+1);
    }
    
    o << indent(i) << "end" << std::endl;
}

