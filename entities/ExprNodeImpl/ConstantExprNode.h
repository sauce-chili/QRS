//
// Created by sc on 14.04.24.
//

#ifndef MODULWORD_Q_RS_CONSTANTEXPRNODE_H
#define MODULWORD_Q_RS_CONSTANTEXPRNODE_H


#include "../ExprNode.h"

class ConstantExprNode : public ExprNode {
     std::string value;

    ConstantExprNode(std::string value);

    bool calculate(unsigned short &params) override;
};


#endif //MODULWORD_Q_RS_CONSTANTEXPRNODE_H
