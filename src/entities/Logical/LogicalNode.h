//
// Created by sc on 08.04.24.
//

#ifndef MODULWORD_Q_RS_LOGICALNODEIMPL_H
#define MODULWORD_Q_RS_LOGICALNODEIMPL_H

#include "entities/Operation.h"
#include "utils/BuilderUtils.h"

class BinaryLogicalOperation : public BinaryOperation {
public:
    BinaryLogicalOperation(ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &params) override = 0;

    double calculate() override = 0;

    void getParameters(std::vector<ExprNode *> &params) override;
};

class UnaryBinaryOperation : public UnaryOperation {
public:
    explicit UnaryBinaryOperation(ExprNode *opr);

    bool calculate(unsigned short &params) override = 0;

    double calculate() override = 0;

    void getParameters(std::vector<ExprNode *> &params) override;
};

class LogicalNodeAND : public BinaryLogicalOperation {
public:
    LogicalNodeAND(ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &params) override;

    double calculate() override;
};

class LogicalNodeOR : public BinaryLogicalOperation {
public :
    LogicalNodeOR(ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &params) override;

    double calculate() override;
};

class LogicalNodeNOT : public UnaryBinaryOperation {

public:
    explicit LogicalNodeNOT(ExprNode *opr);

    bool calculate(unsigned short &params) override;

    double calculate() override;
};

#endif //MODULWORD_Q_RS_LOGICALNODEIMPL_H
