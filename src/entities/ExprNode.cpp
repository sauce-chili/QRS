//
// Created by sc on 14.04.24.
//

#include "ExprNode.h"
#include "utils/Utils.h"
#include "utils/BuilderUtils.h"
#include <bits/stdc++.h>
#include <algorithm>
#include "exception/Exceptions.h"


ExprNode *ExprNode::findParameter(std::vector<ExprNode *> &params) {
    auto it = std::find_if(params.begin(), params.end(), [this](ExprNode *param) {
        return this->compareParameters(param);
    });

    return (it != params.end()) ? *it : nullptr;
}

bool ExprNode::calculate(unsigned short &args) {
    return extractBitOfNumber(args, paramId);
}

void ExprNode::getParameters(std::vector<ExprNode *> &params) {

    if (isConstantExpr()) {
        return;
    }

    auto foundParam = findParameter(params);

    if (foundParam != nullptr) {
        this->paramId = foundParam->paramId;
        return;
    }

    this->paramId = params.size() + 1;
    params.push_back(this);
}

int ExprNode::getPrecedence() const {
    return this->precedence;
}

std::string ExprNode::toString() const {
    return "[ExprNode]";
}

bool ExprNode::operator==(const ExprNode &other) const {
    return type == other.type && precedence == other.precedence;
}

bool ExprNode::isConstantExpr() const {
    return false;
}

int ExprNode::getParamID() const {
    return paramId;
}

EXPR_NODE_TYPE ExprNode::getNodeType() const {
    return type;
}

bool ExprNode::compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) {
    bool result = *this == *otherRoot;

    if (not result){
        pathToDiff += BuilderUtil::getStrRepresentationNodeType(otherRoot->getNodeType());
    }

    return result;
}

bool ExprNode::compareParameters(const ExprNode *other) {
    std::string diff;
    std::string buffer;
    return compareExprTree(other,diff, buffer);
}

double ExprNode::calculate() {
    throw ArithmeticCalculationException();
}
