//
// Created by Luca Brignone on 16/08/22.
//

#include "Student.h"

bool Student::setId(const string& id){
    int prevId;
    stringstream tmp;
    if ((id != "") && (id.size()==7)) {
        if (id[0] == 's') {
            _id = id;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Student::generateNewId(const string &id) {
    int prevId;
    stringstream tmp;
    if (id != "") {
        if (id[0] == 's') {
            prevId = stoi(id.substr(1, 6), nullptr, 10);
            prevId++;
            tmp << 's' << setfill('0') << setw(6) << prevId;
            _id = tmp.str();
            return true;
        } else {
            return false;
        }
    } else {
        _id = "s000001";
        return true;
    }
}

ostream& Student::operator << (ostream& os) {
    os << _id << ";" << (this)->getName() << ";" << (this)->getSurname() << ";" << (this)->getMail();
    return os;
}