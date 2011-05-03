#include "Node.h"

Node::Node(int lineNum) 
    : lineNum(lineNum) {}

std::string Node::indent(int i) {
    std::string ret;    

    for (int j = 0; j < i; ++j) {
        ret += "    ";
    }

    return ret;
}

