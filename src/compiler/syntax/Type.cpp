#include "Type.h"

#include "../Bytecode.h"
#include "../Compiler.h"
#include "../Context.h"

Type::Type(int lineNum) : Node(lineNum) {}

void Type::castTo(Type* type, Bytecode* code, Compiler* comp) {
    if (typeSig() == "Object" || type->typeSig() == "Object") {
        return;
    }

    if (typeSig() == type->typeSig()) {
        return;
    } else if (typeSig() == "Int" && type->typeSig() == "Nat") {
        code->emitOp(ITON);
        return;
    } else if (typeSig() == "Nat" && type->typeSig() == "Int") {
        return;
    } else if (typeSig() == "Int" && type->typeSig() == "Real") {
        code->emitOp(ITOR);
        return;
    } else if (typeSig() == "Nat" && type->typeSig() == "Real") {
        code->emitOp(ITOR);
        return;
    } else if (typeSig() == "Real" && type->typeSig() == "Int") {
        code->emitOp(RTOI);
        return;
    } else if (typeSig() == "Real" && type->typeSig() == "Nat") {
        code->emitOp(RTOI);
        code->emitOp(ITON);
        return;
    } else {
        comp->error("'" + typeSig() + "' cannot be cast to '" + type->typeSig() + "'", lineNum);
    }
}

