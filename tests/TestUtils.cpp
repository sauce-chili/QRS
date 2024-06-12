//
// Created by sc on 12.06.24.
//
#include "TestUtils.h"

void removeWhiteSeparators(std::string &s) {
    s.erase(
            std::remove_if(s.begin(), s.end(),
                           [](unsigned char c) { return std::isspace(c); }), s.end());
}