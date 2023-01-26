//
// Created by Luca Brignone on 04/09/22.
//

#ifndef PROGETTO_PATTERNCONSTRAINVERIFICATION_H
#define PROGETTO_PATTERNCONSTRAINVERIFICATION_H

#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

#include "Date.h"
#include "Course.h"
#include "Professor.h"
#include "CourseOfStudy.h"
#include "AssociateProfessor.h"
#include "FindSomethingInList.h"

using namespace std;

bool parallelVersionProgression (string& errorHandling, int prevVersionid, const string& versionToVerify);

string generateVersion (int versionToGenerate);

bool versionCoherencyTest (string& errorHandling, int versionProgression, const string& versionToVerify);

bool examSessionAcademicYearCoherencyTest (string& errorHandling, int academicYearRef, const vector<Date>& sessionToVerify);

bool examSessionBeginEndVerification (string& errorHandling, const vector<Date>& sessionToVerify);

bool examSessionOrderVerification (string& errorHandling, const vector<Date>& sessionToVerify);

bool sessionDurationConstrainVerification (string& errorHandling, const vector<Date>& sessionToVerify);

bool unavailabilityDatesVerification (const AvailForExam& dateToVerify, const list<AvailForExam>& datesToVerifyWith);

bool putCourseInEndedCourses(string& errorHandling, const Course& courseToCompare, list<Course>& courseList, list<CourseOfStudy>& courseToHandle);

bool removeCourseFromEndedCourses(string& errorHandling, const Course& courseToCompare, list<Course>& courseList, list<CourseOfStudy>& courseToHandle);

#endif //PROGETTO_PATTERNCONSTRAINVERIFICATION_H
