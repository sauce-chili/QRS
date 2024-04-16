//
// Created by sc on 08.04.24.
//

#ifndef MODULWORD_Q_RS_EXCEPTIONS_H
#define MODULWORD_Q_RS_EXCEPTIONS_H


#include <string>

class MissingOperand : std::exception {
    int pos;
public:
    MissingOperand(int pos);

    const char *what() const noexcept override;
};

class UnexpectedElementException : std::exception {
    int pos;
public:
    UnexpectedElementException(int pos);

    const char *what() const noexcept override;
};

class ExceedingLimitParameters : std::exception {
    const char *what() const noexcept override;
};

#endif //MODULWORD_Q_RS_EXCEPTIONS_H
