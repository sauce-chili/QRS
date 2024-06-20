////
//// Created by sc on 09.04.24.
////

#ifndef MODULWORD_Q_RS_ARITHMETICNODE_H
#define MODULWORD_Q_RS_ARITHMETICNODE_H

#include "../Operation.h"
#include "../../utils/BuilderUtils.h"

class BinaryArithmeticNode : public BinaryOperation {
public:
    BinaryArithmeticNode(EXPR_NODE_TYPE type,
                         ExprNode *leftOpr, ExprNode *rightOpr);
    bool isConstantExpr() const override;
};

class UnaryArithmeticNode : public UnaryOperation {
public:
    UnaryArithmeticNode(EXPR_NODE_TYPE type, ExprNode *opr);
    bool isConstantExpr() const override;
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
};

#endif //MODULWORD_Q_RS_ARITHMETICNODE_H
