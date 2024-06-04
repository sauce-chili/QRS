//
// Created by sc on 07.05.24.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "entities/ExprNode.h"
#include "entities/Logical/LogicalNode.h"
#include "entities/Constant/ConstantExprNode.h"
#include "entities/Arithmetic/ArithmeticNode.h"
#include <memory>

using namespace std;

TEST(BinaryOperationComparisonTest, ComplexArithmeticOperationsTrees) {
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

        std::unique_ptr<ExprNode> tree2 = std::make_unique<BinaryArithmeticNode>(
                op,
                std::make_unique<Operand>("a").release(),
                std::make_unique<Operand>("b").release()
        );

        if (not tree1->compareExprTree(tree2.get())) {
            expected = false;
            break;
        }
    }

    EXPECT_TRUE(expected);
}

TEST(BinaryOperationComparisonTest, ComplexBinaryOperationsTrees) {
    // Создаем простые бинарные арифметические деревья для каждого бинарного оператора

    std::unique_ptr<ExprNode> tree1 = std::make_unique<LogicalNodeAND>(
            std::make_unique<Operand>("a").release(),
            std::make_unique<Operand>("b").release()
    );

    std::unique_ptr<ExprNode> tree2 = std::make_unique<LogicalNodeAND>(
            std::make_unique<Operand>("a").release(),
            std::make_unique<Operand>("b").release()
    );

    if (not tree1->compareExprTree(tree2.get())) {
        EXPECT_TRUE(false);
    }

    std::unique_ptr<ExprNode> tree3 = std::make_unique<LogicalNodeOR>(
            std::make_unique<Operand>("a").release(),
            std::make_unique<Operand>("b").release()
    );

    std::unique_ptr<ExprNode> tree4 = std::make_unique<LogicalNodeOR>(
            std::make_unique<Operand>("a").release(),
            std::make_unique<Operand>("b").release()
    );

    if (not tree3->compareExprTree(tree4.get())) {
        EXPECT_TRUE(false);
    }

    EXPECT_TRUE(true);
}

struct TestParams {
    std::string testName;
    std::function<std::unique_ptr<ExprNode>()> createExpr1;
    std::function<std::unique_ptr<ExprNode>()> createExpr2;
    bool expectedResult;
};

class CompareExprNodeTest
        : public ::testing::TestWithParam<TestParams> {
};

TEST_P(CompareExprNodeTest, CompareExprTreeTest) {
    auto params = GetParam();
    unique_ptr<ExprNode> expr1 = params.createExpr1();
    unique_ptr<ExprNode> expr2 = params.createExpr2();
    bool expected = params.expectedResult;
    bool actual = expr1->compareExprTree(expr2.get());

    EXPECT_EQ(actual, expected);
}

const vector<TestParams> testCases = {
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
                true
        },
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
                true
        },
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
                true
        },
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
                false
        },
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
                true
        },
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
                true
        },
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
                false
        },
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
                true
        },
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
                false
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                true
        },
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
                false
        },
        // Logical Expression (a && true) vs Logical Expression (a && true)
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
                true
        },
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
                false // Ожидаемое значение: false, так как левая и правая части не эквивалентны
        },
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
                true
        },
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
                false // Ожидаемое значение: false, так как операнды не эквивалентны
        },
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
                true // Ожидаемое значение: true, так как оба выражения эквивалентны
        },
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
                true // Ожидаемое значение: true, так как оба выражения эквивалентны
        },
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
                false // Ожидаемое значение: true, так как оба выражения эквивалентны
        }
};

INSTANTIATE_TEST_SUITE_P(
        CompareExprTreeTests,
        CompareExprNodeTest,
        ::testing::ValuesIn(testCases),
        [](const testing::TestParamInfo<TestParams> &info) {
            return info.param.testName;
        }
);
