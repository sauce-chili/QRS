////
//// Created by sc on 09.04.24.
////

#include "ArithmeticNode.h"

bool CommutativeArithmeticNode::compareParameters(const ExprNode *other) {
    if (*this != *other) {
        return false;
    }

    const auto binaryParam = dynamic_cast<const BinaryArithmeticNode *>(other);
    bool baseCompare = BinaryOperation::compareParameters(other);

    if (baseCompare) {
        return true;
    }

    std::string diff;
    std::string buffer;

    // TODO split it
    bool commutativeCompare = this->leftOpr->compareExprTree(binaryParam->rightOpr, diff, buffer)
                              && this->rightOpr->compareExprTree(binaryParam->leftOpr, diff, buffer);

    return commutativeCompare;
}

CommutativeArithmeticNode::CommutativeArithmeticNode(EXPR_NODE_TYPE type, ExprNode *leftOpr, ExprNode *rightOpr)
        : BinaryArithmeticNode(type, leftOpr, rightOpr) {

}

std::string ArrayArithmeticNode::toString() const {
    std::string result;
    const std::string wrapper[2] = {"(", ")"};

    // Если leftOpr ссылается на операцию, добавляем скобки вокруг toString() вызова
    if (dynamic_cast<BinaryOperation *>(leftOpr) || dynamic_cast<UnaryOperation *>(leftOpr)) {
        result += BuilderUtil::wrapIn(wrapper, this->leftOpr->toString());
    } else {
        result += this->leftOpr->toString();
    }

    ExprNode *rightNode = this->rightOpr;

    const std::string arrayWrapper[2] = {"[", "]"};
    // Проверяем, является ли rightOpr узлом типа ArrayArithmeticNode
    while (auto arrayNode = dynamic_cast<const ArrayArithmeticNode *>(rightNode)) {
        result += BuilderUtil::wrapIn(arrayWrapper, arrayNode->leftOpr->toString());
        rightNode = arrayNode->rightOpr;
    }

    // Добавляем конечный индекс
    result += BuilderUtil::wrapIn(arrayWrapper, rightNode->toString());
    return result;
}

ArrayArithmeticNode::ArrayArithmeticNode(ExprNode *leftOpr, ExprNode *rightOpr)
        : CommutativeArithmeticNode(EXPR_NODE_TYPE::ARR, leftOpr, rightOpr) {

}

BinaryArithmeticNode::BinaryArithmeticNode(EXPR_NODE_TYPE type,
                                           ExprNode *leftOpr, ExprNode *rightOpr) : BinaryOperation(leftOpr, rightOpr) {
    this->type = type;
    this->precedence = BuilderUtil::getPrecedenceLvl(type);
}

bool BinaryArithmeticNode::isConstantExpr() const {
    bool leftIsConstExpr = leftOpr->isConstantExpr();
    bool rightIsConstExpr = rightOpr->isConstantExpr();

    return leftIsConstExpr && rightIsConstExpr;
};

UnaryArithmeticNode::UnaryArithmeticNode(EXPR_NODE_TYPE type, ExprNode *opr) : UnaryOperation(opr) {
    this->type = type;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

bool UnaryArithmeticNode::isConstantExpr() const {
    return opr->isConstantExpr();
}
