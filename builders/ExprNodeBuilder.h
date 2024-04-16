//
// Created by sc on 08.04.24.
//

#include "../entities/ExprNode.h"
#include "../utils/BuilderUtils.h"

class ExprNodeBuilder {
       BuilderUtil buildUtil;
public:
    ExprNodeBuilder();
    ExprNode *buildExprTree(std::string postfixExpr);
};