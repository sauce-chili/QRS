cmake_minimum_required(VERSION 3.27)
project(ModuleWork_Q_RS)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

add_subdirectory(lib/googletest)
add_subdirectory(src)
add_subdirectory(tests)
