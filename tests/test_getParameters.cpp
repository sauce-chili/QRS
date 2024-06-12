//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/BuildExceptions.h"
#include "TestUtils.h"

using namespace std;

struct GetParametersTestsParam {
    string testName;
    string buildString;
    // str representation of parameter and ID
    vector<pair<string, int>> params;
};

class GetParametersTestDDT
        : public ::testing::TestWithParam<GetParametersTestsParam> {
};

TEST_P(GetParametersTestDDT, GetParametersTest) {
    auto params = GetParam();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    vector<ExprNode *> parameters;
    tree->getParameters(parameters);

    vector<pair<string, int>> &expected = params.params;

    if (expected.size() == parameters.size()) {

        std::sort(parameters.begin(), parameters.end(),
                  [](const ExprNode *a, const ExprNode *b) {
                      return a->getParamID() < b->getParamID();
                  });

        std::sort(expected.begin(), expected.end(),
                  [](const std::pair<std::string, int> &a,
                     const std::pair<std::string, int> &b) {
                      return a.second < b.second;
                  });

        for (int i = 0; i < expected.size(); i++) {

            string actStrParam = parameters[i]->toString();
            int actualId = parameters[i]->getParamID();

            string expStrParam = expected[i].first;
            int expId = expected[i].second;

            removeWhiteSeparators(actStrParam);
            removeWhiteSeparators(expStrParam);

            EXPECT_EQ(actStrParam, expStrParam);
            EXPECT_EQ(actualId, expId);
        }
    } else {
        EXPECT_EQ(expected.size(), parameters.size());
    }
}

const vector<GetParametersTestsParam> commonTestCases = {
        {
                // false && -0xFA+5
                "Tree_without_parameters_only_const",
                "false 0xFA -$ 5 + &&",
                vector<pair<string, int>>()
        },
        {
                //  false && -0xFA+a
                "Tree_contains_one_parameter_and_one_const",
                "false 0xFA -$ a + &&",
                vector<pair<string, int>>{{"(-0xFA)+a", 1}}
        },
        {
                // !((a[i] * b) && ((-0xFA) + 5)) || (x && b*a[i])
                "Tree_with_commutative_parameter",
                "a i [] b * 0xFA -$ 5 + && ! x b a i [] * && ||",
                vector<pair<string, int>>{
                        {"a[i]*b", 1}, // a[i]*b == b*a[i]
                        {"x",      2}
                }
        },
        {
                // !((a[i] * b) && ((-0xFA) + 5)) || (x && b*i[a])
                "Tree_with_parameters_similar_to_commutative",
                "a i [] b * 0xFA -$ 5 + && ! x b i a [] * && ||",
                vector<pair<string, int>>{
                        {"a[i]*b", 1}, // a[i]*b != b*i[a]
                        {"x",      2},
                        {"b*i[a]", 3}
                }
        },
        {
                // !((a[i]*b)&&((-0xFA) + 5)) || (x && ((b || a[i]) ^ (c+k)))
                "Complex_test",
                "a i [] b * 0xFA -$ 5 + && ! b a i [] || c k + ^ ||",
                vector<pair<string, int>>{
                        {"a[i]*b",        1},
                        {"x",             2},
                        {"(b||a[i])^c+k", 3}
                }
        }
};

INSTANTIATE_TEST_SUITE_P(
        GetParametersTest,
        GetParametersTestDDT,
        ::testing::ValuesIn(commonTestCases),
        [](const testing::TestParamInfo<GetParametersTestsParam> &info) {
            return info.param.testName;
        }
);