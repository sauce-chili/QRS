//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/Exceptions.h"
#include "truthtablegererator/Generator.h"
#include "TestUtils.h"

using namespace std;

struct GenerateTableTestParams {
    string testName;
    string buildString;
    vector<string> expectedHeader;
    vector<vector<string>> expectedRowValues;
    bool is_throwable = false;
};

class GenerateTableTestDDT
        : public ::testing::TestWithParam<GenerateTableTestParams> {
};

TEST_P(GenerateTableTestDDT, GenerateTableTest) {
    auto params = GetParam();

    ExceptionList exps;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(params.buildString, exps);

    string actualTable;

    if (params.is_throwable) {
        EXPECT_THROW(
                TruthTableGenerator::generateTable(tree),
                ExceedingLimitParametersException
        );
    } else {
        actualTable = TruthTableGenerator::generateTable(tree);
    }

    vector<string> expectedHeader = params.expectedHeader;
    vector<vector<string>> expectedRowsValues = params.expectedRowValues;

    vector<string> actualHeader = extractHeaders(actualTable);
    vector<vector<string>> actualRowsValues = extractValues(actualTable);

    EXPECT_EQ(expectedHeader, actualHeader);
    EXPECT_EQ(expectedRowsValues, actualRowsValues);
}

const vector<GenerateTableTestParams> commonTestCases = {
        // TEST 1
        {
                "Generate_table_with_one_parameter",
                "true a -$ 0xFA + &&",
                {"-a+0xFA", "F"},
                {
                        {"0", "0"},
                        {"1", "1"}
                }
        },
        // TEST 2 !(a[i]*b && -0xFA + 5) || x  && c+k
        {
                "Generate_table_with_several_parameters",
                "a i [] b * 0xFA -$ 5 + && ! x c k + && ||",
                {"a[i]*b",    "x",          "c+k", "F"},
                {
                        // <td>0</td><td>0</td><td>0</td><td>1</td>
                        {"0", "0", "0", "0"},
                        // <td>0</td><td>0</td><td>1</td><td>1</td>
                        {"0", "0", "1", "1"},
                        // <td>0</td><td>1</td><td>0</td><td>1</td>
                        {"0", "1", "0", "1"},
                        // <td>0</td><td>1</td><td>1</td><td>1</td>
                        {"0", "1", "1", "1"},
                        // <td>1</td><td>0</td><td>0</td><td>0</td>
                        {"1", "0", "0", "0"},
                        // <td>1</td><td>0</td><td>1</td><td>0</td>
                        {"1", "0", "1", "0"},
                        // <td>1</td><td>1</td><td>0</td><td>0</td>
                        {"1", "1", "0", "0"},
                        // <td>1</td><td>1</td><td>1</td><td>1</td>
                        {"1", "1", "1", "1"}
                },
        },
        // TEST 3
        {
                "Generating_table_with_several_parameters_including_commutative_parameters",
                "a i [] b * 0xFA -$ 5 + && ! x b a i [] * c k + && && ||",
                {"a[i]*b",    "x",          "c+k", "F"},
                {
                        // <td>0</td><td>0</td><td>0</td><td>1</td>
                        {"0", "0", "0", "1"},
                        // <td>0</td><td>0</td><td>1</td><td>1</td>
                        {"0", "0", "1", "1"},
                        // <td>0</td><td>1</td><td>0</td><td>1</td>
                        {"0", "1", "0", "1"},
                        // <td>0</td><td>1</td><td>1</td><td>1</td>
                        {"0", "1", "1", "1"},
                        // <td>1</td><td>0</td><td>0</td><td>0</td>
                        {"1", "0", "0", "0"},
                        // <td>1</td><td>0</td><td>1</td><td>0</td>
                        {"1", "0", "1", "0"},
                        // <td>1</td><td>1</td><td>0</td><td>0</td>
                        {"1", "1", "0", "0"},
                        // <td>1</td><td>1</td><td>1</td><td>1</td>
                        {"1", "1", "1", "1"}
                }
        },
        // TEST 4
        // ! x && (-(a[i] && b) || !a[i]) || a[i] && (-(a[i] && b) || x)
        {
                "One_parameter_is_nested_within_another",
                "x ! a i [] b && -$ a i [] ! || && a i [] a i [] b && -$ x || && ||",
                {"x",         "-(a[i]&&b)", "a[i]"},
                {
                        {"0", "0", "0", "1"},
                        {"0", "0", "1", "0"},
                        {"0", "1", "0", "0"},
                        {"0", "1", "1", "1"},
                        {"1", "0", "0", "1"},
                        {"1", "0", "1", "1"},
                        {"1", "1", "0", "0"},
                        {"1", "1", "1", "1"}
                }
        },
        // TEST 5
        {
                "Parameter_limit_exceeded",
                "p1 p2 p3 p4 p5 p6 p7 p8 p9 p10 p11 || || || || || || || || || || ||",
                {},
                {},
                true
        }
};

INSTANTIATE_TEST_SUITE_P(
        GenerateTableTest,
        GenerateTableTestDDT,
        ::testing::ValuesIn(commonTestCases),
        [](const testing::TestParamInfo<GenerateTableTestParams> &info) {
            return info.param.testName;
        }
);