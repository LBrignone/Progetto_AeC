//
// Created by Luca Brignone on 17/08/22.
//

#ifndef PROGETTO_CLASSROOM_H
#define PROGETTO_CLASSROOM_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Classroom {
public:
    Classroom() {};
    const string& getId() const;
    bool setId(const string& id);
    bool generateNewId(const string& id);
    char getType() const;
    bool setType(const char& type);
    const string& getClassroomName() const;
    void setClassroomName(const string& classroomName);
    int getCapacity() const;
    bool setCapacity(const int& capacity);
    int getExamCapacity() const;
    bool setExamCapacity(const int& examCapacity);
    const bool& operator < (const Classroom& classroomToCompare);
    ostream& operator << (ostream& os);

private:
    string _id;
    char _type;
    string _classroomName;
    int _capacity;
    int _examCapacity;
};


#endif //PROGETTO_CLASSROOM_H
