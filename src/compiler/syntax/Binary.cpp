#include "Binary.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"
#include "../../vm/bytecode.h"

Binary::Binary(int lineNum, const BinaryOp op, Expr* lhs, Expr* rhs) 
    : Expr(lineNum), op(op), lhs(lhs), rhs(rhs) {}

Binary::~Binary() {
    if (lhs)
        delete lhs;
    
    if (rhs)
        delete rhs;
}

void Binary::analyze(Context* context, Compiler* comp) {
    lhs->analyze(context, comp);
    rhs->analyze(context, comp);
}

VarEnv* Binary::compile(Bytecode* code, VarEnv* env, Context* context, Compiler* comp) {
    
    // Assignment
    if (op == OP_ASSIGN) {

        // Get variable environment.
        Variable* var = (Variable*)lhs;
        VarEnv* varEnv = env->find(var->ident);
   
        // Make sure the lhs variable exists. 
        if (!varEnv)
            comp->error("Undefined variable '" + var->ident->name + "'", lineNum);

        // Compile the rhs (if it is another binary expr then it will resolve its type).
        rhs->compile(code, env, context, comp);

        // Cast to the correct type.
        rhs->type->castTo(varEnv->type, code, comp);
        
        // Store the result in the variable.
        code->emitOp(STORE);
        code->emitInt(varEnv->offset);

    // Arithmetic/logic
    } else {
        lhs->compile(code, env, context, comp);
        rhs->compile(code, env, context, comp);
 
        type = lhs->type;

        // Cast to the correct type.
        rhs->type->castTo(type, code, comp);
       
        if (type->typeSig() == "Int" || type->typeSig() == "Nat") {  
            switch(op) {
                case OP_AND:
                    code->emitOp(AND); break;
                case OP_OR:
                    code->emitOp(OR); break;
            
                case OP_PLUS:
                    code->emitOp(ADDI); break;
                case OP_MINUS:
                    code->emitOp(SUBI); break;
                case OP_MUL:
                    code->emitOp(MULI); break;
                case OP_DIV:
                    code->emitOp(DIVI); break;

                case OP_EQ:
                    code->emitOp(EQI); break;
                case OP_NE:
                    code->emitOp(EQI);
                    code->emitOp(NOT); break;
                case OP_GT:
                    code->emitOp(GTI); break;
                case OP_GE:
                    code->emitOp(LTI);
                    code->emitOp(NOT); break;
                case OP_LT:
                    code->emitOp(LTI); break;
                case OP_LE:
                    code->emitOp(GTI);
                    code->emitOp(NOT); break;
            }
         } else if (type->typeSig() == "Real") {  
            switch(op) {
                case OP_AND:
                    code->emitOp(AND); break;
                case OP_OR:
                    code->emitOp(OR); break;
            
                case OP_PLUS:
                    code->emitOp(ADDR); break;
                case OP_MINUS:
                    code->emitOp(SUBR); break;
                case OP_MUL:
                    code->emitOp(MULR); break;
                case OP_DIV:
                    code->emitOp(DIVR); break;

                case OP_EQ:
                    code->emitOp(EQR); break;
                case OP_NE:
                    code->emitOp(EQR);
                    code->emitOp(NOT); break;
                case OP_GT:
                    code->emitOp(GTR); break;
                case OP_GE:
                    code->emitOp(LTR);
                    code->emitOp(NOT); break;
                case OP_LT:
                    code->emitOp(LTR); break;
                case OP_LE:
                    code->emitOp(GTR);
                    code->emitOp(NOT); break;
            }
        } else {
            comp->error("Cannot perform binary operation on type '" + type->typeSig() + "'", lineNum);
        }

    }

    return env;
}

VarEnv* Binary::compileToCpp(std::ostream& output, VarEnv* env, Context* context, Compiler* comp) {
    
    // Assignment
    if (op == OP_ASSIGN) {

        // Get variable environment.
        Variable* var = (Variable*)lhs;
        VarEnv* varEnv = env->find(var->ident);
   
        // Make sure the lhs variable exists. 
        if (!varEnv)
            comp->error("Undefined variable '" + var->ident->name + "'", lineNum);

        output << var->ident->name << " = ";

        // Compile the rhs (if it is another binary expr then it will resolve its type).
        rhs->compileToCpp(output, env, context, comp);

    // Arithmetic/logic
    } else {
        output << "(";
        lhs->compileToCpp(output, env, context, comp);
 
        type = lhs->type;

        switch(op) {
            case OP_AND:
                output << " && "; break;
            case OP_OR:
                output << " || "; break;
            
            case OP_PLUS:
                output << " + "; break;
            case OP_MINUS:
                output << " - "; break;
            case OP_MUL:
                output << " * "; break;
            case OP_DIV:
                output << " / "; break;

            case OP_EQ:
                output << " == "; break;
            case OP_NE:
                output << " != "; break;
            case OP_GT:
                output << " > "; break;
            case OP_GE:
                output << " >= "; break;
            case OP_LT:
                output << " < "; break;
            case OP_LE:
                output << " <= "; break;
        }
            
        rhs->compileToCpp(output, env, context, comp);
        output << ")";
    }

    return env;
}

void Binary::show(std::ostream& o, int i) {
    o << "(";
    lhs->show(o);

    o << " ";

    switch(op) {
        case OP_ASSIGN:
            o << ":="; break;
        case OP_PLUS:
            o << "+"; break;
        case OP_MINUS:
            o << "-"; break;
        case OP_MUL:
            o << "*"; break;
        case OP_DIV:
            o << "/"; break;
        case OP_EQ:
            o << "=="; break;
        case OP_NE:
            o << "!="; break;
        case OP_GT:
            o << ">"; break;
        case OP_GE:
            o << ">="; break;
        case OP_LT:
            o << "<"; break;
        case OP_LE:
            o << "<="; break;
    }

    o << " ";

    rhs->show(o);
    o << ")";
}

