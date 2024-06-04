set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES}
        test_buildExprNode.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})
include_directories(../lib/googletest/googletest/include)
include_directories(../lib/googletest/googlemock/include)

target_link_directories(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
target_link_libraries(${CMAKE_PROJECT_NAME}_test PRIVATE gtest)
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)