#set(BINARY ${CMAKE_PROJECT_NAME})
#
##set(CMAKE_AUTOMOC ON)
##set(CMAKE_AUTORCC ON)
##set(CMAKE_AUTOUIC ON)
#
##find_package(Qt5 COMPONENTS
##        Core
##        REQUIRED)
#
#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
#
#set(SOURCES ${SOURCES})
#
#add_executable(${BINARY}_run ${SOURCES})
#
##target_link_libraries(${CMAKE_CURRENT_SOURCE_DIR}
##        Qt5::Core
##)
#
#add_library(${BINARY}_lib STATIC ${SOURCES})

set(BINARY ${CMAKE_PROJECT_NAME})

# Поиск и загрузка пакета Qt с компонентом Core
find_package(Qt5 COMPONENTS Core REQUIRED)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Включение всех файлов .h и .cpp в проект
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

# Добавление директивы include_directories для указания компилятору, где искать заголовочные файлы Qt
include_directories(${Qt5Core_INCLUDE_DIRS})
# Создание исполняемого файла с именем ${BINARY}_run из исходных файлов
add_executable(${BINARY}_run ${SOURCES})

# Добавление Qt компонента Core в цель ${BINARY}_run
target_link_libraries(${BINARY}_run PRIVATE Qt5::Core)

# Создание статической библиотеки
add_library(${BINARY}_lib STATIC ${SOURCES})

