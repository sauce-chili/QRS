//
// Created by sc on 08.04.24.
//
#pragma once

#include <list>
#include <stack>
#include "../entities/ExprNode.h"
#include "../utils/BuilderUtils.h"
#include "exception/Exceptions.h"

class ExprNodeBuilder {

    static void buildNode(const std::string &elem, int idxElem, std::stack<std::pair<int, ExprNode *>> &stack);

    static void buildOperationNode(EXPR_NODE_TYPE type,
                       int idxOperation,
                       std::stack<std::pair<int, ExprNode *>> &stack);

    static void buildLogicalNode(EXPR_NODE_TYPE type,
                                 int idxOperation,
                                 std::stack<std::pair<int, ExprNode *>> &stack);

    static void buildArithmeticalNode(EXPR_NODE_TYPE type,
                                      int idxOperation,
                                      std::stack<std::pair<int, ExprNode *>> &stack);


public:
    /*!
     * @brief Функция создания дерева из строки разбора выражения
     * @details Функция принимает строку в обратной польльской нотации и строит по ней дерево логического выражения.
     * В случае выявления ошибок в записи дерева, ошибку добавляются в список exps. Если после exps.size() != 0, то
     * функция возвращает nullptr
     * @param[in] postfixExpr - строка разбора логического выражения
     * @param[in,out] exps - список выявленных ошибок при построение дерева
     * @return указатель на корень дерева или nullptr, если при построении дерева возникли ошибки
     * */
    static ExprNode *buildExprTree(std::string postfixExpr, std::list<Exception> &exps);
};