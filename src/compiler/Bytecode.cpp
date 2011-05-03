#include "Bytecode.h"

#include <fstream>
#include <sstream>
#include <map>

// ----------------------------------------------------------------------
// Label

Label::Label(std::string name) : name(name), location(-1) {}

// ----------------------------------------------------------------------
// Atom

Atom::Atom(AtomType type, word data) : type(type), data(data), label(0) {}

Atom::Atom(AtomType type, Label* label) : type(type), label(label) {}

long long Atom::analyze(long long location) {
    switch (type) {
        case ATOM_LABEL:
            label->location = location;
            return 0;
        case ATOM_OP:
            return 1;
        case ATOM_INTLIT:
        case ATOM_REALLIT:
        case ATOM_REFERENCE:
            return 8;
    }

    return 0;
}

void Atom::show(std::ostream& o) {
    if (type == ATOM_OP) {
        o << "\t";

        switch(data.b[0]) {

        /* Memory access operations. */
        case LDC:
            o << "ldc\t"; break;
        case LOAD:
            o << "load\t"; break;
        case STORE: 
            o << "store\t"; break;

        /* Arithmetic operations */
        case ADDI:
            o << "addi\n"; break;
        case ADDR:
            o << "addr\n"; break;
        case SUBI:
            o << "subi\n"; break;
        case SUBR:
            o << "subr\n"; break;
        case MULI:
            o << "muli\n"; break;
        case MULR:
            o << "mulr\n"; break;
        case DIVI:
            o << "divi\n"; break;
        case DIVR:
            o << "divr\n"; break;
    
        /* Conversion */
        case ITON:
            o << "iton\n"; break;
        case ITOR:
            o << "itor\n"; break;
        case RTOI:
            o << "rtoi\n"; break;

        /* Logic */
        case NOT:
            o << "not\n"; break;
        case AND:
            o << "and\n"; break;
        case OR:
            o << "or\n"; break;

        /* Compare */
        case EQI:
            o << "eqi\n"; break;
        case EQR:
            o << "eqr\n"; break;
        case LTI:
            o << "lti\n"; break;
        case LTR:
            o << "ltr\n"; break;
        case GTI:
            o << "gti\n"; break;
        case GTR:
            o << "gtr\n"; break;

        /* Conditional jumps */
        case IFT:
            o << "ift\t"; break;
        case IFF:
            o << "iff\t"; break;
        
        /* Flow */
        case GOTO:
            o << "goto\t"; break;
        case FRAME:
            o << "frame\n"; break;
        case INVK:
            o << "invk\t"; break;
        case RET:
            o << "ret\n"; break;
        case RETVAL:
            o << "retval\n"; break;
        case INTRNL:
            o << "intrnl\t"; break;

        /* Objects */
        case SIZE:
            o << "size\t"; break;
        case NEW:
            o << "new\n"; break;

        /* Exit */
        case EXIT:
            o << "exit\n"; break;

        /* If this happens, something is wrong. */
        default:
            o << data.i << std::endl; break;
        }
    } else {
        switch (type) {
        case ATOM_INTLIT:
            o << data.i << std::endl; break;
        case ATOM_REALLIT:
            o << data.r << std::endl; break;
        case ATOM_LABEL:
            o << label->name << ": (" << label->location << ")" << std::endl; break;
        case ATOM_REFERENCE:
            o << label->name << std::endl; break;
        }
    }
}

// ----------------------------------------------------------------------
// Bytecode

Bytecode::Bytecode() : size(0) {
    emitOp(FRAME);
    emitOp(INVK);
    emitReference(getLabel("main"));
    emitOp(EXIT);
}

Bytecode::~Bytecode() {
    int size = labels.size();
    for (int i = 0; i < size; ++i)
        delete labels[i];
}

Label* Bytecode::getLabel(const std::string& name) {
    int size = labels.size();
    for (int i = 0; i < size; ++i) {
        if (labels[i]->name == name)
            return labels[i];
    }

    labels.push_back(new Label(name));
    return labels[size];
}

Label* Bytecode::getUniqueLabel(const std::string& name) {
    static std::map<const std::string, int> unique;

    if (unique.count(name) == 0) {
        unique[name] = 0;
    } else {
        unique[name]++;
    }

    std::stringstream ss;
    ss << name << unique[name];

    return getLabel(ss.str());
 
}

void Bytecode::emitOp(unsigned char opcode) {
    word data;
    data.b[0] = opcode;

    code.push_back(Atom(ATOM_OP, data));
}

void Bytecode::emitInt(long long value) {
    word data;
    data.i = value;

    code.push_back(Atom(ATOM_INTLIT, data));
}

void Bytecode::emitReal(double value) {
    word data;
    data.r = value;

    code.push_back(Atom(ATOM_REALLIT, data));
}

void Bytecode::emitLabel(Label* label) {
    code.push_back(Atom(ATOM_LABEL, label));
}

void Bytecode::emitReference(Label* label) {
    code.push_back(Atom(ATOM_REFERENCE, label));
}

void Bytecode::analyze() {
    for (int i = 0; i < code.size(); ++i)
        size += code[i].analyze(size);
}

void Bytecode::write(const std::string& filename) {
    std::ofstream file(filename.c_str(), std::ios::binary);

    if (!file.is_open())
        return;

    long long magic = 987;
    file.write((char*)&magic, 8);
    file.write((char*)&size, 8);

    for (int i = 0; i < code.size(); ++i) {
        switch (code[i].type) {
        case ATOM_OP:
            file.write((char*)&code[i].data.b[0], 1);
            break;
        case ATOM_INTLIT:
        case ATOM_REALLIT:
            file.write((char*)&code[i].data, 8);
            break;
        case ATOM_REFERENCE:
            file.write((char*)&code[i].label->location, 8);
            break;
        }
    }

    file.close();
}

void Bytecode::show(std::ostream& o) {
    for (int i = 0; i < code.size(); ++i)
        code[i].show(o);
}
