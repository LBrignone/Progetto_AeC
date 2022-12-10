//
// Created by Luca Brignone on 11/11/22.
//

#ifndef PROGETTO_SESSIONSCHEDULER_H
#define PROGETTO_SESSIONSCHEDULER_H

#include <map>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "findSomethingInList.h"
#include "FieldVerificationForScheduling.h"

using namespace std;

typedef struct {
    list<string> _assignedCourseOfStudy;
    string _relateCourse;
    string _version;
    string _classroom;
    bool isEmpty () {
        if (_assignedCourseOfStudy.empty() && _relateCourse.empty() && _version.empty() && _classroom.empty()) {
            return true;
        } else {
            return false;
        }
    }
} examScheduled;

typedef struct {
    Course _course;
    list<string> _assignedCourseOfStudy;
    vector<bool> _constrainDeactivevated = {false, false, false, false, false};
    bool operator <(const CourseOrgBySemester& toCompare) {return (this._course.getPartecipants()) < toCompare._course.getPartecipants();}
} CourseOrgBySemester;

class SessionScheduler {
public:
    SessionScheduler() {};
    SessionScheduler(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor, const list<Classroom>& databaseClassroom);
    ~SessionScheduler() {};
    bool coursesForGivenAcademicYEar(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor);
    int groupingCoursesBySemester(string& errorHandling, const list<CourseOfStudy>& databaseCourseOfStudy);
    int sessionScheduleFromDate(string& errorHandling, const Date& startDate, const Date& stopDate, const int& sessionNumber);
private:
    void groupedCoursesScheduling(const int& sessionNumber, const int& semesterToSchedule,
                                  const Date& startDate, list<Professor>& databaseProfessorList);

    // the map has as key the classroom and keeps for each of them a "calendar" (second parameter of the map)
    vector<pair<Classroom, vector<vector<examScheduled>>>> _datesPlanning;
    // the map has the semester as key for access then a second map as second element, this one keeps as key a list of courses
    // (grouped courses) and a bool that it indicates if the group has been scheduled
    map<int, vector<list<CourseOrgBySemester>>> _groupedCoursesToPlan;
    list<Course> _coursesToSchedule;
};


#endif //PROGETTO_SESSIONSCHEDULER_H
