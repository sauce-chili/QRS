//
// Created by sc on 09.04.24.
//
#include "LogicalNode.h"


bool LogicalNodeAND::calculate(unsigned short &params) {
    bool leftResult = this->leftOpr->calculate(params);
    bool rightResult = this->rightOpr->calculate(params);
    bool result = leftResult && rightResult;
    return result;
}

LogicalNodeAND::LogicalNodeAND(ExprNode *leftOpr, ExprNode *rightOpr) : BinaryLogicalOperation(leftOpr, rightOpr) {
    type = EXPR_NODE_TYPE::AND;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

double LogicalNodeAND::calculate() {
    double leftResult = this->leftOpr->calculate();
    double rightResult = this->rightOpr->calculate();
    double result = leftResult && rightResult;

    return result;
}

bool LogicalNodeOR::calculate(unsigned short &params) {
    bool leftResult = this->leftOpr->calculate(params);
    bool rightResult = this->rightOpr->calculate(params);
    bool result = leftResult || rightResult;
    return result;
}

LogicalNodeOR::LogicalNodeOR(ExprNode *leftOpr, ExprNode *rightOpr) : BinaryLogicalOperation(leftOpr, rightOpr) {
    type = EXPR_NODE_TYPE::OR;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

double LogicalNodeOR::calculate() {
    double leftResult = this->leftOpr->calculate();
    double rightResult = this->rightOpr->calculate();
    double result = leftResult || rightResult;

    return result;
}

bool LogicalNodeNOT::calculate(unsigned short &params) {
    bool result = not this->opr->calculate(params);
    return result;
}

LogicalNodeNOT::LogicalNodeNOT(ExprNode *opr) : UnaryBinaryOperation(opr) {
    type = EXPR_NODE_TYPE::NOT;
    precedence = BuilderUtil::getPrecedenceLvl(type);
}

double LogicalNodeNOT::calculate() {
    double oprValue = this->opr->calculate();

    return not oprValue;
}

void BinaryLogicalOperation::getParameters(std::vector<ExprNode *> &params) {
    this->leftOpr->getParameters(params);
    this->rightOpr->getParameters(params);
}

BinaryLogicalOperation::BinaryLogicalOperation(ExprNode *leftOpr, ExprNode *rightOpr) : BinaryOperation(leftOpr,
                                                                                                        rightOpr) {
}

void UnaryBinaryOperation::getParameters(std::vector<ExprNode *> &params) {
    this->opr->getParameters(params);
}

UnaryBinaryOperation::UnaryBinaryOperation(ExprNode *opr) : UnaryOperation(opr) {
}
