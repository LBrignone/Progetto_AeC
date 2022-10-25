//
// Created by Luca Brignone on 16/08/22.
//

#include "Student.h"

bool Student::setId(const string& id){
    int prevId;
    stringstream tmp;
    if ((id != "") && (id.size()==7)) {
        if (id[0] == 's') {
            try {
                stoi(id.substr(1, id.size() - 1));
            }
            catch (const invalid_argument& excepFromStoi) {
                return false;
            }
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
    if (!id.empty()) {
        if (id[0] == 's' && id.size() == 7) {
            try {
                prevId = stoi(id.substr(1, 6), nullptr, 10);
            }
            catch (const invalid_argument& excepFromStoi) {
                return false;
            }
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

ostream& Student::operator <<(ostream& os) const {
    os << _id << ";" << (this)->getName() << ";" << (this)->getSurname() << ";" << (this)->getMail();
    return os;
}