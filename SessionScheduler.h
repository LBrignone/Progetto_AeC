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

typedef struct examScheduled {
    list<string> _assignedCourseOfStudy;
    string _relateCourse;
    string _version;
    string _classroom;
}examScheduled;

typedef struct {
    Course _course;
    string _assignedCourseOfStudy;
    int constrainDeactivevated = 0;
}CourseOrgBySemester;

class SessionScheduler {
public:
    SessionScheduler() {};
    SessionScheduler(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor);
    ~SessionScheduler() {};
    bool coursesForGivenAcademicYEar(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor);
    int groupingCoursesBySemester(string& errorHandling, const list<CourseOfStudy>& databaseCourseOfStudy);
    int sessionScheduleFromDate(string& errorHandling, const Date& startDate, const Date& stopDate, const int& sessionNumber);
private:
    // the map has as key the classroom and keeps for each of them a "calendar" (second parameter of the map)
    map<Classroom, vector<vector<examScheduled>>> _datesPlanning;
    // the map has the semester as key for access then a second map as second element, this one keeps as key a list of courses
    // (grouped courses) and a bool that it indicates if the group has been scheduled
    map<int, vector<pair<list<CourseOrgBySemester>, bool>>> _groupedCoursesToPlan;
    list<Course> _coursesToSchedule;
};


#endif //PROGETTO_SESSIONSCHEDULER_H
