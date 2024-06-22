//
// Created by sc on 08.04.24.
//

#include "Exceptions.h"

const char *Exception::what() const noexcept {
    return message.c_str();
}

bool Exception::operator==(const Exception &other) const {
    return message == other.message;
}

EmptyTreeException::EmptyTreeException() {
    message = "Empty tree";
}

MissingOperand::MissingOperand(std::string operation, int pos) : operation(operation), pos(pos) {
    message = "Missing operand for operation \"" + operation + "\" at position " + std::to_string(pos);
}

bool MissingOperand::operator==(const Exception &other) const {
    if (const MissingOperand* o = dynamic_cast<const MissingOperand*>(&other)) {
        return this->pos == o->pos && this->operation == o->operation;
    }
    return false;
}

UnexpectedElementException::UnexpectedElementException(std::string elem, int pos) : elem(elem), pos(pos) {
    message = "Unknown sequence \"" + elem + "\" at position " + std::to_string(pos);
}


bool UnexpectedElementException::operator==(const Exception &other) const {
    if (const UnexpectedElementException* o = dynamic_cast<const UnexpectedElementException*>(&other)) {
        return this->pos == o->pos && this->elem == o->elem;
    }
    return false;
}

ExtraOperandException::ExtraOperandException(std::string oprand, int pos) : operand(oprand), pos(pos) {
    message = "Extra operand \"" + oprand + "\" at position " + std::to_string(pos);
}

bool ExtraOperandException::operator==(const Exception &other) const {
    if (const auto* o = dynamic_cast<const ExtraOperandException*>(&other)) {
        return this->pos == o->pos && this->operand == o->operand;
    }
    return false;
}

ArithmeticCalculationException::ArithmeticCalculationException() {
    message = "It is not possible to evaluate this expression arithmetically";
}

ExceedingLimitParametersException::ExceedingLimitParametersException(int limit) {
    message = "The number of different parameters must be less than or equal to " + std::to_string(limit);
}
