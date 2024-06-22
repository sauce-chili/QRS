#include <iostream>
#include <fstream>
#include <string>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "truthtablegererator/Generator.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cerr << "Use: " << argv[0]
                  << " <path to file with postfix tree> <path to output file>" << std::endl;
        return 1;
    }

    string pathToInputFile = argv[1];
    string pathToOutputFile = argv[2];

    ifstream inFile(pathToInputFile);
    if (!inFile.is_open()) {
        std::cerr << "The input file " << pathToInputFile << " specified is incorrect. The file may not exist" << std::endl;
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
        std::cerr << "Failed to access output file:" << pathToOutputFile << std::endl;
        return 1;
    }

    outFile << htmlTable;
    outFile.close();

    return 0;
}