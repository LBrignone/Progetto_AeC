//
// Created by Luca Brignone on 16/08/22.
//

#ifndef PROGETTO_STUDENT_H
#define PROGETTO_STUDENT_H

#include <sstream>
#include <iomanip>
#include <iostream>

#include "Person.h"

class Student : public Person {
public:
    Student() {};
    ~Student() {};
    bool setId(const string& id);
    bool generateNewId(const string& id);
    ostream& operator <<(ostream& os) const;
};


#endif //PROGETTO_STUDENT_H
