//
// Created by sc on 22.04.24.
//
#pragma once
#ifndef MODULWORD_Q_RS_OPERAND_H
#define MODULWORD_Q_RS_OPERAND_H

#include "ExprNode.h"

class Operand : public ExprNode {
protected:
    std::string value;
public:
    explicit Operand(std::string val);

    bool operator==(const ExprNode &other) const override;

    bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) override;

    std::string toString() const override;
};


#endif //MODULWORD_Q_RS_OPERAND_H
