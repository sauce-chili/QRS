//
// Created by sc on 14.04.24.
//
#include <regex>
#include "ExprNodeBuilder.h"
#include "utils/BuilderUtils.h"
#include "entities/Logical/LogicalNode.h"
#include "entities/Arithmetic/ArithmeticNode.h"
#include "entities/Constant/ConstantExprNode.h"

using namespace std;

ExprNode *ExprNodeBuilder::buildExprTree(string postfixExpr, list<Exception> &exps) {

    if (postfixExpr.empty()) {
        exps.push_back(EmptyTreeException());
        return nullptr;
    }

    // splitting str by spaces
    regex sepReg("\\s+"); // once or more spaces
    vector<string> splitted(
            sregex_token_iterator(postfixExpr.begin(), postfixExpr.end(), sepReg, -1),
            sregex_token_iterator()
    );

    stack<pair<int, ExprNode *>> stack;

    for (int idx = 0; idx < splitted.size(); idx++) {
        string s = splitted[idx];
        try {
            buildNode(s, idx, stack);
        } catch (Exception &e) {
            exps.push_back(e);
        }
    }

    pair<int, ExprNode *> topElem = stack.top();
    stack.pop();

    if (stack.empty()) {
        return topElem.second;
    }

    // if stack isn't empty, when add in exceptions all extra elems

    bool topElemIsNotOperation = topElem.second->getNodeType() == EXPR_NODE_TYPE::VAR
                                 || topElem.second->getNodeType() == EXPR_NODE_TYPE::CONST;

    if (topElemIsNotOperation){
        exps.push_back(ExtraOperandException(topElem.second->toString(), topElem.first));
    }
    while (not stack.empty()) {
        auto extraElem = stack.top();
        stack.pop();
        int idxExtraElem = extraElem.first;
        string elemRepresentation = splitted.at(idxExtraElem);
        exps.push_back(ExtraOperandException(elemRepresentation, idxExtraElem + 1));
    }

    return nullptr;
}

void ExprNodeBuilder::buildNode(const std::string &elem, int idxElem, stack<std::pair<int, ExprNode *>> &stack) {
    EXPR_NODE_TYPE type = BuilderUtil::getNodeType(elem);

    if (type == UNDEFINED) {
        throw UnexpectedElementException(elem, idxElem + 1);
    }

    if (type == CONST) {
        stack.push({idxElem, new ConstantExprNode(elem)});
    } else if (type == VAR) {
        stack.push({idxElem, new Operand(elem)});
    } else {
        buildOperationNode(type, idxElem, stack);
    }
}

void ExprNodeBuilder::buildOperationNode(EXPR_NODE_TYPE type, int idxOperation, stack<pair<int, ExprNode *>> &stack) {

    bool isBinaryOperation = BuilderUtil::isBinaryOperation(type);
    bool enoughOperandForBinOperation = isBinaryOperation && stack.size() >= 2;
    bool enoughOperandForUnaryOperation = not isBinaryOperation && not stack.empty();

    if (not enoughOperandForBinOperation && not enoughOperandForUnaryOperation) {
        throw MissingOperand(BuilderUtil::getStrRepresentationNodeType(type), idxOperation + 1);
    }

    if (BuilderUtil::isLogicalOperation(type)) {
        buildLogicalNode(type, idxOperation, stack);
    } else {
        buildArithmeticalNode(type, idxOperation, stack);
    }
}

void ExprNodeBuilder::buildLogicalNode(EXPR_NODE_TYPE type, int idxOperation, stack<pair<int, ExprNode *>> &stack) {
    auto right = stack.top().second;
    stack.pop();

    if (type == EXPR_NODE_TYPE::NOT) {
        stack.push({
                           idxOperation,
                           new LogicalNodeNOT(right)
                   });
        return;
    }

    auto left = stack.top().second;
    stack.pop();

    if (type == EXPR_NODE_TYPE::OR) {
        stack.push({
                           idxOperation,
                           new LogicalNodeOR(left, right)
                   });
    } else if (type == EXPR_NODE_TYPE::AND) {
        stack.push({
                           idxOperation,
                           new LogicalNodeAND(left, right)
                   });
    }
}

void
ExprNodeBuilder::buildArithmeticalNode(EXPR_NODE_TYPE type, int idxOperation, stack<pair<int, ExprNode *>> &stack) {
    auto right = stack.top().second;
    stack.pop();

    if (type == EXPR_NODE_TYPE::UNARY_MINUS) {
        stack.push({
                           idxOperation,
                           new UnaryArithmeticNode(type, right)
                   });
        return;
    }

    auto left = stack.top().second;
    stack.pop();

    if (type == EXPR_NODE_TYPE::ARR) {
        stack.push({
                           idxOperation,
                           new ArrayArithmeticNode(left, right)
                   });
    } else if (BuilderUtil::isCommutativeOperation(type)) {
        stack.push({
                           idxOperation,
                           new CommutativeArithmeticNode(type, left, right)
                   });
    } else {
        stack.push({
                           idxOperation,
                           new BinaryArithmeticNode(type, left, right)
                   });
    }
}


