//
// Created by sc on 08.04.24.
//

#ifndef MODULWORD_Q_RS_EXCEPTIONS_H
#define MODULWORD_Q_RS_EXCEPTIONS_H


#include <string>

class Exception : public std::exception {
protected:
    std::string message;
public:
    const char *what() const noexcept override;
    virtual bool operator==(const Exception &other) const;
};

class EmptyTreeException : public Exception {
public:
    EmptyTreeException();
};

class MissingOperand : public Exception {
    int pos;
    std::string opr;
public:
    MissingOperand(std::string opr, int pos);

    bool operator==(const Exception &other) const override;
};

class UnexpectedElementException : public Exception {
    int pos;
    std::string elem;
public:
    UnexpectedElementException(std::string elem, int pos);

    bool operator==(const Exception &other) const override;
};

class ExtraOperandException : public Exception {
    int pos;
    std::string opr;
public:
    ExtraOperandException(std::string opr, int pos);

    bool operator==(const Exception &other) const override;
};

class ExceedingLimitParametersException : public Exception {
public:
    ExceedingLimitParametersException();
};

#endif //MODULWORD_Q_RS_BUILDEXCEPTIONS_H
