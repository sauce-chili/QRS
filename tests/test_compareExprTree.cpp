//
// Created by sc on 07.05.24.
//
#include <gtest/gtest.h>
#include "entities/ExprNode.h"
#include "utils/Utils.h"
#include "entities/Logical/LogicalNode.h"
#include "entities/Constant/ConstantExprNode.h"
#include "entities/Arithmetic/ArithmeticNode.h"
#include <memory>

using namespace std;

struct CompareExprNodeTestParams {
    std::string testName;
    std::function<std::unique_ptr<ExprNode>()> createExpr1;
    std::function<std::unique_ptr<ExprNode>()> createExpr2;
    std::string pathToDiff;
    bool expectedResult;
};

class CompareExprNodeTestDDT
        : public ::testing::TestWithParam<CompareExprNodeTestParams> {
};

TEST_P(CompareExprNodeTestDDT, CompareExprTreeTest) {
    auto params = GetParam();

    unique_ptr<ExprNode> expr1 = params.createExpr1();
    unique_ptr<ExprNode> expr2 = params.createExpr2();


    bool expected = params.expectedResult;
    string expectedDiff = params.pathToDiff;
    string actualDiff;
    string buffer;
    bool actual = expr1->compareExprTree(expr2.get(), actualDiff, buffer);

    removeWhiteSeparators(actualDiff);
    removeWhiteSeparators(expectedDiff);

    EXPECT_EQ(actual, expected);
    EXPECT_EQ(actualDiff, expectedDiff);
}

// TEST 7
static vector<CompareExprNodeTestParams> provideCompareSimpleBinaryArithmeticTreeTestCases() {
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
    vector<CompareExprNodeTestParams> testCases;
    // создаем простые деревья бинарных арифметических операции
    for (const auto &op: binaryOperators) {
        testCases.push_back({
                                    "Compare_simple_arithmetic_tree_with_root_" + op.second,
                                    [op]() -> std::unique_ptr<ExprNode> {
                                        return std::make_unique<BinaryArithmeticNode>(
                                                op.first,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        );
                                    },
                                    [op]() -> std::unique_ptr<ExprNode> {
                                        return std::make_unique<BinaryArithmeticNode>(
                                                op.first,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        );
                                    },
                                    "",
                                    true
                            });
    }
    return testCases;
}

// TEST 1
static vector<CompareExprNodeTestParams> provideCompareSimpleBinaryLogicalTreeTestCases() {
    // Создаем простые бинарные деревья для каждого логического оператора
    return {
            {
                    "Compare_simple_logical_tree_with_root_AND",
                    []() -> unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    []() -> unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    "",
                    true
            },
            {
                    "Compare_simple_logical_tree_with_root_OR",
                    []() -> unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    []() -> unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    "",
                    true
            }
    };
}

