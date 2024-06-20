//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/BuildExceptions.h"
#include "TestUtils.h"

using namespace std;

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
        // TEST 1
        {
                "AND_with_parameters_value_00",
                "a b &&",
                0b00,
                false,
        },
        // TEST 2
        {
                "AND_with_parameters_value_01",
                "a b &&",
                0b10,
                false,
        },
        // TEST 3
        {
                "AND_with_parameters_value_10",
                "a b &&",
                0b01,
                false,
        },
        // TEST 4
        {
                "AND_with_parameters_value_11",
                "a b &&",
                0b11,
                true,
        },
        // TEST 5
        {
                "OR_with_parameters_value_00",
                "a b ||",
                0b00,
                false,
        },
        // TEST 6
        {
                "OR_with_parameters_value_01",
                "a b ||",
                0b10,
                true,
        },
        // TEST 7
        {
                "OR_with_parameters_value_10",
                "a b ||",
                0b01,
                true,
        },
        // TEST 8
        {
                "OR_with_parameters_value_11",
                "a b ||",
                0b11,
                true,
        },
        // TEST 9
        {
                "NOT_with_parameters_value_0",
                "a !",
                0b0,
                true
        },
        // TEST 10
        {
                "NOT_with_parameters_value_1",
                "a !",
                0b1,
                false
        },
        // TEST 11
        {
                "AND_with_constants",
                "a true 8.1 && &&",
                0b1,
                true
        },
        // TEST 12
        {
                "OR_with_constants",
                "a false 0 || ||",
                0b0,
                false
        },
        // TEST 13
        {
                "NOT_with_constant",
                "false !",
                0b0,
                true
        },
        // TEST 14
        {
                "The_whole_expression_consists_of_constants",
                "true false || 8.2 0b010 && ||",
                0b0,
                false,
        },
        // TEST 15
        {
                "The_whole_expression_consists_of_simple_parameters_1",
                "c a b && ||",
                0b110,
                true
        },
        // TEST 16
        {
                "The_whole_expression_consists_of_simple_parameters_2",
                "c a b && || !",
                0b110,
                false
        },
        // TEST 17
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