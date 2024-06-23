//
// Created by sc on 08.04.24.
//
#pragma once

#include <list>
#include <stack>
#include "entities/ExprNode.h"
#include "utils/BuilderUtils.h"
#include "exception/Exceptions.h"

class ExprNodeBuilder {

    /**
     * @brief Метод создаёт узел дерева на основе элемента выражения.
     *
     * @param elem [in] Элемент выражения.
     * @param idxElem [in] индекс элемента в выражении.
     * @param stack [in, out] стек для хранения узлов дерева и их индекса в выражении.
     *
     * @throw UnexpectedElementException если элемент выражения имеет неопределённый тип.
     * @throw MissingOperand Если недостаточно операндов для создания узла-оператора.
     */
    static void buildNode(const std::string &elem, int idxElem, std::stack<std::pair<int, ExprNode *>> &stack);

    /**
     * @brief Метод создаёт узел операции.
     *
     * @param type [in] тип узла операции.
     * @param idxOperation [in] индекс операции в выражении.
     * @param stack [in, out] стек для хранения узлов дерева и их индекса в выражении.
     *
     * @throw MissingOperand Если недостаточно операндов для создания операции.
     */
    static void buildOperationNode(EXPR_NODE_TYPE type,
                       int idxOperation,
                       std::stack<std::pair<int, ExprNode *>> &stack);

    /**
     * @brief Метод создаёт логический узел.
     *
     * @param type [in] тип логической операции.
     * @param idxOperation [in] индекс операции в записи выражения.
     * @param stack [in, out] стек для хранения узлов дерева и их индекса в выражении.
     */
    static void buildLogicalNode(EXPR_NODE_TYPE type,
                                 int idxOperation,
                                 std::stack<std::pair<int, ExprNode *>> &stack);

    /**
     * @brief Метод создаёт арифметический узел.
     *
     * @param type [in] тип арифметической операции.
     * @param idxOperation [in] индекс операции в записи выражения.
     * @param stack [in, out] стек для хранения узлов дерева и их индекса в выражении.
     */
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