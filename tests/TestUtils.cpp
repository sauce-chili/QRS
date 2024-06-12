//
// Created by sc on 12.06.24.
//
#include "TestUtils.h"

static const size_t openTagLength = 4;
static const size_t closeTagLength = 5;

void removeWhiteSeparators(std::string &s) {
    s.erase(
            std::remove_if(s.begin(), s.end(),
                           [](unsigned char c) { return std::isspace(c); }), s.end());
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Функция для извлечения содержимого ячеек из строки таблицы
std::vector<std::string> extractRowData(const std::string &row) {
    std::vector<std::string> rowData;
    size_t tdPos = 0;
    while ((tdPos = row.find("<td>", tdPos)) != std::string::npos) {
        tdPos += openTagLength; // Пропускаем <td>
        size_t tdEndPos = row.find("</td>", tdPos);
        std::string cell = row.substr(tdPos, tdEndPos - tdPos);
        rowData.push_back(trim(cell));
        tdPos = tdEndPos + closeTagLength; // Пропускаем </td>
    }
    return rowData;
}

// Функция для выделения заголовков таблицы
std::vector<std::string> extractHeaders(const std::string &html) {
    std::vector<std::string> headers;
    size_t pos = html.find("<tr>");
    if (pos != std::string::npos) {
        pos += openTagLength; // Пропускаем <tr>
        size_t endPos = html.find("</tr>", pos);
        std::string row = html.substr(pos, endPos - pos);
        headers = extractRowData(row);
    }
    return headers;
}

// Функция для выделения значений строк таблицы
std::vector<std::vector<std::string>> extractValues(const std::string &html) {
    std::vector<std::vector<std::string>> values;
    size_t pos = html.find("<tr>");
    if (pos != std::string::npos) {
        pos = html.find("<tr>", pos + openTagLength); // Пропускаем первую строку (заголовки)
        while (pos != std::string::npos) {
            pos += openTagLength; // Пропускаем <tr>
            size_t endPos = html.find("</tr>", pos);
            std::string row = html.substr(pos, endPos - pos);
            values.push_back(extractRowData(row));
            pos = html.find("<tr>", endPos + closeTagLength);
        }
    }
    return values;
}


void parseHTMLTable(const std::string &html, std::vector<std::string> &headers,
                    std::vector<std::vector<std::string>> &values) {
    headers = extractHeaders(html);
    values = extractValues(html);
}