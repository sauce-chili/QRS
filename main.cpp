#include <iostream>
#include <fstream>
#include <string>
#include "entities/ExprNode.h"
#include "builders/ExprNodeBuilder.h"
#include "truthtablegererator/Generator.h"
#include <gtest/gtest.h>

using namespace std;

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
