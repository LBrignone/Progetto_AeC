//
// Created by Luca Brignone on 10/08/22.
//

#include "Person.h"

Person::Person(const string& name, const string& surname, const string& mail) {
    _name = name;
    _surname = surname;
    _mail = mail;
}

string& Person::getName() const {
    return (string &) _name;
}

void Person::setName(const string& name) {
    _name = name;
}

string& Person::getSurname() const {
    return (string &) _surname;
}

void Person::setSurname(const string& surname) {
    _surname = surname;
}

string& Person::getMail() const {
    return (string &) _mail;
}

bool Person::setMail(const string& mail) {
    bool toReturn;
    int position, prevPosition;

    position = mail.find('@', 0);
    if ((position != string::npos) && (position != 0)) {
        prevPosition = position;
        position = mail.find('@', position + 1);
        if (position != string::npos) {
            toReturn = false;
        } else {
            position = mail.find('.', prevPosition);
            if ((position != string::npos) && ((position - prevPosition) > 1) && (position != mail.length() - 1)) {
                _mail = mail;
                toReturn = true;
            } else {
                toReturn = false;
            }
        }
    } else {
        toReturn = false;
    }

    return toReturn;
}

string& Person::getId() const {
    return (string &) _id;
}

const bool Person::operator < (const Person& personToCompare) const{
    int tmpIdRvalue, tmpIdLvalue;
    tmpIdRvalue = stoi(personToCompare.getId().substr(1, personToCompare.getId().size() - 1));
    tmpIdLvalue = stoi(_id.substr(1, _id.size() - 1));

    return tmpIdLvalue < tmpIdRvalue;
}
