//
// Created by sc on 09.04.24.
//

#ifndef MODULWORD_Q_RS_ARITHMETICNODE_H
#define MODULWORD_Q_RS_ARITHMETICNODE_H

#include "../ExprNode.h"

class ArithmeticNode : public ExprNode {

    bool isOperator() override;

    bool isCommutativeOperator() override;

    bool calculate(unsigned short &params) override;

    std::string toString() override;

public:
    ArithmeticNode(EXPR_NODE_TYPE type,
                   int priority,
                   bool isCommutativeOperator,
                   ExprNode *leftOpr,
                   ExprNode *rightOpr);

    bool operator==(const ExprNode &other) override;
};


#endif //MODULWORD_Q_RS_ARITHMETICNODE_H
