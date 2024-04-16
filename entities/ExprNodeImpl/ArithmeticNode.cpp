//
// Created by sc on 09.04.24.
//

#include "ArithmeticNode.h"

ArithmeticNode::ArithmeticNode(EXPR_NODE_TYPE type,
                               int priority,
                               bool isCommutativeOperator,
                               ExprNode *leftOpr,
                               ExprNode *rightOpr

) {
    this->type = type;
    this->priority = priority;
    this->leftOpr = leftOpr;
    this->rightOpr = rightOpr;
}

bool ArithmeticNode::isOperator() {
    return false;
}

bool ArithmeticNode::isCommutativeOperator() {
    return false;
}

bool ArithmeticNode::calculate(unsigned short &params) {
    return false;
}

std::string ArithmeticNode::toString() {
    return std::string();
}

bool ArithmeticNode::operator==(const ExprNode &other) {
    return false;
}
