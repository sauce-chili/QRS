//
// Created by sc on 20.06.24.
//

#include "Utils.h"
#include "BuilderUtils.h"

#include <string>
#include <regex>
#include <stdexcept>
#include <cstdlib>

bool isBinary(const std::string &str) {
    std::regex binaryPattern(R"(^[-+]?0[bB][01]+$)");
    return std::regex_match(str, binaryPattern);
}

bool isOctal(const std::string &str) {
    std::regex octalPattern(R"(^[-+]?0[0-7]+$)");
    return std::regex_match(str, octalPattern);
}

bool isHexadecimal(const std::string &str) {
    std::regex hexPattern(R"(^[-+]?0[xX][0-9a-fA-F]+$)");
    return std::regex_match(str, hexPattern);
}

bool isDecimal(const std::string &str) {
    std::regex decimalPattern(R"(^[-+]?\d+(\.\d*)?([eE][-+]?\d+)?([fFlL]{0,2})?$)");
    return std::regex_match(str, decimalPattern);
}

double convertToDecimal(const std::string &str) {
    if (str == "true") {
        return 1.0;
    } else if (str == "false") {
        return 0.0;
    }

    std::string s = str;
    bool isNegative = false;
    if (s[0] == '-') {
        isNegative = true;
        s = s.substr(1);
    } else if (s[0] == '+') {
        s = s.substr(1);
    }

    char *end;
    double result = 0.0;

    if (isBinary(s)) {
        result = std::strtoll(s.c_str() + 2, &end, 2);
    } else if (isOctal(s)) {
        result = std::strtoll(s.c_str() + 1, &end, 8);
    } else if (isHexadecimal(s)) {
        result = std::strtoll(s.c_str() + 2, &end, 16);
    } else if (isDecimal(s)) {
        size_t suffix_pos = s.find_first_of("fFlL");
        if (suffix_pos != std::string::npos) {
            s = s.substr(0, suffix_pos);
        }
        result = std::strtod(s.c_str(), &end);
    } else {
        throw std::invalid_argument("Invalid constant format");
    }

    return isNegative ? -result : result;
}

int extractBitOfNumber(int num, int n) {
    ushort mask = 1 << (n - 1);
    ushort bit = (num & mask) ? 1 : 0;
    return bit;
}