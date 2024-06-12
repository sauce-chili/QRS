//
// Created by sc on 12.06.24.
//

#ifndef MODULWORD_Q_RS_TESTUTILS_H
#define MODULWORD_Q_RS_TESTUTILS_H

#include <iostream>
#include <vector>

void removeWhiteSeparators(std::string &s);

std::string trim(const std::string &str);

std::vector<std::string> extractRowData(const std::string& row);

std::vector<std::string> extractHeaders(const std::string& html);

std::vector<std::vector<std::string>> extractValues(const std::string& html);

void parseHTMLTable(const std::string &html, std::vector<std::string> &headers,
                    std::vector<std::vector<std::string>> &values);

#endif //MODULWORD_Q_RS_TESTUTILS_H

