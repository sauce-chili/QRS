#include <iostream>
#include <fstream>
#include <string>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "truthtablegererator/Generator.h"

using namespace std;


int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cerr << "Используйте: " << argv[0]
                  << " <путь до файла с деревом разбора выражения> <путь до выходного файла>" << std::endl;
        return 1;
    }

    string pathToInputFile = argv[1];
    string pathToOutputFile = argv[2];

    ifstream inFile(pathToInputFile);
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл: " << pathToInputFile << std::endl;
        return 1;
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
        return 1;
    }

    string htmlTable;

    try {
        htmlTable = TruthTableGenerator::generateTable(tree);
    } catch (Exception &e) {
        std::cerr << e.what() << endl;
        return 1;
    }

    // Открываем выходной файл
    std::ofstream outFile(pathToOutputFile);
    if (!outFile.is_open()) {
        std::cerr << "Не удалось получить доступ к выходному файлу: " << pathToOutputFile << std::endl;
        return 1;
    }

    outFile << htmlTable;
    outFile.close();

    return 0;
}