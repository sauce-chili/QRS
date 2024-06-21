//
// Created by sc on 20.06.24.
//

#ifndef MODULWORD_Q_RS_UTILS_H
#define MODULWORD_Q_RS_UTILS_H

#include <iostream>
#include <climits>

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

template<typename T>
T reverseBits(T n, size_t b = sizeof(T) * CHAR_BIT) {

    if (b > std::numeric_limits<T>::digits) {
        throw std::invalid_argument("The number of reversal bits exceeds the number of bits in the number");
    }

    T rv = 0;

    for (size_t i = 0; i < b; ++i, n >>= 1) {
        rv = (rv << 1) | (n & 0x01);
    }

    return rv;
}

#endif //MODULWORD_Q_RS_UTILS_H
