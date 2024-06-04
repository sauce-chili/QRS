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


using namespace std;
using ExceptionList = std::list<Exception>;

struct GetParametersTestsData {
    string testName;
    string buildString;
    vector<string> strParams;
};

class GetParametersTestDDT
        : public ::testing::TestWithParam<GetParametersTestsData> {
};

TEST_P(GetParametersTestDDT, ParseExprNodeTreeToStringTest) {
    auto params = GetParam();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    vector<ExprNode *> parameters;
    tree->getParameters(parameters);

    vector<string> &expected = params.strParams;

    bool result;

    if (expected.size() == parameters.size()) {
        for (int i = 0; i < expected.size(); i++) {
            string actStrParam = parameters[i]->toString();
            string expStrParam = expected[i];

            if (not(actStrParam == expStrParam)) {
                result = false;
                break;
            }
        }

        result = true;
    }

    EXPECT_TRUE(result);
}

vector<GetParametersTestsData> testCases = {
        {
                "Tree_without_parameters_only_const",
                "false 0xFA -$ 5 + &&",
                vector<string>()
        },
        {
                "Tree_contains_one_parameter_and_one_const",
                "false 0xFA -$ a + &&",
                vector<string>{"(-0xFA)+a"}
        },
        {
                "Tree_with_commutative_parameter",
                "a i [] b * 0xFA -$ 5 + && ! x b a i [] * && ||",
                vector<string>{"a[i]*b", "x"} // a[i]*b == b*a[i]
        },
        {
                "Tree_with_parameters_similar_to_commutative",
                "a i [] b * 0xFA -$ 5 + && ! x b i a [] * && ||",
                vector<string>{"a[i]*b", "x", "b*i[a]"} // a[i]*b != b*i[a]
        },
        {
            // !((a[i]*b)&&((-0xFA) + 5)) || (x && ((b || a[i]) ^ (c+k)))
            "Complex_test",
            "a i [] b * 0xFA -$ 5 + && ! b a i [] || c k + ^ ||",
            vector<string>{"a[i]*b", "x", "(b||a[i])^c+k"}
        }
};

INSTANTIATE_TEST_SUITE_P(
        ParseExprNodeTreeToStringTest,
        GetParametersTestDDT,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<GetParametersTestsData> &info) {
            return info.param.testName;
        }
);