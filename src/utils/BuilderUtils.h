//
// Created by sc on 22.04.24.
//
#pragma once
#ifndef MODULWORD_Q_RS_BUILDERUTILS_H
#define MODULWORD_Q_RS_BUILDERUTILS_H


#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include <functional>
#include "entities/ExprNode.h"


class BuilderUtil {
    // "&&", "||", "!"
    static std::unordered_set<EXPR_NODE_TYPE> logicalOperation; // список логических операторов

    // "*", "+", "^", "==", "!="
    static std::unordered_set<EXPR_NODE_TYPE> commutativeOperation; // список коммутативных операций

    static std::unordered_map<EXPR_NODE_TYPE, int> precedence; // словарь приоритов

    static std::unordered_map<std::string, EXPR_NODE_TYPE> operatorsNodeTypes; // словарь возможных операций

    static std::unordered_map<EXPR_NODE_TYPE, std::string> strOperationNodeType; // словарь символьного представления операции

    static std::unordered_map<EXPR_NODE_TYPE, std::function<double(double, double)>> binaryArithmeticalCalculator;

    static std::unordered_map<EXPR_NODE_TYPE, std::function<double(double)>> unaryArithmeticalCalculator;

    static bool isConstantStr(const std::string &str);

    static bool isVariableStr(const std::string &str);

public:

    static EXPR_NODE_TYPE getNodeType(std::string str);

    static std::string getStrRepresentationNodeType(EXPR_NODE_TYPE type);

    static std::function<double(double, double)> getBinaryArithmeticalCalculator(EXPR_NODE_TYPE type);

    static std::function<double(double)> getUnaryArithmeticalCalculator(EXPR_NODE_TYPE type);

    static int getPrecedenceLvl(const EXPR_NODE_TYPE &type);

    static bool isBinaryOperation(const EXPR_NODE_TYPE &op);

    static bool isLogicalOperation(const EXPR_NODE_TYPE &op);

    static bool isArithmeticalOperation(const EXPR_NODE_TYPE &op);

    static bool isCommutativeOperation(const EXPR_NODE_TYPE &op);

    static std::string wrapIn(const std::string wrapper[2], const std::string &wrapable);
};

#endif //MODULWORD_Q_RS_BUILDERUTILS_H
