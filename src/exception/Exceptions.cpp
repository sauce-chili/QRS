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
    message = "Пустое дерево";
}

MissingOperand::MissingOperand(std::string opr, int pos) : opr(opr), pos(pos) {
    message = "Нет операнда у оператора на позиции: " + std::to_string(pos);
}

bool MissingOperand::operator==(const Exception &other) const {
    if (const MissingOperand* o = dynamic_cast<const MissingOperand*>(&other)) {
        return this->pos == o->pos && this->opr == o->opr;
    }
    return false;
}

UnexpectedElementException::UnexpectedElementException(std::string elem, int pos) : elem(elem), pos(pos) {
    message = "Неизвестный элемент на позиции " + std::to_string(pos);
}

bool UnexpectedElementException::operator==(const Exception &other) const {
    if (const UnexpectedElementException* o = dynamic_cast<const UnexpectedElementException*>(&other)) {
        return this->pos == o->pos && this->elem == o->elem;
    }
    return false;
}

ExtraOperandException::ExtraOperandException(std::string opr, int pos) : opr(opr), pos(pos) {
    message = "Лишний операнд на позиции: " + std::to_string(pos);
}

bool ExtraOperandException::operator==(const Exception &other) const {
    if (const auto* o = dynamic_cast<const ExtraOperandException*>(&other)) {
        return this->pos == o->pos && this->opr == o->opr;
    }
    return false;
}

ExceedingLimitParametersException::ExceedingLimitParametersException() {
    message = "Превышен предел максимального кол-ва параметров";
}
