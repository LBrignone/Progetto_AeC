//
// Created by Luca Brignone on 17/08/22.
//

#include "AssociateProfessor.h"

AssociateProfessor::AssociateProfessor(const AssociateProfessor& toCopy) {
    this->_itToProfessor = toCopy._itToProfessor;
    this->_isMain = toCopy._isMain;
    this->_lessonH = toCopy._lessonH;
    this->_exerciseH = toCopy._exerciseH;
    this->_labH = toCopy._labH;
    this->_toCek = toCopy._toCek;
}

list<Professor>::iterator AssociateProfessor::getProfessorPointer() const {
    return _itToProfessor;
}

void AssociateProfessor::setProfessorPointer(list<Professor>::iterator addressOfProfessor) {
    _itToProfessor = addressOfProfessor;
}

int AssociateProfessor::getLessonH() const {
    return _lessonH;
}

bool AssociateProfessor::setLessonH(const int &lessonH) {
    if (lessonH > -1) {
        _lessonH = lessonH;
        return true;
    } else {
        return false;
    }
}

int AssociateProfessor::getExerciseH() const {
    return _exerciseH;
}

bool AssociateProfessor::setExerciseH(const int &exerciseH) {
    if (exerciseH > -1) {
        _exerciseH = exerciseH;
        return true;
    } else {
        return false;
    }
}

int AssociateProfessor::getLabH() const {
    return _labH;
}

bool AssociateProfessor::setLabH(const int &labH) {
    if (labH > -1) {
        _labH = labH;
        return true;
    } else {
        return false;
    }
}

bool AssociateProfessor::getIsMain() const {
    return _isMain;
}

void AssociateProfessor::setIsMain(const bool &isMain) {
    _isMain = isMain;
}

bool AssociateProfessor::getToCheck() const {
    return _toCek;
}

void AssociateProfessor::setToCek(const bool& modify) {
    _toCek = modify;
}

void AssociateProfessor::clear(const list<Professor>::iterator initToProfessorListEnd){
    _itToProfessor = initToProfessorListEnd;
    _lessonH = -1;
    _exerciseH = -1;
    _labH = -1;
    _isMain = false;
}

AssociateProfessor& AssociateProfessor::operator =(const AssociateProfessor& toCopy) {
    _itToProfessor = toCopy._itToProfessor;
    _lessonH = toCopy._lessonH;
    _exerciseH = toCopy._exerciseH;
    _labH = toCopy._labH;
    _isMain = toCopy._isMain;
    return *this;
}
