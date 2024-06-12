//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/BuildExceptions.h"

using namespace std;
using ExceptionList = std::list<Exception>;

struct CalculateTestParams {
    string testName;
    string buildString;
    unsigned short args;
    bool expected;
};

class CalculateTestDDT
        : public ::testing::TestWithParam<CalculateTestParams> {
};

TEST_P(CalculateTestDDT, CalculateTest) {
    auto params = GetParam();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    vector<ExprNode *> parameters;
    tree->getParameters(parameters);
    bool actualResult = tree->calculate(params.args);
    bool expectedResult = params.expected;

    EXPECT_EQ(actualResult, expectedResult);
}

const vector<CalculateTestParams> commonTestCases = {
        {
                "AND_with_parameters_value_00",
                "a b &&",
                0b00,
                false,
        },
        {
                "AND_with_parameters_value_01",
                "a b &&",
                0b10,
                false,
        },
        {
                "AND_with_parameters_value_10",
                "a b &&",
                0b01,
                false,
        },
        {
                "AND_with_parameters_value_11",
                "a b &&",
                0b11,
                false,
        },
        {
                "OR_with_parameters_value_00",
                "a b ||",
                0b00,
                false,
        },
        {
                "OR_with_parameters_value_01",
                "a b ||",
                0b10,
                true,
        },
        {
                "OR_with_parameters_value_10",
                "a b ||",
                0b01,
                true,
        },
        {
                "OR_with_parameters_value_11",
                "a b ||",
                0b11,
                true,
        },
        {
                "NOT_with_parameters_value_0",
                "a !",
                0b0,
                true
        },
        {
                "NOT_with_parameters_value_1",
                "a !",
                0b1,
                false
        },
        {
                "AND_with_constants",
                "a true 8.1 && &&",
                0b1,
                true
        },
        {
                "OR_with_constants",
                "a false 0 || ||",
                0b0,
                false
        },
        {
                "NOT_with_constant",
                "false !",
                0b0,
                true
        },
        {
                "The_whole_expression_consists_of_constants",
                "true false || 8.2 0b010 && ||",
                0b0,
                false,
        },
        {
                "The_whole_expression_consists_of_simple_parameters_1",
                "c a b && ||",
                0b110,
                true
        },
        {
                "The_whole_expression_consists_of_simple_parameters_2",
                "c a b && || !",
                0b110,
                false
        },
        {
                // !((a[i]*b)&&(-0xFA+5)) || x && (b*a[i]) && (c+k)
                "Calculation_of_complex_expression",
                "a i [] b * 0xFA -$ 5 + && ! x b a i [] * c k + && && ||",
                0b110,
                true
        }
};

INSTANTIATE_TEST_SUITE_P(
        CalculateTest,
        CalculateTestDDT,
        ::testing::ValuesIn(commonTestCases),
        [](const testing::TestParamInfo<CalculateTestParams> &info) {
            return info.param.testName;
        }
);