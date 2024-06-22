//
// Created by sc on 22.04.24.
//
#pragma once
#ifndef MODULEWORK_Q_RS_OPERAND_H
#define MODULEWORK_Q_RS_OPERAND_H

#include "ExprNode.h"

/**
 * @brief Класс для представления узлов-операндов
 * */
class Operand : public ExprNode {
protected:
    std::string value; ///< значение операнда
public:
    explicit Operand(std::string val);

    bool operator==(const ExprNode &other) const override;

    bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current) override;

    std::string toString() const override;
};


#endif //MODULEWORK_Q_RS_OPERAND_H
