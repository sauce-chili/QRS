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
#include "exception/Exceptions.h"
#include "truthtablegererator/Generator.h"
#include "TestUtils.h"


using namespace std;

struct CreateRowTestParams {
    string testName;
    unsigned short args;
    unsigned short countArgs;
    bool result;
    vector<string> expectedRowValues;
};

class CreateRowTestDDT
        : public ::testing::TestWithParam<CreateRowTestParams> {
};

TEST_P(CreateRowTestDDT, CreateRowTest) {
    auto params = GetParam();

    string actualRow = TruthTableGenerator::createRow(
            params.args,
            params.countArgs,
            params.result
    );
    vector<string> actualRowValues = extractRowData(actualRow);
    vector<string> expectedRowValues = params.expectedRowValues;

    EXPECT_EQ(expectedRowValues, actualRowValues);;
}

const vector<CreateRowTestParams> commonTestCases = {
        // TEST 1
        {
                "One_parameter_and_result_expression_is_true",
                0b1,
                1,
                true,
                //"<tr><td>0</td><td>0</td></tr>"
                {"1", "1"}
        },
        // TEST 2
        {
                "Multiple_parameters_and_result_expression_is_false",
                0b001,
                3,
                false,
                //"<tr><td>1</td><td>0</td><td>0</td><td>0</td></tr>"
                {"1", "0", "0", "0"}
        },
        // TEST 3
        {
                "Max_numbers_of_parameters_and_result_is_false",
                0b1011011011,
                10,
                false,
                // "<tr><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>0</td><td>1</td><td>1</td><td>1</td>0</tr>"
                { "1", "1", "0", "1", "1", "0", "1", "1", "0", "1", "0"}
        }
};

INSTANTIATE_TEST_SUITE_P(
        CreateRowTest,
        CreateRowTestDDT,
        ::testing::ValuesIn(commonTestCases),
        [](const testing::TestParamInfo<CreateRowTestParams> &info) {
            return info.param.testName;
        }
);