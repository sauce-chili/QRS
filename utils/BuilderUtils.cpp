//
// Created by sc on 14.04.24.
//
#include "BuilderUtils.h"

int BuilderUtil::getPriorityLvl(const EXPR_NODE_TYPE &op) {
    return this->priority[op];
}

bool BuilderUtil::isBinaryOperation(const EXPR_NODE_TYPE &op) {
    return op != EXPR_NODE_TYPE::UNARY_MINUS && op != EXPR_NODE_TYPE::NOT;
}

bool BuilderUtil::isLogicalOperation(const EXPR_NODE_TYPE &op) {
    this->logicalOperation.contains(op);
}

bool BuilderUtil::isArithmeticalOperation(const EXPR_NODE_TYPE &op) {
    return not this->isLogicalOperation(op);
}

bool BuilderUtil::isCommutativeOperation(const EXPR_NODE_TYPE &op) {
    return this->commutativeOperation.contains(op);
}

bool BuilderUtil::isConstant(const std::string &str) {
    if (str.empty()) return false;
    if (str == "true" || str == "false") return true;
    if (str.size() == 1) {
        return isdigit(str[0]);
    }
    if (str.size() >= 2) {
        return isdigit(str[0]) || isdigit(str[1]) && (str[0] == '-' || str[0] == '+');
    }

    return false;
}

bool BuilderUtil::isVariable(const std::string &str) {
    if (str.empty()) return false;

    return str[0] == '_' || isalpha(str[0]);
}

EXPR_NODE_TYPE BuilderUtil::getNodeType(const std::string str) {
    if (isConstant(str))
        return EXPR_NODE_TYPE::CONST;
    else if (isVariable(str))
        return EXPR_NODE_TYPE::VAR;

    return this->operatorsNodeTypes[str];
}
