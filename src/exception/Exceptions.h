//
// Created by sc on 08.04.24.
//

#ifndef MODULWORD_Q_RS_EXCEPTIONS_H
#define MODULWORD_Q_RS_EXCEPTIONS_H


#include <string>

/**
 * @brief Абстрактный класс для реализации исключений
 * */
class Exception : public std::exception {
protected:
    std::string message; ///< Текст ошибки
public:
    const char *what() const noexcept override;
    /**
     * @brief Метод сравнения исключений
     * @param[in] other исключение с которым сравнивается @p this
     * */
    virtual bool operator==(const Exception &other) const;
};

/**
 * @brief Исключений пустого дерева
 * @details Используется при попытке создать дерево из пустой строки.
 * */
class EmptyTreeException : public Exception {
public:
    EmptyTreeException();
};

/**
 * @brief Исключений сигнализирующие об отсутствие операнда у указанной операции
 * */
class MissingOperand : public Exception {
    int pos; ///< позиция операции, у которой отсутствует операнд
    std::string operation; ///< строковое представление операции
public:
    /**
     * @param[in] operation операция
     * @param[in] pos позиция операции у которой отсутствует операнд
     * */
    MissingOperand(std::string operation, int pos);

    bool operator==(const Exception &other) const override;
};

/**
 * @brief Исключение о встреченном неизвестном элементе
 * */
class UnexpectedElementException : public Exception {
    int pos; ///< позиция неизвестного элемента
    std::string elem; ///< неизвестный элемент
public:
    /**
     * @param[in] elem неизвестный элемент
     * @param[in] pos позиция неизвестного элемента
     * */
    UnexpectedElementException(std::string elem, int pos);

    bool operator==(const Exception &other) const override;
};

/**
 * @brief Исключение сигнализирующие о операнде, для которого не была найдена операция
 * */
class ExtraOperandException : public Exception {
    int pos; ///< позиция лишнего операнда
    std::string operand; ///< операнд
public:
    /**
     * @param[in] operand лишний операнд
     * @param[out] pos позиция лишнего операнда
     * */
    ExtraOperandException(std::string operand, int pos);

    bool operator==(const Exception &other) const override;
};

/**
 * @brief Исключение сигнализирующие о превышение максимально допустимого количества параметров в дереве
 * */
class ExceedingLimitParametersException : public Exception {
public:
    /**
     * @param[in] limit максимально допустимое количество параметров
     * */
    explicit ExceedingLimitParametersException(int limit);
};

/**
 * Исключение сигнализирующие о невозможности арифметически вычислить выражение
 * */
class ArithmeticCalculationException : public Exception{
public:
    ArithmeticCalculationException();
};

#endif //MODULWORD_Q_RS_EXCEPTIONS_H
