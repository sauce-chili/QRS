set(BINARY ${CMAKE_PROJECT_NAME}_lib)

# Включение всех файлов .h и .cpp в проект
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

# Создание статической библиотеки
add_library(${BINARY} STATIC ${SOURCES})

# Указание, что библиотека использует компоненты Qt
find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(${BINARY} PRIVATE Qt5::Core)

# Указание компилятору, где искать заголовочные файлы Qt
include_directories(${Qt5Core_INCLUDE_DIRS})

