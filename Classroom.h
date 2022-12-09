//
// Created by Luca Brignone on 17/08/22.
//

#ifndef PROGETTO_CLASSROOM_H
#define PROGETTO_CLASSROOM_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

class Classroom {
public:
    Classroom() {};
    Classroom(const Classroom& toCopy);
    ~Classroom() {};
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
    bool getOccupation(const int& hourSlot);
    void setOccupation(const int& hourSlot, const bool& status);
    bool operator <(const Classroom& classroomToCompare);
    Classroom& operator =(const Classroom& toAssign);
    ostream& operator <<(ostream& os) const;

private:
    string _id;
    char _type = '\0';
    string _classroomName;
    int _capacity = 0;
    int _examCapacity = 0;
    vector<bool> _hourSlotOccupation = {false, false, false, false, false, false};
};


#endif //PROGETTO_CLASSROOM_H
