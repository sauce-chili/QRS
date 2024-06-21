set(BINARY ${CMAKE_PROJECT_NAME}_lib)

# Включение всех файлов .h и .cpp в проект
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

# Создание статической библиотеки
add_library(${BINARY} STATIC ${SOURCES})

# Добавление исполняемого файла для основной программы
add_executable(${CMAKE_PROJECT_NAME}_main main.cpp)

# Связывание основной программы с библиотекой
target_link_libraries(${CMAKE_PROJECT_NAME}_main ${BINARY})

