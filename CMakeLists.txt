cmake_minimum_required(VERSION 3.27)
project(ModulWord_Q_RS)

set(CMAKE_CXX_STANDARD 20)



#add_executable(ModulWord_Q_RS src/main.cpp
#        src/entities/ExprNode.h
#        src/entities/Logical/LogicalNode.h
#        src/builders/ExprNodeBuilder.h
#        src/exception/BuildExceptions.cpp
#        src/exception/BuildExceptions.h
#        src/entities/Logical/LogicalNode.cpp
#        src/entities/Arithmetic/ArithmeticNode.cpp
#        src/entities/Arithmetic/ArithmeticNode.h
#        src/entities/ExprNode.cpp
#        src/entities/Constant/ConstantExprNode.cpp
#        src/entities/Constant/ConstantExprNode.h
#        src/builders/ExprNodeBuilder.cpp
#        src/entities/Operation.cpp
#        src/entities/Operation.h
#        src/entities/Operand.cpp
#        src/entities/Operand.h
#        src/utils/BuilderUtils.cpp
#        src/utils/BuilderUtils.h
#        src/truthtablegererator/Generator.cpp
#        src/truthtablegererator/Generator.h
#        tests/Test_lower.cpp
#        tests/Test_lower.h
#        tests/AllTests.cpp
#        tests/AllTests.h
#        tests/test_main.cpp
#        tests/test_compareExprTree/Test_compareExprTree.cpp
#        tests/test_compareExprTree/Test_compareExprTree.h
#)


include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib/googletest)