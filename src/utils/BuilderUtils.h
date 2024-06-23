//
// Created by sc on 22.04.24.
//
#pragma once
#ifndef MODULEWORK_Q_RS_BUILDERUTILS_H
#define MODULEWORK_Q_RS_BUILDERUTILS_H


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <functional>
#include "entities/ExprNode.h"

/**
 * @brief Вспомогательный класс используемый для построения дерева
 * */
class BuilderUtil {
    // "&&", "||", "!"
    static std::unordered_set<EXPR_NODE_TYPE> logicalOperation; ///< набор логических операторов

    // "*", "+", "^", "==", "!="
    static std::unordered_set<EXPR_NODE_TYPE> commutativeOperation; ///< набор коммутативных операций

    static std::unordered_map<EXPR_NODE_TYPE, int> precedence; ///< словарь приоритов

    static std::unordered_map<std::string, EXPR_NODE_TYPE> operatorsNodeTypes; ///< словарь сопоставления строковой записи операции к типу операции @p EXPR_NODE_TYPE

    static std::unordered_map<EXPR_NODE_TYPE, std::string> strOperationNodeType; ///< словарь строковых представлений операций

    static std::unordered_map<EXPR_NODE_TYPE, std::function<double(double, double)>> binaryArithmeticalCalculator; ///< словарь функций, вычисляющих арифметическое значение данной бинарной операции */

    static std::unordered_map<EXPR_NODE_TYPE, std::function<double(double)>> unaryArithmeticalCalculator; ///< словарь функций, вычисляющих арифметическое значение данной унарной операции */

    /**
     * @brief Метод проверяет является переданный параметр @p str константой
     * @param[in] str проверяемая строка
     * @return true/false в зависимости от того является ли @p str константой
     * @example Примеры_констант\n true/false; 32; 0xFA; 20.3; 20.3f; 25L; 1.04E+3
     * */
    static bool isConstantStr(const std::string &str);

    /**
     * @brief Метод проверяет является переданный параметр @p str переменной
     * @param[in] str проверяемая строка
     * @return true/false в зависимости от того является ли @p str переменной
     * */
    static bool isVariableStr(const std::string &str);

public:

    /**
     * @brief Метод возвращает тип операции строкового представляения операции
     * @details В случае если не удалось определить тип операции возвращается @p EXPR_NODE_TYPE::UNDEFINED
     * @param[in] str строковая запись операции
     * @return тип операции
     * */
    static EXPR_NODE_TYPE getNodeType(std::string str);

    /**
     * @brief Метод возвращает строковое представление операции типа @p type
     * @param[in] type тип операции
     * @return строковое представление операции типа @p type
     * */
    static std::string getStrRepresentationNodeType(EXPR_NODE_TYPE type);

    /**
     * @brief Метод возвращает функцию соответсвующую бинарной операции @p type, которая вычисляет арифметичесоке значение узла
     * @param[in] type тип операции
     * @return вычисляющая арифметическое значение бинарной операции функция
     * */
    static std::function<double(double, double)> getBinaryArithmeticalCalculator(EXPR_NODE_TYPE type);

    /**
     * @brief Метод возвращает функцию соответсвующую унарной операции @p type, которая вычисляет арифметичесоке значение узла
     * @param[in] type тип операции
     * @return вычисляющая арифметическое значение унарной операции функция
     * */
    static std::function<double(double)> getUnaryArithmeticalCalculator(EXPR_NODE_TYPE type);

    /**
     * @brief Метод возвращает уровень приоритета операции @p type
     * @param[in] type тип операции
     * @return уровень приоритета
     * */
    static int getPrecedenceLvl(const EXPR_NODE_TYPE &type);

    /**
     * @brief Метод проверяет является ли операция @p op бинарной
     * @param[in] op проверяемая операция
     * @return true/false в зависимости от того является ли @p op бинарной операцией
     * */
    static bool isBinaryOperation(const EXPR_NODE_TYPE &op);

    /**
     * @brief Метод проверяет является ли операция @p op логической операцией
     * @param[in] op проверяемая операция
     * @return true/false в зависимости от того является ли @p op логической операцией
     * */
    static bool isLogicalOperation(const EXPR_NODE_TYPE &op);

    /**
     * @brief Метод проверяет является ли операция @p op арифметической операцией
     * @param[in] op проверяемая операция
     * @return true/false в зависимости от того является ли @p op арифметической операцией
     * */
    static bool isArithmeticalOperation(const EXPR_NODE_TYPE &op);

    /**
     * @brief Метод проверяет является ли операция @p op коммутативной операцией
     * @param[in] op проверяемая операция
     * @return true/false в зависимости от того является ли @p op коммутативной операцией
     * */
    static bool isCommutativeOperation(const EXPR_NODE_TYPE &op);

};

#endif //MODULEWORK_Q_RS_BUILDERUTILS_H
