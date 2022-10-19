//
// Created by Luca Brignone on 10/08/22.
//

#ifndef PROGETTO_PERSON_H
#define PROGETTO_PERSON_H

/*
 * qui definisco le carattristiche comuni sia per gli studenti che professiri, e che verranno ereditate dalle rispettive
 * classi derivate
 */

#include <string>

using namespace std;

class Person {
public:
    Person() {};
    Person(const string& name, const string& surname, const string& mail);
    string& getName() const;
    void setName(const string& name);
    string& getSurname() const;
    void setSurname(const string& surname);
    string& getMail() const;
    bool setMail(const string& mail);
    string& getId() const;
    virtual bool generateNewId(const string& id) { return false; };
    const bool operator <(const Person& personToCompare) const;


private:
    string _name;
    string _surname;
    string _mail;

protected:
    string _id;
};


#endif //PROGETTO_PERSON_H
