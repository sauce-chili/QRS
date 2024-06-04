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
#include <memory>

using namespace std;

TEST(BinaryOperationComparisonTest, BuildingTreeFromBinaryArithmeticOperations) {
    // Создаем простые бинарные арифметические деревья для каждого бинарного оператора
    std::vector<EXPR_NODE_TYPE> binaryOperators = {
            PLUS, MINUS, MUL, DIV, MOD, XOR, SHLA, SHRA, EQ, NEQ, GREAT, LESS, GREAT_OR_EQ, LESS_OR_EQ
    };

    bool expected = true;

    for (EXPR_NODE_TYPE op: binaryOperators) {
        std::unique_ptr<ExprNode> tree1 = std::make_unique<BinaryArithmeticNode>(
                op,
                std::make_unique<Operand>("a").release(),
                std::make_unique<Operand>("b").release()
        );

        string buildStr = "a b " + BuilderUtil::getStrNodeType(op);
        std::list<Exception> exps;
        ExprNode *tree2 = ExprNodeBuilder::buildExprTree(buildStr, exps);

        bool cmpResult = tree1->compareExprTree(tree2);
        if (not exps.empty() || not cmpResult) {
            expected = false;
            delete tree2;
            break;
        }
        delete tree2;
    }

    EXPECT_TRUE(expected);
}

// Псевдоним для удобства использования типа списка исключений
using ExceptionList = std::list<Exception>;

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

TEST_P(BuildExprNodeTest, CompareExprTreeTest) {
    auto params = GetParam();
    unique_ptr<ExprNode> expectedTree = params.expectedTree();
    unique_ptr<ExceptionList> expectedExceptions = params.expectedExps();

    ExceptionList actualExceptions;
    string inStr = params.buildString;
    ExprNode *actualTree = ExprNodeBuilder::buildExprTree(inStr, actualExceptions);

    bool result = false;

    if (not expectedExceptions->empty()) {
        result = std::equal(expectedExceptions->begin(), expectedExceptions->end(), actualExceptions.end());
    } else {
        result = expectedTree->compareExprTree(actualTree);
    }
    EXPECT_TRUE(result);
}

const vector<BuildExprNodeTestParams> testCases = {
        {
                "building_a_tree_from_a_unary_node",
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

INSTANTIATE_TEST_SUITE_P(
        BuildExprTreeTest,
        BuildExprNodeTest,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<BuildExprNodeTestParams> &info) {
            return info.param.testName;
        }
);

