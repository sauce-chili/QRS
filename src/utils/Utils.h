//
// Created by sc on 20.06.24.
//

#ifndef MODULEWORK_Q_RS_UTILS_H
#define MODULEWORK_Q_RS_UTILS_H

#include <iostream>
#include <climits>

/**
 * @brief Функция удаляет все пробельные символы из строки.
 *
 * @param s [in, out] Строка, из которой нужно удалить пробельные символы.
 */
void removeWhiteSeparators(std::string &s);

/**
 * @brief Функция удаляет пробельные символы в начале и конце строки.
 *
 * @param str [in] Строка, которую нужно обрезать.
 * @return Новая строка без пробельных символов в начале и конце.
 */
std::string trim(const std::string &str, const std::string &predicate = " \t");

/**
 * @brief Метод оборачивает @p wrapable в пару значений @p wrapper[2]
 * @param[in] wrapper обертка для значения @p wrapable
 * @param[in] wrapable оборачиваемое значение
 * @return обернутое в пару @p wrapper значение.
 *
 * Пример использования:
 * @code
 *  string wrapper[2] = {"(", ")"};
 *  string wrapable = "a + b";
 *  wrapIn(wrapper, wrapable); // result: (a+b)
 * @endcode
 * */
std::string wrapIn(const std::string wrapper[2], const std::string &wrapable);

/**
 * @brief Функция проверяет, является ли строка двоичным числом.
 *
 * @details Эта функция поверяет, состоит ли строка только из символов '0' и '1', что делает её допустимым двоичным числом.
 *
 * @param[in] str входная строка для проверки.
 * @return true, если строка является двоичным числом; false в противном случае.
 */
bool isBinary(const std::string &str);

/**
 * @brief Функция проверяет, является ли строка восьмеричным числом.
 * @details Эта функция проверяет, состоит ли строка только из символов от '0' до '7', что делает её допустимым восьмеричным числом.
 * @param[in] str входная строка для проверки.
 * @return true, если строка является восьмеричным числом; false в противном случае.
 */
bool isOctal(const std::string &str);

/**
 * @brief Функция проверяет, является ли строка шестнадцатеричным числом.
 *
 * @details Эта функция проверяет, состоит ли строка из символов от '0' до '9' и от 'a' до 'f' или от 'A' до 'F', что делает её допустимым шестнадцатеричным числом.
 *
 * @param str входная строка для проверки.
 * @return true, если строка является шестнадцатеричным числом; false в противном случае.
 */
bool isHexadecimal(const std::string &str);

/**
 * @brief Функция проверяет, является ли строка десятичным числом.
 *
 * @details Эта функция проверяет, состоит ли строка только из цифр от '0' до '9' и/или строковых литералов (f,F,l,L), что делает её допустимым десятичным числом.
  * @param str входная строка для проверки.
 * @return true, если строка является десятичным числом; false в противном случае.
 */
bool isDecimal(const std::string &str);

/**
 * @brief Функция преобразует строку в десятичное число.
 * @details Эта функция принимает строку, представляющую число в любом из поддерживаемых форматов в С++ (двоичный, восьмеричный, десятичный, шестнадцатеричный)
 * и преобразует её в десятичное число с плавающей точкой. Формат числа определяется автоматически на основе содержимого строки.
 * @param str входная строка для преобразования.
 * @return число с плавающей точкой, представляющее десятичное значение входной строки.
 * @throws std::invalid_argument если строка не является допустимым числом в одном из поддерживаемых форматов.
 */
double convertToDecimal(const std::string &str);

/*!
 * @brief Фукнкция извлекает бит числа
 * @param num число, из которого извлекается бит
 * @param n позиция бита (начинается с 1)
 * @return бит числа @p num на позации @p n
 * */
int extractBitOfNumber(int num, int n);

/**
 * @brief Функция разворачивает заданное количество битов в числа.
 *
 * @details Эта функция принимает число и разворачивает указанное количество бит, начиная с младшего бита.
 *
 * @tparam T тип числа, для которого производится операция.
 * @param num число, биты которого нужно развернуть.
 * @param nb количество бит, которые нужно развернуты (по умолчанию, все биты в числе).
 * @return число с развернутыми битами.
 * @throws std::invalid_argument если количество бит для переворота превышает количество бит в числе.
 *
 * @note Если `nb` не указано, по умолчанию используется количество бит в числе типа `T`.
 *
 * Пример использования:
 * @code
 * uint8_t x = 0b00001111;
 * uint8_t y = reverseBits(x, 8); // y будет равно 0b11110000
 * @endcode
 */
template<typename T>
T reverseBits(T num, size_t nb = sizeof(T) * CHAR_BIT) {

    if (nb > std::numeric_limits<T>::digits) {
        throw std::invalid_argument("The number of reversal bits exceeds the number of bits in the number");
    }

    T rv = 0;

    for (size_t i = 0; i < nb; ++i, num >>= 1) {
        rv = (rv << 1) | (num & 0x01);
    }

    return rv;
}

#endif //MODULEWORK_Q_RS_UTILS_H
