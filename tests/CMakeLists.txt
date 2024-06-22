set(BINARY ${CMAKE_PROJECT_NAME}_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

# Вместо создания отдельного исполняемого файла для тестов,
# мы добавляем исходные файлы тестов в основной исполняемый файл
target_sources(${CMAKE_PROJECT_NAME}_main PRIVATE ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${CMAKE_PROJECT_NAME}_main --test)

include_directories(../lib/googletest/googletest/include)
include_directories(../lib/googletest/googlemock/include)
include_directories(../src)