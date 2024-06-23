//
// Created by sc on 12.06.24.
//

#ifndef MODULEWORK_Q_RS_TESTUTILS_H
#define MODULEWORK_Q_RS_TESTUTILS_H

#include <iostream>
#include <vector>
#include <list>
#include "exception/Exceptions.h"

/**
 * Псевдоноим для списка ошибок
 * */
using ExceptionList = std::list<Exception>;

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
std::string trim(const std::string &str);

/**
 * @brief Функция извлекает данные из строки, представляющей строку таблицы HTML.
 *
 * @param htmlRow [in] Строка, представляющая строку таблицы HTML.
 * @return Вектор строк, содержащий данные из ячеек таблицы.
 */
std::vector<std::string> extractRowData(const std::string& htmlRow);

/**
 * @brief Функция извлекает заголовки из таблицы HTML.
 *
 * @param htmlTable [in] Строка, представляющая таблицу HTML.
 * @return Вектор строк, содержащий заголовки таблицы.
 */
std::vector<std::string> extractHeaders(const std::string& htmlTable);

/**
 * @brief Функция извлекает значения из таблицы HTML.
 *
 * @param htmlTable [in] Строка, представляющая таблицу HTML.
 * @return Вектор векторов строк, содержащий значения из ячеек таблицы.
 */
std::vector<std::vector<std::string>> extractValues(const std::string& htmlTable);

void parseHTMLTable(const std::string &html, std::vector<std::string> &headers,
                    std::vector<std::vector<std::string>> &values);

#endif //MODULEWORK_Q_RS_TESTUTILS_H

