cmake_minimum_required(VERSION 3.27)
project(ModulWord_Q_RS)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        REQUIRED)

add_executable(ModulWord_Q_RS main.cpp
        entities/ExprNode.h
        entities/ExprNodeImpl/LogicalNode.h
        builders/ExprNodeBuilder.h
        utils/BuilderUtils.h
        entities/Exceptions.cpp
        entities/Exceptions.h
        entities/ExprNodeImpl/LogicalNode.cpp
        entities/ExprNodeImpl/ArithmeticNode.cpp
        entities/ExprNodeImpl/ArithmeticNode.h
        entities/ExprNode.cpp
        utils/BuilderUtils.cpp
        entities/ExprNodeImpl/VarExprNode.h
        entities/ExprNodeImpl/VarExprNode.cpp
        entities/ExprNodeImpl/ConstantExprNode.cpp
        entities/ExprNodeImpl/ConstantExprNode.h
        builders/ExprNodeBuilder.cpp
)
target_link_libraries(ModulWord_Q_RS
        Qt5::Core
)

