//
// Created by sc on 08.04.24.
//
#include <bits/stdc++.h>

#ifndef MODULWORD_Q_RS_EXPRNODE_H
#define MODULWORD_Q_RS_EXPRNODE_H

#include <iostream>
#include <map>
#include <vector>

#define NO_ID -1

enum EXPR_NODE_TYPE {
    NOT, // !
    AND, // &&
    OR, // ||
    PLUS, // +
    MINUS, // -
    UNARY_MINUS, // -$
    MUL, // *
    DIV, // /
    MOD, // %
    XOR, // ^
    SHLA, // <<
    SHRA, // >>
    EQ, // ==
    NEQ, // !=
    GREAT, // >
    LESS, // <
    GREAT_OR_EQ, // >=
    LESS_OR_EQ,// <=,
    ARR, // []
    VAR,
    CONST,
};

class ExprNode {

private:
    int paramId = NO_ID;
protected:
    int priority;
    EXPR_NODE_TYPE type;

    virtual bool isOperator() = 0;

    virtual bool isCommutativeOperator() = 0;

public:
    ExprNode *leftOpr = nullptr;
    ExprNode *rightOpr = nullptr;

    virtual bool calculate(unsigned short &params) = 0;

    virtual std::string toString() = 0;

    virtual bool operator==(const ExprNode &other) const = 0;

    virtual void getParameters(const ExprNode *root, std::vector<ExprNode *> &params);

    bool compareExprTree(const ExprNode *otherRoot);
};

#endif //MODULWORD_Q_RS_EXPRNODE_H
