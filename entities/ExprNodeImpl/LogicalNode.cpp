//
// Created by sc on 09.04.24.
//
#include "LogicalNode.h"

bool BaseLogicalNode::operator==(const ExprNode &other) {
    if (this == &other) return true;
    if (typeid(*this) != typeid(other)) {
        return false;
    }
    const auto &o = dynamic_cast<const BaseLogicalNode &>(other);

    return this->priority == o.priority && this->type == o.type;
}


LogicalNodeAND::LogicalNodeAND(ExprNode* leftOpr, ExprNode* rightOpr) {
    this->leftOpr = leftOpr;
    this->rightOpr = rightOpr;
    this->type = EXPR_NODE_TYPE::AND;
    this->priority = BuilderUtil().getPriorityLvl(this->type);
}

bool LogicalNodeAND::calculate(unsigned short &params) {
    return false;
}

std::string LogicalNodeAND::toString() {
    return std::string();
}

LogicalNodeOR::LogicalNodeOR(ExprNode* leftOpr, ExprNode* rightOpr) {
    this->leftOpr = leftOpr;
    this->rightOpr = rightOpr;
    this->type = EXPR_NODE_TYPE::OR;
    this->priority = BuilderUtil().getPriorityLvl(this->type);
}

bool LogicalNodeOR::calculate(unsigned short &params) {
    return false;
}

std::string LogicalNodeOR::toString() {
    return std::string();
}

LogicalNodeNOT::LogicalNodeNOT(ExprNode* opr) {
    this->leftOpr = opr;
    this->type = EXPR_NODE_TYPE::NOT;
    this->priority = BuilderUtil().getPriorityLvl(this->type);
}

bool LogicalNodeNOT::calculate(unsigned short &params) {
    return false;
}

std::string LogicalNodeNOT::toString() {
    return std::string();
}
