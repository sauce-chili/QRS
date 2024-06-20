//
// Created by sc on 09.04.24.
//
#include "LogicalNode.h"


bool LogicalNodeAND::calculate(unsigned short &params) {
    bool result = this->leftOpr->calculate(params) && this->rightOpr->calculate(params);
    return result;
}

LogicalNodeAND::LogicalNodeAND(ExprNode *leftOpr, ExprNode *rightOpr) : BinaryLogicalOperation(leftOpr, rightOpr) {
    type = EXPR_NODE_TYPE::AND;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

bool LogicalNodeOR::calculate(unsigned short &params) {
    bool result = this->leftOpr->calculate(params) || this->rightOpr->calculate(params);
    return result;
}

LogicalNodeOR::LogicalNodeOR(ExprNode *leftOpr, ExprNode *rightOpr) : BinaryLogicalOperation(leftOpr, rightOpr) {
    type = EXPR_NODE_TYPE::OR;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

bool LogicalNodeNOT::calculate(unsigned short &params) {
    bool result = not this->opr->calculate(params);
    return result;
}

LogicalNodeNOT::LogicalNodeNOT(ExprNode *opr) : UnaryBinaryOperation(opr) {
    type = EXPR_NODE_TYPE::NOT;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

void BinaryLogicalOperation::getParameters(std::vector<ExprNode *> &params) {
    this->leftOpr->getParameters(params);
    this->rightOpr->getParameters(params);
}

BinaryLogicalOperation::BinaryLogicalOperation(ExprNode *leftOpr, ExprNode *rightOpr) : BinaryOperation(leftOpr,
                                                                                                        rightOpr) {
    this->leftOpr = leftOpr;
    this->rightOpr = rightOpr;
}

void UnaryBinaryOperation::getParameters(std::vector<ExprNode *> &params) {
    this->opr->getParameters(params);
}

UnaryBinaryOperation::UnaryBinaryOperation(ExprNode *opr) : UnaryOperation(opr) {
    this->opr = opr;
}
