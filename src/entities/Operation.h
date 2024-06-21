//
// Created by sc on 17.04.24.
//
#ifndef MODULWORD_Q_RS_OPERATION_H
#define MODULWORD_Q_RS_OPERATION_H

#include "ExprNode.h"

class BinaryOperation : public ExprNode {
protected:
    bool compareParameters(const ExprNode *other) override;

public:
    ExprNode *leftOpr = nullptr;
    ExprNode *rightOpr = nullptr;

    BinaryOperation(ExprNode *leftOpr, ExprNode *rightOpr);

    std::string toString() const override;

    bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) override;

    bool isConstantExpr() const override;
};

class UnaryOperation : public ExprNode {
protected:
    bool compareParameters(const ExprNode *other) override;

public:
    ExprNode *opr = nullptr;

    explicit UnaryOperation(ExprNode *opr);

    std::string toString() const override;

    bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) override;

    bool isConstantExpr() const override;
};

#endif //MODULWORD_Q_RS_OPERATION_H
