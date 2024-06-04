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

struct GenerateTableTestParams {
    string testName;
    string buildString;
    string expectedTable
};

class GenerateTableTestDDT
        : public ::testing::TestWithParam<GenerateTableTestParams> {
};

TEST_P(GenerateTableTestDDT, GenerateTableTest) {
    auto params = GetParam();

    string actualResult = TruthTableGenerator::createRow(
            params.args,
            params.countArgs,
            params.result
    );
    string expectedResult = params.expectedRow;

    EXPECT_EQ(actualResult, expectedResult);
}

vector<GenerateTableTestParams> testCases = {
        {
                "Generate_table_with_one_parameter",
                "true a -$ 0xFA + &&",
                R"SONG(
<table>
<tr>
    <td>a+(-0xFA)</td><td>F</td>
</tr>
<tr>
    <td>0</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>1</td>
</tr>
</table>
)SONG"
        },
        {
                "Generate_table_with_several_parameters",
                "a i [] b * 0xFA -$ 5 + && ! x c k + && ||",
                R"SONG(
<table>
<tr>
    <td>a[i]*b</td><td>x</td><td>c+k</td><td>F</td>
</tr>
<tr>
    <td>0</td><td>0</td><td>0</td><td>1</td>
</tr>
<tr>
    <td>0</td><td>0</td><td>1</td><td>1</td>
</tr>
<tr>
    <td>0</td><td>1</td><td>0</td><td>1</td>
</tr>
<tr>
    <td>0</td><td>1</td><td>1</td><td>1</td>
</tr>
<tr>
    <td>1</td><td>0</td><td>0</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>0</td><td>1</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>1</td><td>0</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>1</td><td>1</td><td>1</td>
</tr>
</table>
)SONG"
        },
        {
            "Generating_table_with_several_parameters_including_commutative_parameters"
            "a i [] b * 0xFA -$ 5 + && ! x b a i [] * c k + && && ||",
                R"SONG(
<table>
<tr>
    <td>a[i]*b</td><td>x</td><td>c+k</td><td>F</td>
</tr>
<tr>
    <td>0</td><td>0</td><td>0</td><td>1</td>
</tr>
<tr>
    <td>0</td><td>0</td><td>1</td><td>1</td>
</tr>
<tr>
    <td>0</td><td>1</td><td>0</td><td>1</td>
</tr>
<tr>
    <td>0</td><td>1</td><td>1</td><td>1</td>
</tr>
<tr>
    <td>1</td><td>0</td><td>0</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>0</td><td>1</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>1</td><td>0</td><td>0</td>
</tr>
<tr>
    <td>1</td><td>1</td><td>1</td><td>1</td>
</tr>
</table>
)SONG"
        }
};

INSTANTIATE_TEST_SUITE_P(
        GenerateTableTest,
        GenerateTableTestDDT,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<GenerateTableTestParams> &info) {
            return info.param.testName;
        }
);