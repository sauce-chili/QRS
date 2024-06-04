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
#include "truthtablegererator/Generator.h"
#include <bitset>


using namespace std;
using ExceptionList = std::list<Exception>;

struct CreateRowTestParams {
    string testName;
    unsigned short args;
    unsigned short countArgs;
    bool result;
    string expectedRow;
};

class CreateRowTestDDT
        : public ::testing::TestWithParam<CreateRowTestParams> {
};

TEST_P(CreateRowTestDDT, CreateRowTest) {
    auto params = GetParam();

    string actualResult = TruthTableGenerator::createRow(
            params.args,
            params.countArgs,
            params.result
    );
    string expectedResult = params.expectedRow;

    EXPECT_EQ(actualResult, expectedResult);
}

vector<CreateRowTestParams> testCases = {
        {
            "One_parameter_and_result_expression_is_true",
            0b1,
            1,
            true,
            "<tr><td>0</td><td>0</td></tr>"
        },
        {
            "Multiple_parameters_and_result_expression_is_false",
            0b001,
            3,
            false,
                "<tr><td>1</td><td>0</td><td>0</td><td>0</td></tr>"
        },
        {
            "Max_numbers_of_parameters_and_result_is_false",
            0b1011011011,
            10,
            false,
            "<tr><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td>0</tr>"
        }
};

INSTANTIATE_TEST_SUITE_P(
        CreateRowTest,
        CreateRowTestDDT,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<CreateRowTestParams> &info) {
            return info.param.testName;
        }
);