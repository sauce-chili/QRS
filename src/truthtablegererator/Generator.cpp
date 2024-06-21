//
// Created by sc on 22.04.24.
//

#include "Generator.h"
#include "utils/BuilderUtils.h"
#include "utils/Utils.h"
#include "exception/Exceptions.h"
#include <string>
#include <cmath>

const std::string TruthTableGenerator::CELL_TAGS[2] = {"<td>", "</td>"};
const std::string TruthTableGenerator::ROW_TAGS[2] = {"<tr>", "</tr>"};
const std::string TruthTableGenerator::TABLE_TAGS[2] = {"<table>", "</table>"};

std::string TruthTableGenerator::generateTable(ExprNode *root) {

    std::vector<ExprNode *> params;
    root->getParameters(params);

    int countParameters = params.size();

    if (countParameters > MAX_COLUMN) {
        throw ExceedingLimitParametersException();
    }

    std::string table;
    table += createHeader(params);
    table += createRowsOfValues(root, countParameters);
    table = BuilderUtil::wrapIn(TABLE_TAGS, table);

    return table;
}

std::string TruthTableGenerator::createHeader(std::vector<ExprNode *> &params) {
    std::string header;

    for (auto p: params) {
        std::string val = p->toString();
        header += createCell(val);
    }
    header += createCell("F");

    header = BuilderUtil::wrapIn(ROW_TAGS, header);

    return header;
}

std::string TruthTableGenerator::createCell(const std::string &val) {
    std::string cell = BuilderUtil::wrapIn(CELL_TAGS, val);
    return cell;
}

std::string TruthTableGenerator::createRowsOfValues(ExprNode *root, int countOfParams) {
    std::string rowsOfValues;
    int countOfRow = pow(2, countOfParams);
    for (unsigned short p = 0; p < countOfRow; p++) {
        unsigned short rp = reverseBits(p,countOfParams);
        bool result = root->calculate(rp);
        rowsOfValues += createRow(p, countOfParams, result);
    }

    return rowsOfValues;
}

std::string TruthTableGenerator::createRow(unsigned short args, int countColumns, bool result) {

    std::string row;
    for (unsigned short bitIdx = 0; bitIdx < countColumns; bitIdx++) {

        int bit = extractBitOfNumber(args, bitIdx + 1);

        row = createCell(std::to_string(bit)) + row;
    }

    row += createCell(std::to_string(result));

    row = BuilderUtil::wrapIn(ROW_TAGS, row);

    return row;
}
