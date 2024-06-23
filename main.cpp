#include <iostream>
#include <fstream>
#include <string>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "truthtablegererator/Generator.h"
#include <gtest/gtest.h>

using namespace std;

/**
 * @brief Запускает основную программу.
 *
 * @details Функция читает выражение из входного файла, строит дерево выражений,
 * генерирует таблицу истинности и записывает её в выходной файл.
 *
 * @param[in] pathToInputFile Путь к входному файлу, содержащему постфиксное выражение.
 * @param[in] pathToOutputFile Путь к выходному файлу, в который будет записана таблица истинности.
 * @result таблица истинности в указанном файле @p pathToOutputFile
 */
void runMainProgram(const string &pathToInputFile, const string &pathToOutputFile) {
    ifstream inFile(pathToInputFile);
    if (!inFile.is_open()) {
        std::cerr << "The input file " << pathToInputFile << " specified is incorrect. The file may not exist" << std::endl;
        exit(1);
    }

    string postfixTree;
    getline(inFile, postfixTree);
    inFile.close();

    list<Exception> exps;
    ExprNode *tree = ExprNodeBuilder::buildExprTree(postfixTree, exps);

    if (not exps.empty()) {
        for (const auto &e: exps) {
            std::cerr << e.what() << endl;
        }
        exit(1);
    }

    string htmlTable;

    try {
        htmlTable = TruthTableGenerator::generateTable(tree);
    } catch (Exception &e) {
        std::cerr << e.what() << endl;
        exit(1);
    }

    std::ofstream outFile(pathToOutputFile);
    if (!outFile.is_open()) {
        std::cerr << "Failed to access output file:" << pathToOutputFile << std::endl;
        exit(1);
    }

    outFile << htmlTable;
    outFile.close();
}

/**
 * @brief Точка входа в программу.
 *
 * @details Функция проверяет аргументы командной строки и запускает программу в
 * соответствующем режиме. Если аргументы соответствуют режиму тестирования,
 * запускаются тесты. В противном случае запускается основная программа с
 * переданными путями к входному и выходному файлам.
 *
 * @note При @p argc=2 и @p argv[1]=--test - запускаются тесты \n
 * @note При @p argc=3 - запускается основная программа, где параметры: \n
 * @p argv[1] - путь к входному файлу с разбором логического выражения, записанного в постфиксном формате \n
 * @p argv[2] - путь к выходному файлу, где будет содержаться html код таблицы истинности \n
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return int Код возврата. 0 - успешное завершение, 1 - ошибка.
 *
 * Запуск программы из консоли для Windows. \n
 *
 * Для запуска тестов:
 * @code
 * ModuleWork_Q_RS_main.exe --test # запускает тесты
 * @endcode
 *
 * Для запуска основной программы:
  * @code
 * ModuleWork_Q_RS_main.exe input.txt out.html
 * @endcode
 */
int main(int argc, char *argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--test") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else if (argc == 3) {
        string pathToInputFile = argv[1];
        string pathToOutputFile = argv[2];
        runMainProgram(pathToInputFile, pathToOutputFile);
        return 0;
    } else {
        std::cerr << "Use: " << argv[0]
                  << " <path to file with postfix tree> <path to output file> or --test" << std::endl;
        return 1;
    }
}
