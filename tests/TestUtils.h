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

#endif //MODULEWORK_Q_RS_TESTUTILS_H

