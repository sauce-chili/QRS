//
// Created by sc on 08.04.24.
//
#ifndef MODULWORD_Q_RS_EXPRNODE_H
#define MODULWORD_Q_RS_EXPRNODE_H

#include <iostream>
#include <map>
#include <vector>

#define NO_ID -1

/**
 * @brief Типы узлов
 * */
enum EXPR_NODE_TYPE {
    NOT, ///< !
    AND, ///< &&
    OR, ///< ||
    PLUS, ///< +
    MINUS, ///< -
    UNARY_MINUS, ///< -$
    MUL, ///< *
    DIV, ///< /
    MOD, ///< %
    XOR, ///< ^
    SHLA, ///< <<
    SHRA, ///< >>
    EQ, ///< ==
    NEQ, ///< !=
    GREAT, ///< >
    LESS, ///< <
    GREAT_OR_EQ, ///< >=
    LESS_OR_EQ,///< <=,
    ARR, ///< []
    VAR,///< Какая-либо переменная
    CONST, ///< Констанста
    UNDEFINED /// < Используется для ошибок
};

/**
 * @brief Абстрактный класс узла выражения
 * */
class ExprNode {

protected:
    int paramId = NO_ID; ///< присваиваемый номер параметра
    int precedence; ///< приоритет узла
    EXPR_NODE_TYPE type; ///< тип узла

    /*!
     * @brief Метод ищет @p this в коллекции @p params, учитывая коммутацию верхнего узла
     * @details Метод выполняет поиск @p this в @p params, производя поэлементное сравнение с учетом коммутации операции
     * <u>корня</u>. Если @p this не найдет, то возврается nullptr. Для сравния параметров используется ExprNode::compareParameters
     * @param[in] params - список параметров, где будет выполняться поиск
     * @return элемент из @p params совпавший с @p this или nullptr, если @p this не найден.
     * @example Одинаковыми будут считаться параметы a + b ^ c и b ^ c + a, однако a + (b ^ c) и (c ^ b) + a будут считаться разными параметрами
     * @see ExprNode::compareParameters
     * */
     ExprNode* findParameter(std::vector<ExprNode *> &params); // метод поиска параметра

    /**
     * @brief Метод сравнивает выражения с учётом коммутации верхнего уровня
     * @param[in] other выражение с которым происходит сравнение
     * @return true/false в зависимости от равенства параметров
     * @example Одинаковыми будут считаться параметы a + b ^ c и b ^ c + a, однако a + (b ^ c) и (c ^ b) + a будут считаться разными параметрами
     * */
    virtual bool compareParameters(const ExprNode *other); // методы сравнения параметров

public:
    /**
     * @brief Метод вычисляет значение логического выражение
     * @param[in] args - значения принимаемые параметрами логического значения
     * @return значение логического выражения при заданном наборе значения параметров
     * */
    virtual bool calculate(unsigned short &args);

    /**
     * @brief Метод вычисляет арифметическое значение выражения.
     * @pre Перед вызовом необходимо проверить вычисляемое ли значение выражения арифметически
     * с помощью метода ExprNode::isConstantExpr. При попытке вызвать данный метод у дерева,
     * значение которого невозможно вычислить арифметически, будет выброшено исключение ArithmeticCalculationException.
     * @return значение дерева-выражения
     * @see ExprNode::isConstantExpr()
     * @see ArithmeticCalculationException
     * @throw ArithmeticCalculationException
     */
    virtual double calculate();

    /**
     * @brief Метод преобразует дерево логического выражения в строковой формат
     * @return строковое представление дерева логического выражения
     * */
    virtual std::string toString() const = 0;

    /**
     * @brief Метод сравнивает узлы
     * @param[in] other узел, с которым происходит сравнение
     * @return true/false в зависимости от равенства узлов
     * */
    virtual bool operator==(const ExprNode &other) const;

    /**
     * @brief Метод выполняет поиск параметров логического выражения
     * @details Метод начинает поиск параметров с левой ветки в узле, после переходит на правую.
     * При нахождение параметра узлу присваивается ID и он (если ещё не находится в @p params ) добавляется
     * в выходной списко @p params
     * @param[in,out] params - заполняемые найденными параметрами список
     * */
    virtual void getParameters(std::vector<ExprNode *> &params);

    /**
     * @brief Метод сравнивающий деревья
     * @param[in] other - дерево, которым идет сравнение
     * @param[in,out] pathToDiff - путь в дереве @p other до первого узла с которым наблюдается различие
     * @param[in] current - служебный буффер
     * @return true/false в зависимости от эквивалентности деревьев
     * */
    virtual bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff, std::string &current);

    /**
     * @brief Метод определяющий является ли выражение константным
     * @example Константное выражение: true && -(23 * 0x0FA)
     * @return true/false в зависимости от того является ли выржение константным
     * */
    virtual bool isConstantExpr() const;

    /**
     * @brief Метод возвращает приоритет узла
     * @return уровень приоритета узла
     * */
    int getPrecedence() const;

    /**
     * @brief Метод возвращает индектификатор узла-параметра. Если узел не является параметром возвращается -1
     * @result id параметра
     * */
    int getParamID() const;

    /**
     * @brief Метд возвращает тип узла
     * @return тип узла
     * */
    EXPR_NODE_TYPE getNodeType() const;
};

#endif //MODULWORD_Q_RS_EXPRNODE_H