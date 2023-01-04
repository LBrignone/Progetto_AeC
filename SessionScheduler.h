//
// Created by Luca Brignone on 11/11/22.
//

#ifndef PROGETTO_SESSIONSCHEDULER_H
#define PROGETTO_SESSIONSCHEDULER_H

#include <map>
#include <list>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ConstConversion.hpp"
#include "FindSomethingInList.h"
#include "FieldVerificationForScheduling.h"

#define CONSTRAIN_1_DISTANCE 2
#define CONSTRAIN_2_DISTANCE 14
#define CONSTRAIN_2_DISTANCE_RELAXED 3
#define MAX_SLOT_PER_DAY 5

using namespace std;

struct examScheduled{
    list<string> _assignedCourseOfStudy;
    string _relateCourse;
    string _version;
    string _classroom;

    const bool isEmpty () const {
        if (_assignedCourseOfStudy.empty() && _relateCourse.empty() && _version.empty() && _classroom.empty()) {
            return true;
        } else {
            return false;
        }
    }
};

struct courseOrgBySemester{
    Course _course;
    list<pair<string, bool>> _assignedCourseOfStudy;
    vector<bool> _constrainDeactivated = {false, false, false, false, false};

    void setCourseOfStudyError(const string& courseOfStudyToSet) {
        list<pair<string, bool>>::iterator it_assignedCourseOfStudy;
        it_assignedCourseOfStudy = find(_assignedCourseOfStudy.begin(), _assignedCourseOfStudy.end(), make_pair(courseOfStudyToSet, false));
        it_assignedCourseOfStudy->second = true;
    }
    bool operator <(const courseOrgBySemester& toCompare) {return (this->_course.getPartecipants()) < toCompare._course.getPartecipants();}
};

struct expandedScheduleForPrint{
    string _assignedCourseOfStudy;
    string _relateCourse;
    string _version;
    string _classroom;
    vector<bool> _constrainDeactivated = {false, false, false, false};
    bool operator ==(const expandedScheduleForPrint& toCompare) {
        return ((this->_assignedCourseOfStudy == toCompare._assignedCourseOfStudy) && (this->_relateCourse == toCompare._relateCourse) && (this->_version == toCompare._version) && (this->_classroom == toCompare._classroom));
    }
    ostream& operator <<(ostream& os) const {
        os << _relateCourse << "[" << _version << "]" << "(" << _assignedCourseOfStudy << ")|" << _classroom << ";";
        return os;
    }
};

class SessionScheduler {
public:
    SessionScheduler() {};
    SessionScheduler(string& errorHandling, const int& refAcademicYear,
                     const list<Course>& databaseCourses, list<Professor>& databaseProfessor,
                     const list<Classroom>& databaseClassroom,
                     const list<CourseOfStudy>& databaseCourseOfStudy, const Date& startRef,
                     const Date& stopRef, const int& sessionNumber);
    ~SessionScheduler() {};
    void groupedCoursesScheduling(const int& sessionNumber, const int& semesterToSchedule,
                                  const Date& startDate, list<Professor>& databaseProfessorList,
                                  const int& academicYearRef);
    void outputSessionFile(const string& fileBaseName, const int& sessionNumber, const Date& sessionDateStartRef);
    void outputWarningFile(const string& fileBaseName, const int& sessionNumber);
private:
    bool coursesForGivenAcademicYear(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear,
                                     list<Professor>& databaseProfessor);
    int groupingCoursesBySemester(string& errorHandling, const list<CourseOfStudy>& databaseCourseOfStudy);
    bool sessionScheduleFromDate(string& errorHandling, const Date& startDate, const Date& stopDate, const int& sessionNumber);
    bool constrain_1(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                     const int& dayRef,
                     map<int, vector<vector<courseOrgBySemester>>>& copyCoursesForConstrainViolation,
                     const int& semesterRef, const int& groupRef, const int& courseRef);
    bool constrain_2(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                     const int& dayRef, const int& slotRef, const int& constrainRelaxed,
                     map<int, vector<vector<courseOrgBySemester>>>& copyCoursesForConstrainViolation,
                     const int& semesterRef, const int& groupRef, const int& courseRef);
    bool constrain_3(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                     const int& academicYearRef, const Date& startSessionDate, const int& dateIncrement, const int& slotRef,
                     const Course& courseToInsert, list<Professor>& professorListToVerifyAndUpdate);
    bool constrain_4(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                     const Course& courseToInsert, const int& dayRef, const int& slotRef, int& classroomChosen);
    void coursePositioning(vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                           const Course& courseToInsert, const int& classroomChosen, const int& dayRef, const int& slotRef);

    // the map has as key the classroom and keeps for each of them a "calendar" (second parameter of the map)
    vector<pair<Classroom, vector<vector<examScheduled>>>> _datesPlanning;
    // the map has the semester as key for access then a second map as second element, this one keeps as key a list of courses
    // (grouped courses) and a bool that it indicates if the group has been scheduled
    map<int, vector<vector<courseOrgBySemester>>> _groupedCoursesToPlan;
    list<Course> _coursesToSchedule;
};


#endif //PROGETTO_SESSIONSCHEDULER_H
