////
//// Created by sc on 09.04.24.
////

#ifndef MODULWORD_Q_RS_ARITHMETICNODE_H
#define MODULWORD_Q_RS_ARITHMETICNODE_H

#include "../Operation.h"
#include "../../utils/BuilderUtils.h"

class BinaryArithmeticNode : public BinaryOperation {
    std::function<double(double, double)> binaryCalculator;
public:
    BinaryArithmeticNode(EXPR_NODE_TYPE type,
                         ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &args) override;
    double calculate() override;
};

class UnaryArithmeticNode : public UnaryOperation {
    std::function<double(double)> unaryCalculator;
public:
    UnaryArithmeticNode(EXPR_NODE_TYPE type, ExprNode *opr);

    bool calculate(unsigned short &args) override;
    double calculate() override;
};

// Commutative operation
class CommutativeArithmeticNode : public BinaryArithmeticNode {
public:
    CommutativeArithmeticNode(EXPR_NODE_TYPE type,
                              ExprNode *leftOpr,
                              ExprNode *rightOpr);

protected:
    bool compareParameters(const ExprNode *other) override;
};

// Implementation
class ArrayArithmeticNode : public CommutativeArithmeticNode {
public:
    ArrayArithmeticNode(ExprNode *leftOpr,
                        ExprNode *rightOpr);

    std::string toString() const override;

    bool isConstantExpr() const override;
};

#endif //MODULWORD_Q_RS_ARITHMETICNODE_H