static vector<CompareExprNodeTestParams> provideCompareExprNodeCommonTestCases() {
    return {
            // TEST 2
            // выражение a[len * (n - 1)] для обоих деревьев
            {
                    "Comparing_a_complex_arithmetic_tree_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<ArrayArithmeticNode>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<CommutativeArithmeticNode>(
                                        MUL,
                                        std::make_unique<Operand>("len").release(),
                                        std::make_unique<BinaryArithmeticNode>(
                                                MINUS,
                                                std::make_unique<Operand>("n").release(),
                                                std::make_unique<ConstantExprNode>("1").release()
                                        ).release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<ArrayArithmeticNode>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<CommutativeArithmeticNode>(
                                        MUL,
                                        std::make_unique<Operand>("len").release(),
                                        std::make_unique<BinaryArithmeticNode>(
                                                MINUS,
                                                std::make_unique<Operand>("n").release(),
                                                std::make_unique<ConstantExprNode>("1").release()
                                        ).release()
                                ).release()
                        );
                    },
                    "",
                    true
            },
            // TEST 3
            // Test: (a[i] >> n) / b[j] vs (a[j] >> n) / b[i]
            {
                    "Comparing_a_complex_arithmetic_tree_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<BinaryArithmeticNode>(
                                DIV,
                                std::make_unique<BinaryArithmeticNode>(
                                        SHRA,
                                        std::make_unique<ArrayArithmeticNode>(
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("i").release()
                                        ).release(),
                                        std::make_unique<Operand>("n").release()
                                ).release(),
                                std::make_unique<ArrayArithmeticNode>(
                                        std::make_unique<Operand>("b").release(),
                                        std::make_unique<Operand>("j").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<BinaryArithmeticNode>(
                                DIV,
                                std::make_unique<BinaryArithmeticNode>(
                                        SHRA,
                                        std::make_unique<ArrayArithmeticNode>(
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("j").release()
                                        ).release(),
                                        std::make_unique<Operand>("n").release()
                                ).release(),
                                std::make_unique<ArrayArithmeticNode>(
                                        std::make_unique<Operand>("b").release(),
                                        std::make_unique<Operand>("i").release()
                                ).release()
                        );
                    },
                    "/ -> >> -> [] -> j",
                    false
            },
            // TEST 4
            // Test: - a vs - a
            {
                    "Comparison_of_a_simple_unary_operation_tree",
                    []() -> unique_ptr<ExprNode> {
                        return make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                make_unique<Operand>("a").release()
                        );
                    },
                    []() -> unique_ptr<ExprNode> {
                        return make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                make_unique<Operand>("a").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 5
            // Test: - (b - a * arr[i]) vs - (a - b * arr[i])
            {
                    "Comparison_of_complex_unary_trees_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<BinaryArithmeticNode>(
                                        MINUS,
                                        std::make_unique<Operand>("b").release(),
                                        std::make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<ArrayArithmeticNode>(
                                                        std::make_unique<Operand>("arr").release(),
                                                        std::make_unique<Operand>("i").release()
                                                ).release()
                                        ).release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<BinaryArithmeticNode>(
                                        MINUS,
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("b").release(),
                                                std::make_unique<ArrayArithmeticNode>(
                                                        std::make_unique<Operand>("arr").release(),
                                                        std::make_unique<Operand>("i").release()
                                                ).release()
                                        ).release()
                                ).release()
                        );
                    },
                    "- -> - -> a",
                    false
            },
            // TEST 6
            // Test: - (a * b + (n >> arr[i])) vs - (a * b + (n >> arr[i]))
            {
                    "Comparison_of_complex_unary_trees_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<CommutativeArithmeticNode>(
                                        PLUS,
                                        std::make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<BinaryArithmeticNode>(
                                                SHRA,
                                                std::make_unique<Operand>("n").release(),
                                                std::make_unique<ArrayArithmeticNode>(
                                                        std::make_unique<Operand>("arr").release(),
                                                        std::make_unique<Operand>("i").release()
                                                ).release()
                                        ).release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<CommutativeArithmeticNode>(
                                        PLUS,
                                        std::make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<BinaryArithmeticNode>(
                                                SHRA,
                                                std::make_unique<Operand>("n").release(),
                                                std::make_unique<ArrayArithmeticNode>(
                                                        std::make_unique<Operand>("arr").release(),
                                                        std::make_unique<Operand>("i").release()
                                                ).release()
                                        ).release()
                                ).release()
                        );
                    },
                    "",
                    true
            },
            // TEST 8
            // Logical Expression (a && b || c && b) vs Logical Expression (a && b || c && b)
            {
                    "Comparison_of_complex_binary_logic_trees_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("c").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("c").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release()
                        );
                    },
                    "",
                    true
            },
            // TEST 9
            // Logical Expression (b && a || c && b) vs Logical Expression (a && b || c && b)
            {
                    "Comparison_of_complex_binary_logic_trees_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("b").release(),
                                        std::make_unique<Operand>("a").release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("c").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("c").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release()
                        );
                    },
                    "|| -> && -> a",
                    false
            },
            // TEST 10
            // Logical NOT (!a) vs Logical NOT (!a)
            {
                    "Comparison_of_unary_logical_operations_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<Operand>("a").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<Operand>("a").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 11
            // Logical NOT (!a) vs Logical NOT (!b)
            {
                    "Comparison_of_unary_logical_operations_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<Operand>("a").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<Operand>("b").release()
                        );
                    },
                    "! -> b",
                    false
            },
            // TEST 12
            // Logical NOT (!(a && b || c)) vs Logical NOT (!(a && b || c))
            {
                    "Comparison_of_complex_unary_logical_operators",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<LogicalNodeAND>(
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<LogicalNodeAND>(
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    "",
                    true
            },
            // TEST 13
            // Arithmetic Expression (a + 8) vs Arithmetic Expression (a + 8)
            {
                    "Comparison_of_an_arithmetic_tree_with_a_numeric_constant",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 14
            // Arithmetic Expression (a + 8.2) vs Arithmetic Expression (a + 8.2)
            {
                    "Comparison_of_arithmetic_trees_containing_fractional_numeric_constants",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 15
            // Arithmetic Expression (a + 8.0) vs Arithmetic Expression (a + 8)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_written_in_different_formats_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8.0").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 16
            // Binary Arithmetic Expression (a + 8) vs Binary Arithmetic Expression (a + 0b1000)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_written_in_different_formats_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("0b1000").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 17
            // Binary Arithmetic Expression (a ^ 8) vs Binary Arithmetic Expression (a ^ 010)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_written_in_different_formats_3",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("010").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 18
            // Binary Arithmetic Expression (a == 17) vs Binary Arithmetic Expression (a == 0x11)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_written_in_different_formats_4",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                EQ,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("17").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                EQ,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("0x11").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 19
            // Binary Arithmetic Expression (a != 8) vs Binary Arithmetic Expression (a != 0x12)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_written_in_different_formats_5",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                NEQ,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                NEQ,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("0x12").release()
                        );
                    },
                    "!= -> 0x12",
                    false
            },
            // TEST 20
            // Binary Arithmetic Expression (a + 8) vs Binary Arithmetic Expression (a + 001)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_written_in_different_formats_6",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("001").release()
                        );
                    },
                    "+ -> 001",
                    false
            },
            // TEST 21
            // Arithmetic Expression (a % true) vs Arithmetic Expression (a % true)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_logical_constants_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                MOD,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                MOD,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 22
            // Arithmetic Expression (a % true) vs Arithmetic Expression (a % false)
            {
                    "Comparison_of_binary_arithmetic_trees_containing_logical_constants_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                MOD,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                MOD,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("false").release()
                        );
                    },
                    "% -> false",
                    false
            },
            // Logical Expression (a && true) vs Logical Expression (a && true)
            // TEST 23
            {
                    "Comparison_of_binary_logic_trees_containing_logical_constants_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 24
            // Logical Expression (a || true) vs Logical Expression (a || false)
            {
                    "Comparison_of_binary_logic_trees_containing_logical_constants_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("false").release()
                        );
                    },
                    "|| -> false",
                    false // Ожидаемое значение: false, так как левая и правая части не эквивалентны
            },
            // TEST 25
            // Logical Expression (! true) vs Logical Expression (! false)
            {
                    "Comparison_of_unary_logical_operations_contains_logical_constant",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<ConstantExprNode>("false").release()
                        );
                    },
                    "! -> false",
                    false
            },
            // TEST 26
            // Logical Expression (a && 8.2) vs Logical Expression (a && 8.2)
            {
                    "Comparison_of_binary_logic_trees_containing_numeric_constants",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeAND>(
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 27
            // Unary Expression (- true) vs Unary Expression (- false)
            {
                    "Comparison_of_unary_arithmetic_trees_containing_Boolean_constants",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<ConstantExprNode>("true").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<ConstantExprNode>("false").release()
                        );
                    },
                    "- -> false",
                    false // Ожидаемое значение: false, так как операнды не эквивалентны
            },
            // TEST 28
            // Unary Expression (- 8.2) vs Unary Expression (- 8.2)
            {
                    "Comparison_of_unary_arithmetic_trees_containing_numeric_constants",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<ConstantExprNode>("8.2").release()
                        );
                    },
                    "",
                    true // Ожидаемое значение: true, так как оба выражения эквивалентны
            },
            // TEST 29
            // (a && b) || !(d + arr[i]) && 0b10 vs (a && b) || !(d + arr[i]) && 0b10
            {
                    "Comparison_of_complex_combination_trees_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<LogicalNodeNOT>(
                                                std::make_unique<CommutativeArithmeticNode>(
                                                        PLUS,
                                                        std::make_unique<Operand>("d").release(),
                                                        std::make_unique<ArrayArithmeticNode>(
                                                                std::make_unique<Operand>("arr").release(),
                                                                std::make_unique<Operand>("i").release()
                                                        ).release()
                                                ).release()
                                        ).release(),
                                        std::make_unique<ConstantExprNode>("0b10").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeOR>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("a").release(),
                                        std::make_unique<Operand>("b").release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<LogicalNodeNOT>(
                                                std::make_unique<CommutativeArithmeticNode>(
                                                        PLUS,
                                                        std::make_unique<Operand>("d").release(),
                                                        std::make_unique<ArrayArithmeticNode>(
                                                                std::make_unique<Operand>("arr").release(),
                                                                std::make_unique<Operand>("i").release()
                                                        ).release()
                                                ).release()
                                        ).release(),
                                        std::make_unique<ConstantExprNode>("0b10").release()
                                ).release()
                        );
                    },
                    "",
                    true // Ожидаемое значение: true, так как оба выражения эквивалентны
            },
            // TEST 30
            // (-8.2 || b[i]) != (x && ! a[i]) vs (-8.2 || a[i]) != (x && ! b[i])
            {
                    "Comparison_of_complex_combination_trees_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                NEQ,
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<ConstantExprNode>("-8.2").release(),
                                        std::make_unique<ArrayArithmeticNode>(
                                                std::make_unique<Operand>("b").release(),
                                                std::make_unique<Operand>("i").release()
                                        ).release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("x").release(),
                                        std::make_unique<LogicalNodeNOT>(
                                                std::make_unique<ArrayArithmeticNode>(
                                                        std::make_unique<Operand>("a").release(),
                                                        std::make_unique<Operand>("i").release()
                                                ).release()
                                        ).release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                NEQ,
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<ConstantExprNode>("-8.2").release(),
                                        std::make_unique<ArrayArithmeticNode>(
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("i").release()
                                        ).release()
                                ).release(),
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<Operand>("x").release(),
                                        std::make_unique<LogicalNodeNOT>(
                                                std::make_unique<ArrayArithmeticNode>(
                                                        std::make_unique<Operand>("b").release(),
                                                        std::make_unique<Operand>("i").release()
                                                ).release()
                                        ).release()
                                ).release()
                        );
                    },
                    "!= -> || -> [] -> a",
                    false
            },
            // TEST 31
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_with_a_type_modifier_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("17LL").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("17l").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 32
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_with_a_type_modifier_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                MUL,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("23.3f").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                MUL,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("23.3").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 33
            {
                    "Comparison_of_binary_arithmetic_trees_containing_numeric_constants_with_a_type_modifier_3",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("0.2ll").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("0.2FF").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 34
            {
                    "Comparison_of_binary_arithmetic_trees_containing_number_with_mantissa_1",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("1.04E+3").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                XOR,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("1040").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 35
            {
                    "Comparison_of_binary_arithmetic_trees_containing_number_with_mantissa_2",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("0.0033f").release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<CommutativeArithmeticNode>(
                                PLUS,
                                std::make_unique<Operand>("a").release(),
                                std::make_unique<ConstantExprNode>("3.3E-3").release()
                        );
                    },
                    "",
                    true
            },
            // TEST 36
            // Logical NOT (!(a * b || c)) vs Logical NOT (!(a + b || c))
            {
                    "The_tree_is_distinguished_by_the_arithmetic_binary_operation",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<BinaryArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<BinaryArithmeticNode>(
                                                PLUS,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    "! -> || -> +",
                    false
            },
            // TEST 37
            // Logical !(a * b && c) vs !(a + b || c)
            {
                    "The_tree_is_distinguished_by_the_logical_binary_operation",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<BinaryArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<BinaryArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    "! -> ||",
                    false
            },
            // TEST 38
            // Logical !(a * b && c) vs -(a * b && c)
            {
                    "The_tree_is_distinguished_by_the_unary_arithmetic_operation",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<BinaryArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<UnaryArithmeticNode>(
                                UNARY_MINUS,
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<BinaryArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    "-",
                    false
            },
            // TEST 39
            {
                    "The_trees_differ_in_several_nodes_but_only_the_first_distinct_one_is_displayed",
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeOR>(
                                        std::make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("b").release()
                                        ).release(),
                                        std::make_unique<Operand>("c").release()
                                ).release()
                        );
                    },
                    []() -> std::unique_ptr<ExprNode> {
                        return std::make_unique<LogicalNodeNOT>(
                                std::make_unique<LogicalNodeAND>(
                                        std::make_unique<CommutativeArithmeticNode>(
                                                MUL,
                                                std::make_unique<Operand>("a").release(),
                                                std::make_unique<Operand>("c").release()
                                        ).release(),
                                        std::make_unique<Operand>("d").release()
                                ).release()
                        );
                    },
                    "! -> &&",
                    false
            }
    };
}


static vector<CompareExprNodeTestParams> provideTestCases() {

    auto tests = {
            provideCompareSimpleBinaryLogicalTreeTestCases(),
            provideCompareSimpleBinaryArithmeticTreeTestCases(),
            provideCompareExprNodeCommonTestCases()
    };

    vector<CompareExprNodeTestParams> testCases;
    for (auto tc: tests) {
        testCases.insert(testCases.end(), tc.begin(), tc.end());
    }

    return testCases;
}

INSTANTIATE_TEST_SUITE_P(
        CompareExprTreeTests,
        CompareExprNodeTestDDT,
        ::testing::ValuesIn(provideTestCases()),
        [](const testing::TestParamInfo<CompareExprNodeTestParams> &info) {
            return info.param.testName;
        }
);
