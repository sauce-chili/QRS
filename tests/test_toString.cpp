//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "utils/BuilderUtils.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/Exceptions.h"
#include "utils/Utils.h"
#include "TestUtils.h"

using namespace std;

struct ExprNodeToStringTestsParam {
    string testName;
    string buildString;
    string expected;
};

class ExprNodeToStringTest
        : public ::testing::TestWithParam<ExprNodeToStringTestsParam> {
};

TEST_P(ExprNodeToStringTest, ParseExprNodeTreeToStringTest) {
    auto params = GetParam();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    string actual = tree->toString();
    string expected = params.expected;

    removeWhiteSeparators(actual);
    removeWhiteSeparators(expected);

    EXPECT_EQ(actual, expected);
}

// TEST 1
static vector<ExprNodeToStringTestsParam> provideParseSimpleBinaryToStrTestCases() {

    const vector<pair<
            EXPR_NODE_TYPE, string
    >
    > binaryOperators = {
            {AND,         "AND"},
            {OR,          "OR"},
            {PLUS,        "PLUS"},
            {MINUS,       "MINUS"},
            {MUL,         "MUL"},
            {DIV,         "DIV"},
            {MOD,         "MOD"},
            {XOR,         "XOR"},
            {SHLA,        "SHLA"},
            {SHRA,        "SHRA"},
            {EQ,          "EQ"},
            {NEQ,         "NEQ"},
            {GREAT,       "GREAT"},
            {LESS,        "LESS"},
            {GREAT_OR_EQ, "GREAT_OR_EQ"},
            {LESS_OR_EQ,  "LESS_OR_EQ"}
    };
    vector<ExprNodeToStringTestsParam> testCases;


    for (const auto &op: binaryOperators) {
        string strOp = BuilderUtil::getStrRepresentationNodeType(op.first);
        testCases.push_back(
                {
                        "Parse_simple_binary_node_with_root_" + op.second,
                        "a b " + strOp,
                        "a" + strOp + "b"
                }
        );
    }

    return testCases;
}

static vector<ExprNodeToStringTestsParam> provideCommonTestCases() {
    return {
            // TEST 2
            {
                    "Parse_array_node_to_str",
                    "a i []",
                    "a[i]"
            },
            // TEST 3
            {
                    "Parse_simple_unary_node_with_root_UNARY_MINUS",
                    "a -$",
                    "-a"
            },
            // TEST 3
            {
                    "Parse_simple_unary_node_with_root_NOT",
                    "a !",
                    "!a"
            },
            // TEST 4
            {
                    "Parse_logical_node_with_logical_const_to_str",
                    "a true &&",
                    "a && true"
            },
            // TEST 5
            {
                    "Parse_arithmetical_node_with_arithmetical_const_to_str",
                    "a 0xFF *",
                    "a * 0xFF"
            },
            // TEST 6
            {
                    "Parse_arithmetical_tree_to_str",
                    "c b + a b - +",
                    "c + b + a - b"
            },
            // TEST 7
            {
                    "Parse_tree_with_nodes_different_precedence_lvl_to_str",
                    "c b + a a c - % *",
                    "(c + b) * a % (a - c)"
            },
            // TEST 8
            {
                    "Parse_array_tree_to_str",
                    "arr 1 + 0 a b + [] []",
                    "(arr+1)[0][a+b]",
            },
            // TEST 9
            {
                    "Parse_a_complex_tree_to_a_string_1",
                    "a i [] b * 5 -$ && ! x b a i [] * && ||",
                    "!(a[i] * b && -5) || x && b * a[i]"
            },
            // TEST 10
            {
                "Parse_a_complex_tree_to_a_string_2",
                "x ! a i [] b && -$ a i [] ! || && a i [] a i [] b && -$ x || && ||",
                "! x && (-(a[i] && b) || !a[i]) || a[i] && (-(a[i] && b) || x)"
            }
    };
}

static vector<ExprNodeToStringTestsParam> provideTestCases() {

    auto tests = {
            provideParseSimpleBinaryToStrTestCases(),
            provideCommonTestCases(),
    };

    vector<ExprNodeToStringTestsParam> testCases;
    for (auto tc: tests) {
        testCases.insert(testCases.end(), tc.begin(), tc.end());
    }

    return testCases;
}

INSTANTIATE_TEST_SUITE_P(
        ParseExprNodeTreeToStringTest,
        ExprNodeToStringTest,
        ::testing::ValuesIn(provideTestCases()),
        [](const testing::TestParamInfo<ExprNodeToStringTestsParam> &info) {
            return info.param.testName;
        }
);

