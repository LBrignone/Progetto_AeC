//
// Created by Luca Brignone on 10/08/22.
//

#include "Person.h"

Person::Person(const string& name, const string& surname, const string& mail) {
    _name = name;
    _surname = surname;
    _mail = mail;
}

string &Person::getName() const {
    return (string &) _name;
}

void Person::setName(const string& name) {
    _name = name;
}

string &Person::getSurname() const {
    return (string &) _surname;
}

void Person::setSurname(const string &surname) {
    _surname = surname;
}

string &Person::getMail() const {
    return (string &) _mail;
}

bool Person::setMail(const string& mail) {
    int position;
    position = mail.find('@', 0);
    if (position != string::npos){
        position = mail.find('.', position);
        if (position != string::npos){
            _mail = mail;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

string &Person::getId() const {
    return (string &) _id;
}

const bool& Person::operator < (const Person& personToCompare) const{
    int tmpIdRvalue, tmpIdLvalue;
    tmpIdRvalue = stoi(personToCompare.getId().substr(1, personToCompare.getId().size() - 1));
    tmpIdLvalue = stoi(_id.substr(1, _id.size() - 1));
    return tmpIdLvalue < tmpIdRvalue;
}
