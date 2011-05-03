#include "While.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

While::While(int lineNum, Expr* condition, Stmts* stmts) 
    : Stmt(lineNum), condition(condition), stmts(stmts) {}

While::~While() {
    if (condition)
        delete condition;

    if (stmts)
        delete stmts;
}

void While::analyze(Context* context, Compiler* comp) {
    condition->analyze(context, comp);
    stmts->analyze(context, comp);
}

VarEnv* While::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    Label* condLabel = code->getUniqueLabel("whileCond");
    Label* endLabel = code->getUniqueLabel("whileEnd");
    
    code->emitLabel(condLabel);
    condition->compile(code, env, context, comp);
    
    code->emitOp(IFF);
    code->emitReference(endLabel);
    
    stmts->compile(code, env, context, comp);
    code->emitOp(GOTO);
    code->emitReference(condLabel);

    code->emitLabel(endLabel);
    return env;
}

VarEnv* While::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    output << "while (";
    condition->compileToCpp(output, env, context, comp);
    output << ") {" << std::endl;
    stmts->compileToCpp(output, env, context, comp);
    output << "}" << std::endl;

    return env;
}

void While::show(std::ostream& o, int i) {
    o << std::endl;
    
    o << indent(i) << "while ";
    condition->show(o);
    o << std::endl;

    stmts->show(o, i+1);

    o << indent(i) << "end" << std::endl;
}

