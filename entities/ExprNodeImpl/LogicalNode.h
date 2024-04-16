//
// Created by sc on 08.04.24.
//

#include "../ExprNode.h"
#include "../../utils/BuilderUtils.h"

#ifndef MODULWORD_Q_RS_LOGICALNODEIMPL_H
#define MODULWORD_Q_RS_LOGICALNODEIMPL_H

class BaseLogicalNode : public ExprNode {
    bool operator==(const ExprNode &other) override;

protected:
    bool isOperator() override;

    bool isCommutativeOperator() override;
};

class LogicalNodeAND : public BaseLogicalNode {
public:
    LogicalNodeAND(ExprNode *leftOpr, ExprNode *rightOpr);

    std::string toString() override;

    bool calculate(unsigned short &params) override;
};

class LogicalNodeOR : BaseLogicalNode {
public :
    LogicalNodeOR(ExprNode *leftOpr, ExprNode *rightOpr);

private:
    std::string toString() override;

public:
    bool calculate(unsigned short &params) override;
};

class LogicalNodeNOT : BaseLogicalNode {
public:
private:
    std::string toString() override;

public:
    LogicalNodeNOT(ExprNode *opr);

    bool calculate(unsigned short &params) override;
};

#endif //MODULWORD_Q_RS_LOGICALNODEIMPL_H
