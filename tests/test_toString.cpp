//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/ExprNode.h"
#include "entities/Logical/LogicalNode.h"
#include "entities/Constant/ConstantExprNode.h"
#include "entities/Arithmetic/ArithmeticNode.h"
#include "utils/BuilderUtils.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/BuildExceptions.h"
#include <memory>

using namespace std;

TEST(ExprNodeToString, BinaryOperationToString) {

    std::vector<EXPR_NODE_TYPE> binaryOperators = {
            AND, OR, PLUS, MINUS, MUL, DIV, MOD, XOR, SHLA, SHRA, EQ, NEQ, GREAT, LESS, GREAT_OR_EQ, LESS_OR_EQ
    };

    bool result = true;

    for (EXPR_NODE_TYPE op: binaryOperators) {
        string strOp = BuilderUtil::getStrNodeType(op);
        string inStr = "a b " + strOp;

        list<Exception> exps;
        ExprNode *root = ExprNodeBuilder::buildExprTree(inStr, exps);

        string expectedStr = "a" + strOp + "b";
        string actualStr = root->toString();

        delete root;

        if (expectedStr != actualStr) {
            result = false;
            break;
        }
    }

    EXPECT_TRUE(result);
}

TEST(ExprNodeToString, UnaryOperationToString) {
    std::vector<EXPR_NODE_TYPE> unaryOperation = {UNARY_MINUS, NOT};

    bool result = true;

    for (EXPR_NODE_TYPE op: unaryOperation) {
        string strOp = BuilderUtil::getStrNodeType(op);
        string inStr = "a " + strOp;

        list<Exception> exps;
        ExprNode *root = ExprNodeBuilder::buildExprTree(inStr, exps);

        string expectedStr = strOp + "a";
        string actualStr = root->toString();

        delete root;

        if (expectedStr != actualStr) {
            result = false;
            break;
        }
    }

    EXPECT_TRUE(result);
}

using ExceptionList = std::list<Exception>;

struct ExprNodeToStringParams {
    string testName;
    string buildString;
    string expected;
};

class ExprNodeToStringTestDDT
        : public ::testing::TestWithParam<ExprNodeToStringParams> {
};

TEST_P(ExprNodeToStringTestDDT, ExprNodeToString) {
    auto params = GetParam();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    string actual = tree->toString();
    string expected = params.expected;

    bool result = actual == expected;

    EXPECT_TRUE(result);
}

vector<ExprNodeToStringParams> testCases = {
        {
                "Parse_array_node_to_str",
                "a i []",
                "a[i]"
        },
        {
            "Parse_logical_node_with_logical_const_to_str",
            "a true &&",
            "a&&true"
        },
        {
            "Parse_arithmetical_node_with_arithmetical_const_to_str",
            "a 0xFF *",
            "a*0xFF"
        },
        {
            "Parse_arithmetical_tree_to_str",
            "c b + a b − +",
            "c+b+a-b"
        },
        {
            "Parse_tree_with_nodes_different_precedence_lvl_to_str",
            "c b + a a c - % *",
            "(c+b)∗(a%(a−c))"
        },
        {
            "Parse_array_tree_to_str",
            "arr 1 + 0 a b + [] []",
            "(arr+1)[0][a+b]",
        },
        {
            "Parse_a_complex_tree_to_a_string",
            "a i [] b * -5 && ! x b a i [] * && ||",
            "!((a[i]*b)&&-5)||(x && (b*a[i]))"
        }

};

INSTANTIATE_TEST_SUITE_P(
        ExprNodeToString,
        ExprNodeToStringTestDDT,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<ExprNodeToStringParams> &info) {
            return info.param.testName;
        }
);

