//
// Created by sc on 08.04.24.
//

#include "Exceptions.h"

UnexpectedElementException::UnexpectedElementException(int pos) {
    this->pos = pos;
}

const char *UnexpectedElementException::what() const noexcept {
    return ("Неизвестный элемент на позиции" + std::to_string(pos)).c_str();
}

MissingOperand::MissingOperand(int pos) {
    this->pos = pos;
}

const char *MissingOperand::what() const noexcept {
    return ("Не операнда у операнда на позиции: " + std::to_string(pos)).c_str();
}

const char *ExceedingLimitParameters::what() const noexcept {
    return "Превышен предел максимального кол-ва параметров";
}
