//
// Created by sc on 14.04.24.
//
#pragma once
#ifndef MODULWORD_Q_RS_CONSTANTEXPRNODE_H
#define MODULWORD_Q_RS_CONSTANTEXPRNODE_H


#include "../Operand.h"

class ConstantExprNode : public Operand {
    double numValue;
public:
    explicit ConstantExprNode(std::string val);

    bool calculate(unsigned short &params) override;
    bool operator==(const ExprNode &other) const override;
    bool isConstantExpr() const override;
};


#endif //MODULWORD_Q_RS_CONSTANTEXPRNODE_H
