//
// Created by Luca Brignone on 06/10/22.
//

#include "ErrorHandling.h"

isNotMain::isNotMain():message("the first elemento of the list is not the regular professor");

const char* isNotMain::what() const noexcept {
    return message;
}