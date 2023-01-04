//
// Created by Luca Brignone on 11/11/22.
//
#ifndef PROGETTO_FIELDVERIFICATIONFORSCHEDULING_H
#define PROGETTO_FIELDVERIFICATIONFORSCHEDULING_H

#include <list>
#include <string>

#include "Course.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ErrorHandling.h"
#include "SessionScheduler.h"
#include "FindSomethingInList.h"

using namespace std;

bool courseFieldVerification (string& errorHandling, const list<Course>& courseListToVerify, list<Professor>& professorList);

bool professorFieldVerification(string& errorHandling, const Professor& professorToVerify);

bool classroomFieldVerification(string& errorHandling, const list<Classroom>& databaseClassroomToVerify);

list<string> regroupingCoursesForCommonCourse(const list<Course>& courseToSchedule, const Course& idToFind);

int groupedCoursesVerification(string& errorHandling, const list<string>& groupedCourses, const list<Course>& coursesToSchedule,
                               const list<CourseOfStudy>& databaseCourseOfStudy, list<struct courseOrgBySemester>& courseListToSchedule, int& semester);

void myUnique(list<string>& courseList);

#endif //PROGETTO_FIELDVERIFICATIONFORSCHEDULING_H
