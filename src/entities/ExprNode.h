//
// Created by sc on 08.04.24.
//
#ifndef MODULWORD_Q_RS_EXPRNODE_H
#define MODULWORD_Q_RS_EXPRNODE_H

#include <iostream>
#include <map>
#include <vector>

#define NO_ID -1

/// Типы узлов
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
};

/*!
 * @class
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
     * @return элемент из @p params совпавший с @p this или nullptr, если @this не найден.
     * @example Одинаковыми будут считаться параметы a + b ^ c и b ^ c + a, однако a + (b ^ c) и (c ^ b) + a будут считаться разными параметрами
     * @see ExprNode::compareParameters
     * */
    virtual bool findParameter(std::vector<ExprNode *> &params); // метод поиска параметра

    /*!
     * @brief Метод сравнивает выражения с учётом коммутации верхнего уровня
     * @param[in] other выражение с которым происходит сравнение
     * @return true/false в зависимости от равенства параметров
     * @example Одинаковыми будут считаться параметы a + b ^ c и b ^ c + a, однако a + (b ^ c) и (c ^ b) + a будут считаться разными параметрами
     * */
    virtual bool compareParameters(const ExprNode *other); // методы сравнения параметров

public:
    /*!
     * @brief Метод вычисляет значение логического выражение
     * @param[in] args - значения принимаемые параметрами логического значения
     * @return значение логического выражения при заданном наборе значения параметров
     * */
    virtual bool calculate(unsigned short &args);

    /*!
     * @brief Метод преобразует дерево логического выражения в строковой формат
     * @return строковое представление дерева логического выражения
     * */
    virtual std::string toString() = 0;

    /*!
     * @brief Метод сравнивает узлы
     * @param[in] other узел, с которым происходит сравнение
     * @return true/false в зависимости от равенства узлов
     * */
    virtual bool operator==(const ExprNode &other) const;

    /*!
     * @brief Метод выполняет поиск параметров логического выражения
     * @details Метод начинает поиск параметров с левой ветки в узле, после переходит на правую.
     * При нахождение параметра узлу присваивается ID и он (если ещё не находится в @p params) добавляется
     * в выходной списко @p params
     * @param[in,out] params - заполняемые найденными параметрами список
     * */
    virtual void getParameters(std::vector<ExprNode *> &params);

    /*!
     * @brief Метод сравнивающая деревья
     * @param[in] other - дерево, которым идет сравнение
     * @return true/false в зависимости от эквивалентности деревьев
     * */
    virtual bool compareExprTree(const ExprNode *otherRoot, std::string &pathToDiff);

    /*!
     * @brief Метод возвращает приоритет узла
     * @return уровень приоритета узла
     * */
    int getPrecedence() const;

    /*!
     * @brief Метод возвращает индектификатор узла-параметра. Если узел не является параметром возвращается -1
     * @result id параметра
     * */
    int getParamID() const;
};

#endif //MODULWORD_Q_RS_EXPRNODE_H