//
// Created by sc on 14.04.24.
//

#include "ConstantExprNode.h"

bool ConstantExprNode::calculate(unsigned short &params) {
    if (value == "true")
    {
        return true;
    }
    else if (value == "false")
    {
        return false;
    }

    bool result;
    std::istringstream(value) >> std::boolalpha >> result;
    return result;
}

ConstantExprNode::ConstantExprNode(std::string value) {
    this->value = value;
}
