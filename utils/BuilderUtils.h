//
// Created by sc on 08.04.24.
//
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <climits>
#include "../entities/ExprNode.h"

class BuilderUtil {

    // "&&", "||", "!"
    std::unordered_set<EXPR_NODE_TYPE> logicalOperation = {
            EXPR_NODE_TYPE::AND, EXPR_NODE_TYPE::OR, EXPR_NODE_TYPE::NOT
    };

    // "*", "+", "^", "==", "!="
    std::unordered_set<EXPR_NODE_TYPE> commutativeOperation = {
            EXPR_NODE_TYPE::MUL, EXPR_NODE_TYPE::PLUS, EXPR_NODE_TYPE::XOR, EXPR_NODE_TYPE::EQ, EXPR_NODE_TYPE::NEQ
    };

    std::unordered_map<EXPR_NODE_TYPE, int> priority = {
            {EXPR_NODE_TYPE::ARR,         2}, // []
            {EXPR_NODE_TYPE::UNARY_MINUS, 3}, // -%
            {EXPR_NODE_TYPE::NOT,         3}, // !
            {EXPR_NODE_TYPE::MUL,         5}, // *
            {EXPR_NODE_TYPE::DIV,         5}, // /
            {EXPR_NODE_TYPE::DIV,         5}, // %
            {EXPR_NODE_TYPE::PLUS,        6}, // +
            {EXPR_NODE_TYPE::MINUS,       6}, // -
            {EXPR_NODE_TYPE::SHLA,        7}, // <<
            {EXPR_NODE_TYPE::SHRA,        7}, // >>
            {EXPR_NODE_TYPE::LESS,        9}, // <
            {EXPR_NODE_TYPE::LESS_OR_EQ,  9}, // <=
            {EXPR_NODE_TYPE::GREAT,       9}, // >
            {EXPR_NODE_TYPE::GREAT_OR_EQ, 9}, // >=
            {EXPR_NODE_TYPE::EQ,          10}, // ==
            {EXPR_NODE_TYPE::NEQ,         10}, // !=
            {EXPR_NODE_TYPE::XOR,         12}, // ^
            {EXPR_NODE_TYPE::AND,         14}, // &&
            {EXPR_NODE_TYPE::OR,          15}, // ||
            {EXPR_NODE_TYPE::VAR,   INT16_MAX}, // variable
            {EXPR_NODE_TYPE::CONST, INT16_MAX} // const
    };

    std::unordered_map<std::string, EXPR_NODE_TYPE> operatorsNodeTypes = {
            {"[]", EXPR_NODE_TYPE::ARR},
            {"-$", EXPR_NODE_TYPE::UNARY_MINUS},
            {"!",  EXPR_NODE_TYPE::NOT},
            {"*",  EXPR_NODE_TYPE::MUL},
            {"/",  EXPR_NODE_TYPE::DIV},
            {"%",  EXPR_NODE_TYPE::MOD},
            {"+",  EXPR_NODE_TYPE::PLUS},
            {"-",  EXPR_NODE_TYPE::MINUS},
            {"<<", EXPR_NODE_TYPE::SHLA},
            {">>", EXPR_NODE_TYPE::SHRA},
            {"<",  EXPR_NODE_TYPE::LESS},
            {"<=", EXPR_NODE_TYPE::LESS_OR_EQ},
            {">",  EXPR_NODE_TYPE::GREAT},
            {">=", EXPR_NODE_TYPE::LESS_OR_EQ},
            {"==", EXPR_NODE_TYPE::EQ},
            {"!=", EXPR_NODE_TYPE::NEQ},
            {"^",  EXPR_NODE_TYPE::XOR},
            {"&&", EXPR_NODE_TYPE::AND},
            {"||", EXPR_NODE_TYPE::OR}
    };


    bool isConstant(const std::string &str);

    bool isVariable(const std::string &str);

public:

    EXPR_NODE_TYPE getNodeType(std::string str);

    int getPriorityLvl(const EXPR_NODE_TYPE &type);

    bool isBinaryOperation(const EXPR_NODE_TYPE &op);

    bool isLogicalOperation(const EXPR_NODE_TYPE &op);

    bool isArithmeticalOperation(const EXPR_NODE_TYPE &op);

    bool isCommutativeOperation(const EXPR_NODE_TYPE &op);
};