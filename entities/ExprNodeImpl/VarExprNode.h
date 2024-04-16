//
// Created by sc on 14.04.24.
//

#ifndef MODULWORD_Q_RS_VAREXPRNODE_H
#define MODULWORD_Q_RS_VAREXPRNODE_H

#include "../ExprNode.h"

class VariableNode : public ExprNode {
    std::string value;
public:
    VariableNode(std::string value);

    bool calculate(unsigned short &params) override;
};

#endif //MODULWORD_Q_RS_VAREXPRNODE_H
