//
// Created by sc on 22.04.24.
//

#ifndef MODULWORD_Q_RS_GENERATOR_H
#define MODULWORD_Q_RS_GENERATOR_H


#include <list>
#include "entities/ExprNode.h"

class TruthTableGenerator {
private:
    static const std::string CELL_TAGS[2];
    static const std::string ROW_TAGS[2];
    static const std::string TABLE_TAGS[2];

    static std::string createCell(const std::string &val);

    static std::string createRowsOfValues(ExprNode *root, int countOfParams);

    static std::string createHeader(std::vector<ExprNode *> &params);

public:
    static const unsigned int MAX_COLUMN = 10;

    /*!
     * @brief Функция создаёт html-код строки значений параметров
     * @param[in] args - значения принимаемые параметрами
     * @param[in] countColumns - кол-во параметров
     * @param[in] result - значение принимаемое логическим выражением
     * */
    static std::string createRow(unsigned short args, int countColumns, bool result);

    /*!
     * @brief Функция создает html-код таблицы истинности для переданного дерева логического выражения
     * @param[in] root - корень дерева логического выражения
     * @return html-код таблицы истинности
     * */
    static std::string generateTable(ExprNode *root);
};


#endif //MODULWORD_Q_RS_GENERATOR_H
