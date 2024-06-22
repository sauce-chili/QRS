//
// Created by sc on 08.04.24.
//

#ifndef MODULWORD_Q_RS_LOGICALNODEIMPL_H
#define MODULWORD_Q_RS_LOGICALNODEIMPL_H

#include "entities/Operation.h"
#include "utils/BuilderUtils.h"

/**
 * @brief Абстрактный класс для реализации бинарных логических операций
 **/
class BinaryLogicalOperation : public BinaryOperation {
public:
    /**
     * @param[in] leftOpr левый операнд операции
     * @param[out] rightOpr правый операнд операции
     * */
    BinaryLogicalOperation(ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &params) override = 0;

    double calculate() override = 0;

    void getParameters(std::vector<ExprNode *> &params) override;
};

/**
 * @brief Абстрактный класс для реализации унарных логических операций
 **/
class UnaryBinaryOperation : public UnaryOperation {
public:
    /**
     * @param[in] opr операнд операции
     * */
    explicit UnaryBinaryOperation(ExprNode *opr);

    bool calculate(unsigned short &params) override = 0;

    double calculate() override = 0;

    void getParameters(std::vector<ExprNode *> &params) override;
};

/**
 * Реализация операции @p AND(&&)
 * */
class LogicalNodeAND : public BinaryLogicalOperation {
public:
    /**
     * @param[in] leftOpr левый операнд операции
     * @param[out] rightOpr правый операнд операции
     * */
    LogicalNodeAND(ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &params) override;

    double calculate() override;
};

/**
 * Реализация операции @p OR(||)
 * */
class LogicalNodeOR : public BinaryLogicalOperation {
public :
    /**
     * @param[in] leftOpr левый операнд операции
     * @param[out] rightOpr правый операнд операции
     * */
    LogicalNodeOR(ExprNode *leftOpr, ExprNode *rightOpr);

    bool calculate(unsigned short &params) override;

    double calculate() override;
};

/**
 * Реализация операции @p NOT(!)
 * */
class LogicalNodeNOT : public UnaryBinaryOperation {

public:
    /**
     * @param[in] opr операнд операции
     * */
    explicit LogicalNodeNOT(ExprNode *opr);

    bool calculate(unsigned short &params) override;

    double calculate() override;
};

#endif //MODULWORD_Q_RS_LOGICALNODEIMPL_H
