//
// Created by Luca Brignone on 17/08/22.
//

#include "Classroom.h"

const string& Classroom::getId() const {
    return _id;
}

bool Classroom::setId(const string& id) {
    _id = id;
}

bool Classroom::generateNewId(const string &id) {
    int prevId;
    stringstream tmp;
    if (id != "") {
        if (id[0] == 'A') {
            prevId = stoi(id.substr(1, 3), nullptr, 10);
            prevId++;
            tmp << 'A' << setfill('0') << setw(3) << prevId;
            _id = tmp.str();
            return true;
        } else {
            return false;
        }
    } else {
        _id = "A001";
    }
}

char Classroom::getType() const {
    return _type;
}

bool Classroom::setType(const char &type) {
    char tmp = type;
    if ((type > 96) && (type < 123)) {
        tmp -= 32;
    }
    if ((tmp == 'A') || (tmp == 'L')) {
        _type = type;
        return true;
    } else {
        return false;
    }
}

const string& Classroom::getClassroomName() const {
    return _classroomName;
}

void Classroom::setClassroomName(const string& classroomName) {
    _classroomName = classroomName;
}

int Classroom::getCapacity() const {
    return _capacity;
}

bool Classroom::setCapacity(const int &capacity) {
    if (capacity > 0) {
        _capacity = capacity;
        return true;
    } else {
        return false;
    }
}

int Classroom::getExamCapacity() const {
    return _examCapacity;
}

bool Classroom::setExamCapacity(const int &examCapacity) {
    if ((examCapacity > 0) && (examCapacity < _capacity)) {
        _examCapacity = examCapacity;
        return true;
    } else {
        return false;
    }
}

const bool& Classroom::operator < (const Classroom& classroomToCompare) {
    int tmpIdRvalue, tmpIdLvalue;
    tmpIdRvalue = stoi(classroomToCompare.getId().substr(1, classroomToCompare.getId().size() - 1));
    tmpIdLvalue = stoi(_id.substr(1, _id.size() - 1));
    return tmpIdLvalue < tmpIdRvalue;
}

ostream& Classroom::operator << (ostream& os) {
    os << _id << ";" << _type << ";" << _classroomName << ";" << _capacity << ";" << _examCapacity;
    return os;
}