//
// Created by sc on 14.04.24.
//

#include "ConstantExprNode.h"
#include "utils/BuilderUtils.h"
#include <bits/stdc++.h>
#include <utility>
#include "utils/Utils.h"

bool ConstantExprNode::calculate(unsigned short &params) {
    return (bool) numValue;
}

ConstantExprNode::ConstantExprNode(std::string val) : Operand(val) {
    this->type = EXPR_NODE_TYPE::CONST;
    this->precedence = BuilderUtil::getPrecedenceLvl(type);
    this->numValue = convertToDecimal(val);
}

bool ConstantExprNode::isConstantExpr() const {
    return true;
}

bool ConstantExprNode::operator==(const ExprNode &other) const {
    if (Operand::operator==(other)) {
        return true;
    }

    const auto c = dynamic_cast<const ConstantExprNode *>(&other);

    return numValue == c->numValue;
}
