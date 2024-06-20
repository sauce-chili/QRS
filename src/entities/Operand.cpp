//
// Created by sc on 22.04.24.
//

#include "Operand.h"
#include "utils/BuilderUtils.h"


bool Operand::compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) {
    bool result = *this == *otherRoot;

    if (not result){
        pathToDiff += otherRoot->toString();
    }

    return result;
}

std::string Operand::toString() const {
    return value;
}

bool Operand::operator==(const ExprNode &other) const {
    bool nodeEqual = ExprNode::operator==(other);
    const auto otherOperand = dynamic_cast<const Operand *>(&other);
    return nodeEqual && (otherOperand->value == this->value);
}

Operand::Operand(std::string val) {
    this->type = EXPR_NODE_TYPE::VAR;
    this->precedence = BuilderUtil::getPrecedenceLvl(type);
    this->value = val;
}
