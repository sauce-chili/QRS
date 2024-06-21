cmake_minimum_required(VERSION 3.27)
project(ModulWord_Q_RS)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
# Добавление опции для выбора типа сборки
option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(lib/googletest)
    add_subdirectory(tests)
endif()
