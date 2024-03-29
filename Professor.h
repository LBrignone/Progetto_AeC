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
    AvailForExam() {}
    AvailForExam(Date date1, Date date2) {start = date1; stop = date2;}
} AvailForExam;

class Professor : public Person {
public:
    Professor() {};
    Professor(const Professor& toCopy);
    ~Professor() {};
    bool setId(const string& id);
    bool generateNewId(const string& id);
    bool getChangeInUnavail();
    void setChangeInUnavail(const bool& newState);
    void resetChangeInUnavail();
    bool isAvailExamProgramming(const Date& startData, const Date& stopData, const Date& academicYear);
    const list<AvailForExam>& getUnavailListByAcademicYear(string& errorHandling, const Date& academicYear) const;
    list<string> getUnavailForExam();
    Date getMinDateForUnavail() const;
    Date getMaxDateForUnavail() const;
    bool setUnavailability(const list<AvailForExam>& unavailDatesList, const Date& academicYear);
    void appendUnavailability(const Date &startUnavail, const Date &stopUnavail, const Date& academicYear);
    bool appendUnavailability(const AvailForExam& unavailDates, const Date& academicYear);     // all the controls on date's coherency MUST be performed before calling this function (NO control is performed inside)
    void appendUnavailabilityForExam(const Date &startUnavail, const Date &stopUnavail);
    list<AvailForExam> getUnavailabilityForExam() const;
    void setUnavailabilityForExam(const list<AvailForExam>& unavailForExam);
    void clearMapAcademicYearUnavailability(const Date& academicYear);
    void clearUnavailabilityForExam();
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
