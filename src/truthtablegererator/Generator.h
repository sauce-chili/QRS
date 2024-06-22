//
// Created by sc on 22.04.24.
//

#ifndef MODULEWORK_Q_RS_GENERATOR_H
#define MODULEWORK_Q_RS_GENERATOR_H


#include <list>
#include "entities/ExprNode.h"

/**
 * @brief Класс для создания таблицы истинности заданного выражения
 * */
class TruthTableGenerator {
private:

    static const std::string CELL_TAGS[2]; ///< Теги ячейки таблицы
    static const std::string ROW_TAGS[2]; ///< Теги строки таблицы
    static const std::string TABLE_TAGS[2]; ///< Теги таблицы

    static const std::string HTML_DOC_WRAPPER[2]; ///< Обёртка html файла для таблицы

    /*!
     * @brief Метод генерирует html код ячейки таблицы
     * @param[in] val содержимое ячейки
     * @return html код ячейки таблицы
     * */
    static std::string createCell(const std::string &val);

    /**
     * @brief Метод генерирует html код строк значений таблицы истинности
     * @param[in] root дерево выражения
     * @param[in] countOfParams количество найденных параметров
     * @return html код строк значений таблицы истинности
     * */
    static std::string createRowsOfValues(ExprNode *root, int countOfParams);

    /**
     * @brief Метод генерирует html код заголовка таблицы
     * @param[in] params параметры найденные в выражение
     * @return html код строки-заголовка таблицы
     * */
    static std::string createHeader(std::vector<ExprNode *> &params);

public:
    static const unsigned int MAX_COLUMN = 10;

    /**
     * @brief Метод создаёт html-код строки значений параметров
     * @param[in] args значения принимаемые параметрами
     * @param[in] countColumns кол-во параметров
     * @param[in] result значение принимаемое логическим выражением
     * @return html код строки таблицы
     * */
    static std::string createRow(unsigned short args, int countColumns, bool result);

    /**
     * @brief Метод создает html-код таблицы истинности для переданного дерева логического выражения
     * @param[in] root корень дерева логического выражения
     * @return html-код таблицы истинности
     * @throw ExceedingLimitParametersException
     * @see ExceedingLimitParametersException
     * */
    static std::string generateTable(ExprNode *root);
};


#endif //MODULEWORK_Q_RS_GENERATOR_H
