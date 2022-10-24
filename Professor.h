//
// Created by Luca Brignone on 16/08/22.
//

#ifndef PROGETTO_PROFESSOR_H
#define PROGETTO_PROFESSOR_H

#include <map>
#include <list>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Date.h"
#include "Person.h"

using namespace std;

typedef struct AvailForExam {
    Date start;
    Date stop;
} AvailForExam;

class Professor : public Person {
public:
    Professor() {};
    ~Professor() {};
    bool setId(const string& id);
    bool generateNewId(const string& id);
    bool getChangeInUnavail();
    void setChangeInUnavail(const bool& newState);
    void resetChangeInUnavail();
    bool isAvailExamProgramming (const Date& data, const Date& academicYear);
    const list<AvailForExam>& getUnavailListByAcademicYear (const Date& academicYear) const;
    Date getMinDateForUnavail() const;
    Date getMaxDateForUnavail() const;
    void appendUnavailability(const Date &startUnavail, const Date &stopUnavail, const Date& academicYear);
    bool appendUnavailability(const AvailForExam& unavailDates, const Date& academicYear);     // all the controls on date's coherency MUST be performed before colling this function (NO control is performed inside)
    void appendUnavailabilityForExam(const Date &startUnavail, const Date &stopUnavail);
    void clearMapAcademicYearUnavailability(const Date& academicYear);
    const Professor operator ++(int);
    bool operator <(const Professor& toCompare);
    Professor& operator =(const Professor& toCopy);
    Professor& operator =(const list<Professor>::const_iterator & toCopy);
    ostream& operator <<(ostream& os) const;

private:
    bool _changeInUnavail = false;
    map<Date, list<AvailForExam>> _unavailability;
    list<AvailForExam> _unavailabilityForExam;
};


#endif //PROGETTO_PROFESSOR_H
