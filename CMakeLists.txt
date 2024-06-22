cmake_minimum_required(VERSION 3.27)
project(ModuleWork_Q_RS)

set(CMAKE_CXX_STANDARD 20)

# Установка флагов для статической компоновки
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

include_directories(src)

add_subdirectory(lib/googletest)
add_subdirectory(src)

add_executable(${CMAKE_PROJECT_NAME}_main main.cpp)

# Связывание main с библиотекой
target_link_libraries(${CMAKE_PROJECT_NAME}_main ${CMAKE_PROJECT_NAME}_lib)

# Включение подкаталог tests после определения цели main
add_subdirectory(tests)

# Связывание main с gtest и gtest_main после добавления тестов
target_link_libraries(${CMAKE_PROJECT_NAME}_main gtest gtest_main)