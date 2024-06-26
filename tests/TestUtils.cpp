//
// Created by sc on 12.06.24.
//
#include <algorithm>
#include "TestUtils.h"
#include "utils/Utils.h"

static const size_t openTagLength = 4;
static const size_t closeTagLength = 5;


std::vector<std::string> extractRowData(const std::string &htmlRow) {
    std::vector<std::string> rowData;
    size_t tdPos = 0;
    while ((tdPos = htmlRow.find("<td>", tdPos)) != std::string::npos) {
        tdPos += openTagLength; // Пропускаем <td>
        size_t tdEndPos = htmlRow.find("</td>", tdPos);
        std::string cell = htmlRow.substr(tdPos, tdEndPos - tdPos);
        rowData.push_back(trim(cell));
        tdPos = tdEndPos + closeTagLength; // Пропускаем </td>
    }
    return rowData;
}

std::vector<std::string> extractHeaders(const std::string &htmlTable) {
    std::vector<std::string> headers;
    size_t pos = htmlTable.find("<tr>");
    if (pos != std::string::npos) {
        pos += openTagLength; // Пропускаем <tr>
        size_t endPos = htmlTable.find("</tr>", pos);
        std::string row = htmlTable.substr(pos, endPos - pos);
        headers = extractRowData(row);
    }
    return headers;
}

std::vector<std::vector<std::string>> extractValues(const std::string &htmlTable) {
    std::vector<std::vector<std::string>> values;
    size_t pos = htmlTable.find("<tr>");
    if (pos != std::string::npos) {
        pos = htmlTable.find("<tr>", pos + openTagLength); // Пропускаем первую строку (заголовки)
        while (pos != std::string::npos) {
            pos += openTagLength; // Пропускаем <tr>
            size_t endPos = htmlTable.find("</tr>", pos);
            std::string row = htmlTable.substr(pos, endPos - pos);
            values.push_back(extractRowData(row));
            pos = htmlTable.find("<tr>", endPos + closeTagLength);
        }
    }
    return values;
}