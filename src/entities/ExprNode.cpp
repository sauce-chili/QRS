//
// Created by sc on 14.04.24.
//

#include "ExprNode.h"
#include <bits/stdc++.h>
#include <algorithm>


bool ExprNode::findParameter(std::vector<ExprNode *> &params) {
    bool result = std::ranges::any_of(params, [this](const auto& p) {
        std::string diff = "";
        return this->compareExprTree(p,diff);
    });
    return result;
}

bool ExprNode::calculate(unsigned short &args) {
    unsigned mask = 1 << (this->paramId - 1);
    unsigned short bit = (args & mask) ? 1 : 0;
    return bit;
}

void ExprNode::getParameters(std::vector<ExprNode *> &params) {
    if (findParameter(params)) return;

    this->paramId = params.size() + 1;
    params.push_back(this);
}

int ExprNode::getPrecedence() const {
    return this->precedence;
}

bool ExprNode::operator==(const ExprNode &other) const {
    return type==other.type && precedence == other.precedence;
}

std::string ExprNode::toString() {
    return "[ExprNode]";
}

bool ExprNode::compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff) {
    pathToDiff = "";
    return false;
}

bool ExprNode::compareParameters(const ExprNode *other) {
    return false;
}

