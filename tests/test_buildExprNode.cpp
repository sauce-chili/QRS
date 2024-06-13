//
// Created by sc on 04.06.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "entities/Logical/LogicalNode.h"
#include "entities/Constant/ConstantExprNode.h"
#include "entities/Arithmetic/ArithmeticNode.h"
#include "utils/BuilderUtils.h"
#include "builders/ExprNodeBuilder.h"
#include "exception/BuildExceptions.h"
#include "TestUtils.h"
#include <memory>

using namespace std;

unique_ptr<ExceptionList> createEmptyExceptionList() {
    return make_unique<ExceptionList>();
}

struct BuildExprNodeTestParams {
    string testName;
    string buildString;
    function<std::unique_ptr<ExprNode>()> expectedTree;
    function<std::unique_ptr<ExceptionList>()> expectedExps;
};

class BuildExprNodeTest
        : public ::testing::TestWithParam<BuildExprNodeTestParams> {
};

TEST_P(BuildExprNodeTest, BuildExprTreeTest) {
    auto params = GetParam();
    unique_ptr<ExprNode> expectedTree = params.expectedTree();
    unique_ptr<ExceptionList> expectedExceptions = params.expectedExps();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *actualTree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    bool result;

    if (not expectedExceptions->empty()) {
        result = std::equal(expectedExceptions->begin(), expectedExceptions->end(), actualExceptions.end());
        EXPECT_TRUE(result);
    } else {
        string actualDiff = "";
        string expectedDiff = "";
        string buffer = "";
        result = expectedTree->compareExprTree(actualTree, actualDiff, buffer);
        EXPECT_TRUE(result);

        removeWhiteSeparators(actualDiff);
        removeWhiteSeparators(expectedDiff);

        EXPECT_EQ(actualDiff, expectedDiff);
    }
}

// TEST 1
vector<BuildExprNodeTestParams> provideBuildSimpleArithmeticalTreeTestCases() {
    const vector<pair<
            EXPR_NODE_TYPE, string
    >
    > binaryOperators = {
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
    vector<BuildExprNodeTestParams> testCases;
    // [TEST 1]
    // создаем простые деревья бинарных арифметических операции
    for (const auto &op: binaryOperators) {
        testCases.push_back({
                                    "Build_simple_arithmetic_tree_with_root_" + op.second,
                                    "a b " + BuilderUtil::getStrRepresentationNodeType(op.first),
                                    [op]() -> std::unique_ptr<ExprNode> {
                                        return std::make_unique<BinaryArithmeticNode>(
                                                op.first,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        );
                                    },
                                    {}
                            });
    }
    return testCases;
}

vector<BuildExprNodeTestParams> provideCommonTestCases() {
    return {
            // TEST 2
            {
                    "Build_simple_arithmetic_tree_with_root_unary_minus",
                    "a b * -$",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<CommutativeArithmeticNode>(
                                        MUL,
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 3
            {
                    "Building_AND_node",
                    "a b &&",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 4
            {
                    "Building_OR_node",
                    "a b ||",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 5
            {
                    "Building_NOT_node",
                    "a b * !",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<CommutativeArithmeticNode>(
                                        MUL,
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 6
            {
                    "Building_a_tree_with_a_numeric_constant",
                    "a 8.2 *",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 7
            {
                    "Building_a_tree_with_logical_constant",
                    "a true &&",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 8
            // !(a[i] * b && -0xFA) || (x && b * a[i])
            {
                    "Building_a_complex_tree",
                    "a i [] b * 0xFA -$ && ! x b a i [] * && ||",
                    []() -> unique_ptr<ExprNode> {
                        return make_unique<LogicalNodeOR>(
                                make_unique<LogicalNodeNOT>(
                                        make_unique<LogicalNodeAND>(
                                                make_unique<CommutativeArithmeticNode>(
                                                        MUL,
                                                        make_unique<ArrayArithmeticNode>(
                                                                make_unique<Operand>("a").release(),
                                                                make_unique<Operand>("i").release()
                                                        ).release(),
                                                        make_unique<Operand>("b").release()
                                                ).release(),
                                                make_unique<UnaryArithmeticNode>(
                                                        UNARY_MINUS,
                                                        std::make_unique<ConstantExprNode>("0xFA").release()
                                                ).release()
                                        ).release()
                                ).release(),
                                make_unique<LogicalNodeAND>(
                                        make_unique<Operand>("x").release(),
                                        make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                make_unique<Operand>("b").release(),
                                                make_unique<ArrayArithmeticNode>(
                                                        make_unique<Operand>("a").release(),
                                                        make_unique<Operand>("b").release()
                                                ).release()
                                        ).release()

                                ).release()
                        );
                    },
                    createEmptyExceptionList
            },
            // TEST 10
            {
                    "Missing_operand",
                    "a b + +",
                    []() -> unique_ptr<ExprNode> {
                        return nullptr;
                    },
                    []() -> unique_ptr<ExceptionList> {
                        auto exceptions = make_unique<list<Exception>>();
                        exceptions->emplace_back(MissingOperand("+", 4));
                        return exceptions;
                    }
            },
            // TEST 11
            {
                    "Unknown_sequence",
                    "a b ++",
                    []() -> unique_ptr<ExprNode> {
                        return nullptr;
                    },
                    []() -> unique_ptr<ExceptionList> {
                        auto exceptions = make_unique<list<Exception>>();
                        exceptions->emplace_back(UnexpectedElementException("++", 3));
                        return exceptions;
                    }
            },
            // TEST 12
            {
                    "Extra_operand",
                    "a b c ||",
                    []() -> unique_ptr<ExprNode> {
                        return nullptr;
                    },
                    []() -> unique_ptr<ExceptionList> {
                        auto exceptions = make_unique<list<Exception>>();
                        exceptions->emplace_back(ExtraOperandException("a", 1));
                        return exceptions;
                    }
            }
    };
};

static vector<BuildExprNodeTestParams> provideTestCases() {

    auto tests = {
            provideBuildSimpleArithmeticalTreeTestCases(),
            provideCommonTestCases(),
    };

    vector<BuildExprNodeTestParams> testCases;
    for (auto tc: tests) {
        testCases.insert(testCases.end(), tc.begin(), tc.end());
    }

    return testCases;
}

INSTANTIATE_TEST_SUITE_P(
        BuildExprTreeTest,
        BuildExprNodeTest,
        ::testing::ValuesIn(provideTestCases()),
        [](const testing::TestParamInfo<BuildExprNodeTestParams> &info) {
            return info.param.testName;
        }
);

