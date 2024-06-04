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
#include <bitset>


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

    vector<ExprNode*> parameters;
    tree->getParameters(parameters);
    bool actualResult = tree->calculate(params.args);
    bool expectedResult = params.expected;

    EXPECT_EQ(actualResult,expectedResult);
}

vector<CalculateTestParams> testCases = {
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
            "a !",
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
                "The_whole_expression_consists_of_simple_parameters",
                "c a b && ||",
                0b110,
                true
        },
        {
            // !((a[i]*b)&&(-0xFA+5)) || x && (b*a[i]) && (c+k)
            "Сalculation_of_complex_expression",
            "a i [] b * 0xFA -$ 5 + && ! x b a i [] * c k + && && ||",
            0b110,
            true
        }
};

INSTANTIATE_TEST_SUITE_P(
        CalculateTest,
        CalculateTestDDT,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<CalculateTestParams> &info) {
            return info.param.testName;
        }
);