//
// Created by sc on 14.04.24.
//
#pragma once
#ifndef MODULWORD_Q_RS_CONSTANTEXPRNODE_H
#define MODULWORD_Q_RS_CONSTANTEXPRNODE_H


#include "entities/Operand.h"

/**
 * @brief Класс для представления узлов-констант
 * */
class ConstantExprNode : public Operand {
    double numValue; ///< числовое представление значения операнда

    /**
     * @brief Конвертирует значение операнда в числовое представление
     * @param[in]val конвертируемое значение
     * @return числовое представление значения операнда
     * */
    double parseToNumValue(std::string val);
public:
    explicit ConstantExprNode(std::string val);
    bool calculate(unsigned short &params) override;
    double calculate() override;
    bool operator==(const ExprNode &other) const override;
    bool isConstantExpr() const override;
};


#endif //MODULWORD_Q_RS_CONSTANTEXPRNODE_H
