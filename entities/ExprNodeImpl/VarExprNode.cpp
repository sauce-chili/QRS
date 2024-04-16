//
// Created by sc on 14.04.24.
//

#include "VarExprNode.h"

bool VariableNode::calculate(unsigned short &params) {
    return false;
}

VariableNode::VariableNode(std::string value) {
    this->value =  value;
}

