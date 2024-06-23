//
// Created by sc on 22.04.24.
//

#include <regex>
#include "BuilderUtils.h"
#include "Utils.h"

std::unordered_set<EXPR_NODE_TYPE> BuilderUtil::logicalOperation = {
        EXPR_NODE_TYPE::AND, EXPR_NODE_TYPE::OR, EXPR_NODE_TYPE::NOT
};

std::unordered_map<EXPR_NODE_TYPE, int> BuilderUtil::precedence = {
        {EXPR_NODE_TYPE::ARR,         2}, // []
        {EXPR_NODE_TYPE::UNARY_MINUS, 3}, // -$
        {EXPR_NODE_TYPE::NOT,         3}, // !
        {EXPR_NODE_TYPE::MUL,         5}, // *
        {EXPR_NODE_TYPE::DIV,         5}, // /
        {EXPR_NODE_TYPE::MOD,         5}, // %
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
        {EXPR_NODE_TYPE::VAR,   INT16_MIN}, // variable
        {EXPR_NODE_TYPE::CONST, INT16_MIN} // const
};

std::unordered_map<std::string, EXPR_NODE_TYPE> BuilderUtil::operatorsNodeTypes = {
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
        {">=", EXPR_NODE_TYPE::GREAT_OR_EQ},
        {"==", EXPR_NODE_TYPE::EQ},
        {"!=", EXPR_NODE_TYPE::NEQ},
        {"^",  EXPR_NODE_TYPE::XOR},
        {"&&", EXPR_NODE_TYPE::AND},
        {"||", EXPR_NODE_TYPE::OR}
};

std::unordered_map<EXPR_NODE_TYPE, std::string> BuilderUtil::strOperationNodeType = {

        {EXPR_NODE_TYPE::ARR,         "[]"},
        {EXPR_NODE_TYPE::UNARY_MINUS, "-"},
        {EXPR_NODE_TYPE::NOT,         "!"},
        {EXPR_NODE_TYPE::MUL,         "*"},
        {EXPR_NODE_TYPE::DIV,         "/"},
        {EXPR_NODE_TYPE::MOD,         "%"},
        {EXPR_NODE_TYPE::PLUS,        "+"},
        {EXPR_NODE_TYPE::MINUS,       "-"},
        {EXPR_NODE_TYPE::SHLA,        "<<"},
        {EXPR_NODE_TYPE::SHRA,        ">>"},
        {EXPR_NODE_TYPE::LESS,        "<"},
        {EXPR_NODE_TYPE::LESS_OR_EQ,  "<="},
        {EXPR_NODE_TYPE::GREAT,       ">"},
        {EXPR_NODE_TYPE::GREAT_OR_EQ, ">="},
        {EXPR_NODE_TYPE::EQ,          "=="},
        {EXPR_NODE_TYPE::NEQ,         "!="},
        {EXPR_NODE_TYPE::XOR,         "^"},
        {EXPR_NODE_TYPE::AND,         "&&"},
        {EXPR_NODE_TYPE::OR,          "||"}
};

std::unordered_map<EXPR_NODE_TYPE, std::function<double(double, double)>> BuilderUtil::binaryArithmeticalCalculator = {
        {MUL, [](double l, double r) -> double { return l * r; }},
        {DIV, [](double l, double r) -> double { return l / r; }},
        {MOD, [](double l, double r) -> double { return (int) l << (int) r; }},
        {PLUS, [](double l, double r) -> double { return l + r; }},
        {MINUS, [](double l, double r) -> double { return l - r; }},
        {SHLA, [](double l, double r) -> double { return (int) l << (int) r; }},
        {SHRA, [](double l, double r) -> double { return (int) l >> (int) r; }},
        {LESS, [](double l, double r) -> double { return l < r; }},
        {LESS_OR_EQ, [](double l, double r) -> double { return l <= r; }},
        {GREAT, [](double l, double r) -> double { return l > r; }},
        {GREAT_OR_EQ, [](double l, double r) -> double { return l >= r; }},
        {EQ, [](double l, double r) -> double { return l == r; }},
        {NEQ, [](double l, double r) -> double { return l != r; }},
        {XOR, [](double l, double r) -> double { return (int) l ^ (int) r; }},
};

std::unordered_map<EXPR_NODE_TYPE, std::function<double(double)>> BuilderUtil::unaryArithmeticalCalculator = {
        {UNARY_MINUS, [](double o) -> double { return -o; }}
};

std::unordered_set<EXPR_NODE_TYPE> BuilderUtil::commutativeOperation = {
        EXPR_NODE_TYPE::MUL, EXPR_NODE_TYPE::PLUS, EXPR_NODE_TYPE::XOR, EXPR_NODE_TYPE::EQ, EXPR_NODE_TYPE::NEQ
};

int BuilderUtil::getPrecedenceLvl(const EXPR_NODE_TYPE &type) {
    return precedence[type];
}

bool BuilderUtil::isBinaryOperation(const EXPR_NODE_TYPE &op) {
    return op != EXPR_NODE_TYPE::UNARY_MINUS && op != EXPR_NODE_TYPE::NOT;
}

bool BuilderUtil::isLogicalOperation(const EXPR_NODE_TYPE &op) {
    return logicalOperation.contains(op);
}

bool BuilderUtil::isArithmeticalOperation(const EXPR_NODE_TYPE &op) {
    return not isLogicalOperation(op);
}

bool BuilderUtil::isCommutativeOperation(const EXPR_NODE_TYPE &op) {
    return commutativeOperation.contains(op);
}

bool BuilderUtil::isConstantStr(const std::string &str) {
    if (str.empty()) return false;
    if (str == "true" || str == "false") return true;
    if (isDecimal(str) || isBinary(str) || isOctal(str) || isHexadecimal(str)) return true;
    return false;
}

bool BuilderUtil::isVariableStr(const std::string &str) {
    if (str.empty()) return false;

    std::regex validCppVarNameMask(R"(^[a-zA-Z_][a-zA-Z0-9_]*$)");
    return std::regex_match(str, validCppVarNameMask);
}

EXPR_NODE_TYPE BuilderUtil::getNodeType(const std::string str) {
    if (isConstantStr(str))
        return EXPR_NODE_TYPE::CONST;
    else if (isVariableStr(str))
        return EXPR_NODE_TYPE::VAR;
    else if (operatorsNodeTypes.contains(str)) {
        return operatorsNodeTypes[str];
    }

    return EXPR_NODE_TYPE::UNDEFINED;
}

std::string BuilderUtil::getStrRepresentationNodeType(EXPR_NODE_TYPE type) {
    return strOperationNodeType[type];
}

std::function<double(double, double)> BuilderUtil::getBinaryArithmeticalCalculator(EXPR_NODE_TYPE type) {
    return binaryArithmeticalCalculator[type];
}

std::function<double(double)> BuilderUtil::getUnaryArithmeticalCalculator(EXPR_NODE_TYPE type) {
    return unaryArithmeticalCalculator[type];
}
