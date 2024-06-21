//
// Created by sc on 17.04.24.
//

#include "Operation.h"
#include "../utils/BuilderUtils.h"

std::string BinaryOperation::toString() const {
    std::string result;
    const std::string wrapper[2] = {"(", ")"};
    result += precedence < leftOpr->getPrecedence() ?
              BuilderUtil::wrapIn(wrapper, leftOpr->toString())
                                                    :
              leftOpr->toString();

    result += BuilderUtil::getStrRepresentationNodeType(type);

    result += precedence < rightOpr->getPrecedence() ?
              BuilderUtil::wrapIn(wrapper, rightOpr->toString())
                                                     :
              rightOpr->toString();

    return result;
}

bool BinaryOperation::compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) {
    if(otherRoot == nullptr){
        pathToDiff += "nullptr";
        return false;
    }

    if (this == otherRoot) {
        return true;
    }

    bool result;

    if (*this == *otherRoot) {
        const auto *operation = dynamic_cast<const BinaryOperation *>(otherRoot);

        std::string path = BuilderUtil::getStrRepresentationNodeType(otherRoot->getNodeType()) + " -> ";
        bool leftIsEqual = this->leftOpr->compareExprTree(operation->leftOpr, path, current);

        if (not leftIsEqual) {
            pathToDiff += path;
            return false;
        }

        path = BuilderUtil::getStrRepresentationNodeType(otherRoot->getNodeType()) + " -> ";
        bool rightIsEqual = this->rightOpr->compareExprTree(operation->rightOpr, path, current);

        if (not rightIsEqual) {
            pathToDiff += path;
            return false;
        }

        result = true;
    } else {
        pathToDiff += BuilderUtil::getStrRepresentationNodeType(otherRoot->getNodeType());
        result = false;
    }

    return result;
}

BinaryOperation::BinaryOperation(ExprNode *leftOpr, ExprNode *rightOpr) {
    this->leftOpr = leftOpr;
    this->rightOpr = rightOpr;
}

bool BinaryOperation::compareParameters(const ExprNode *other) {
    if (*this != *other) {
        return false;
    }
    std::string diff;
    std::string buffer;
    const auto binaryOp = dynamic_cast<const BinaryOperation *>(other);
    bool leftCompare = this->leftOpr->compareExprTree(binaryOp->leftOpr, diff, buffer);

    if (not leftCompare) {
        return false;
    }
    buffer.clear();
    bool rightCompare = this->rightOpr->compareExprTree(binaryOp->rightOpr, diff, buffer);

    return rightCompare;
}


std::string UnaryOperation::toString() const {
    std::string result = BuilderUtil::getStrRepresentationNodeType(this->type);
    const std::string wrapper[2] = {"(", ")"};
    result += this->precedence < this->opr->getPrecedence() ?
              BuilderUtil::wrapIn(wrapper, this->opr->toString())
                                                            :
              this->opr->toString();

    return result;
}

bool UnaryOperation::compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) {
    if(otherRoot == nullptr){
        pathToDiff += "nullptr";
        return false;
    }

    if (this == otherRoot) {
        return true;
    }
    bool result = false;
    if (*this == *otherRoot) {

        const auto *operation = dynamic_cast<const UnaryOperation *>(otherRoot);

        std::string path = BuilderUtil::getStrRepresentationNodeType(otherRoot->getNodeType()) + " -> ";
        result = this->opr->compareExprTree(operation->opr, path, current);

        if (not result) {
            pathToDiff += path;
        }

    } else {
        pathToDiff += BuilderUtil::getStrRepresentationNodeType(otherRoot->getNodeType());
    }

    return result;
}

UnaryOperation::UnaryOperation(ExprNode *opr) {
    this->opr = opr;
}

bool UnaryOperation::compareParameters(const ExprNode *other) {
    if (*this != *other) {
        return false;
    }
    std::string diff;
    std::string buffer;
    const auto unaryOp = dynamic_cast<const UnaryOperation *>(other);
    bool resultCompare = this->opr->compareExprTree(unaryOp->opr, diff, buffer);

    return resultCompare;
}
