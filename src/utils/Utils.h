//
// Created by sc on 20.06.24.
//

#ifndef MODULWORD_Q_RS_UTILS_H
#define MODULWORD_Q_RS_UTILS_H

#include <iostream>

bool isBinary(const std::string &str);

bool isOctal(const std::string &str);

bool isHexadecimal(const std::string &str);

bool isDecimal(const std::string &str);

double convertToDecimal(const std::string &str);

/*!
 * @brief Фукнкция извлекает бит числа
 * @param num число, из которого извлекается бит
 * @param n позиция бита (начинается с 1)
 * @return бит числа @p num на позации @p n
 * */
int extractBitOfNumber(int num, int n);

#endif //MODULWORD_Q_RS_UTILS_H
