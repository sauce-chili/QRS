//
// Created by sc on 17.04.24.
//
#ifndef MODULWORD_Q_RS_OPERATION_H
#define MODULWORD_Q_RS_OPERATION_H

#include "ExprNode.h"

/**
 * @brief Абстрактный класс для представления бинарных операций
 * */
class BinaryOperation : public ExprNode {
protected:
    bool compareParameters(const ExprNode *other) override;

public:
    ExprNode *leftOpr = nullptr; ///< левый операнд операции
    ExprNode *rightOpr = nullptr; ///< правый операнд операции

    /**
     * @param[in] leftOpr левый операнд операции
     * @param[out] rightOpr правый операнд операции
     * */
    BinaryOperation(ExprNode *leftOpr, ExprNode *rightOpr);

    std::string toString() const override;

    bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) override;

    bool isConstantExpr() const override;
};

/**
 * @brief Абстрактный класс для представления унарных операций
 * */
class UnaryOperation : public ExprNode {
protected:
    bool compareParameters(const ExprNode *other) override;

public:
    ExprNode *opr = nullptr; ///< операнд операции

    /**
     * @param[in] opr операнд операции
     * */
    explicit UnaryOperation(ExprNode *opr);

    std::string toString() const override;

    bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) override;

    bool isConstantExpr() const override;
};

#endif //MODULWORD_Q_RS_OPERATION_H
