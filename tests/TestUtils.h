//
// Created by sc on 12.06.24.
//

#ifndef MODULEWORK_Q_RS_TESTUTILS_H
#define MODULEWORK_Q_RS_TESTUTILS_H

#include <iostream>
#include <vector>
#include <list>
#include "exception/Exceptions.h"

using ExceptionList = std::list<Exception>;

void removeWhiteSeparators(std::string &s);

std::string trim(const std::string &str);

std::vector<std::string> extractRowData(const std::string& htmlRow);

std::vector<std::string> extractHeaders(const std::string& htmlTable);

std::vector<std::vector<std::string>> extractValues(const std::string& htmlTable);

void parseHTMLTable(const std::string &html, std::vector<std::string> &headers,
                    std::vector<std::vector<std::string>> &values);

#endif //MODULEWORK_Q_RS_TESTUTILS_H

