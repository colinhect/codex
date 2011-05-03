#ifndef _BYTECODE_
#define _BYTECODE_

#include "../vm/word.h"
#include "../vm/bytecode.h"

#include <iostream>
#include <string>
#include <vector>

// ----------------------------------------------------------------------
// Label

class Label {
public:

    std::string name;   // The name of the label.
    long long location; // Location in the code the label points to.
                        // A value of -1 means the label does not point
                        // to anything yet.

    Label(std::string name);

};

// ----------------------------------------------------------------------
// AtomType

enum AtomType {
    ATOM_OP,
    ATOM_INTLIT,
    ATOM_REALLIT,
    ATOM_LABEL,
    ATOM_REFERENCE
};

// ----------------------------------------------------------------------
// Atom

class Atom {
public:

    AtomType type;
    word data;
    Label* label;

    Atom(AtomType type, word data);
    Atom(AtomType type, Label* label);
    long long analyze(long long location);
    void show(std::ostream& o);

};

// ----------------------------------------------------------------------
// Bytecode

class Bytecode {
private:

    std::vector<Label*> labels;
    std::vector<Atom> code;
    long long size;

public:

    Bytecode();
    ~Bytecode();

    Label* getLabel(const std::string& name);
    Label* getUniqueLabel(const std::string& name);

    void emitOp(unsigned char opcode);
    void emitInt(long long value);
    void emitReal(double value);
    void emitLabel(Label* label);
    void emitReference(Label* label);

    void analyze();

    void write(const std::string& filename);

    void show(std::ostream& o);

};

#endif
