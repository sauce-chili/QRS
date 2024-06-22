////
//// Created by sc on 09.04.24.
////

#ifndef MODULEWORK_Q_RS_ARITHMETICNODE_H
#define MODULEWORK_Q_RS_ARITHMETICNODE_H

#include "utils/BuilderUtils.h"
#include "entities/Operation.h"

/**
 * @brief Реализация бинарной арифметической операции
 * */
class BinaryArithmeticNode : public BinaryOperation {
    std::function<double(double, double)> binaryCalculator; ///< функция для вычисления арифметического значения бинарной арифметической операции
public:
    /**
     * @param[in] type тип узла
     * @param[in] leftOpr левый операнд операции
     * @param[in] rightOpr правый операнд операции
     * */
    BinaryArithmeticNode(EXPR_NODE_TYPE type,
                         ExprNode *leftOpr,
                         ExprNode *rightOpr);

    bool calculate(unsigned short &args) override;
    double calculate() override;
};

/**
 * @brief Реализация унарной арифметической операции
 * */
class UnaryArithmeticNode : public UnaryOperation {
    std::function<double(double)> unaryCalculator; ///< ///< функция для вычисления арифметического значения унарной арифметической операции
public:
    /**
     * @param[in] type тип узла
     * @param[in] opr операнд операции
     * */
    UnaryArithmeticNode(EXPR_NODE_TYPE type, ExprNode *opr);

    bool calculate(unsigned short &args) override;
    double calculate() override;
};

/**
 * @brief Реализация бинарной коммутативных операций
 * @details Отличие от @p BinaryArithmeticNode заключается в том,
 * что при сравнение с другими коммутационными опециями проверяется коммутация корня выражения.
 * Коммутационными операциями являются:
 * @p EXPR_NODE_TYPE::MUL (*), @p EXPR_NODE_TYPE::PLUS (+),
 * @p EXPR_NODE_TYPE::XOR (^), @p EXPR_NODE_TYPE::EQ (==),@p EXPR_NODE_TYPE::NEQ (!=)
 * @example
 * Пример коммутационных операций:
 * a + b = b + a;
 * a * b = b * a;
 * a ^ b = b ^ a;
 * a == b = b == a;
 * a != b = b != a;
 * Более сложные пример:
 * (5 + x) * a = a * (5 + x), однако (5 + x) * a != (x + 5) * a
 * */
class CommutativeArithmeticNode : public BinaryArithmeticNode {
public:
    /**
     * @param[in] type тип узла
     * @param[in] leftOpr левый операнд операции
     * @param[in] rightOpr правый операнд операции
     * */
    CommutativeArithmeticNode(EXPR_NODE_TYPE type,
                              ExprNode *leftOpr,
                              ExprNode *rightOpr);

protected:
    bool compareParameters(const ExprNode *other) override;
};

/**
 * @brief Реализации узла-массива @p EXPR_NODE_TYPE::ARR ([])
 * */
class ArrayArithmeticNode : public CommutativeArithmeticNode {
public:
    /**
     * @param[in] leftOpr левый операнд операции
     * @param[in] rightOpr правый операнд операции
     * */
    ArrayArithmeticNode(ExprNode *leftOpr,
                        ExprNode *rightOpr);

    std::string toString() const override;

    bool isConstantExpr() const override;
};

#endif //MODULEWORK_Q_RS_ARITHMETICNODE_H
