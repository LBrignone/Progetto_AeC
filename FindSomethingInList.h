//
// Created by Luca Brignone on 27/08/22.
//

#ifndef PROGETTO_FINDSOMETHINGINLIST_H
#define PROGETTO_FINDSOMETHINGINLIST_H

#include <list>
#include <string>
#include <iostream>
#include <algorithm>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Classroom.h"
#include "Professor.h"
#include "CourseOfStudy.h"
#include "SessionScheduler.h"

list<Student>::const_iterator findStudent(const list<Student>& studentList, const string& idToFind);

list<Professor>::const_iterator findProfessor(const list<Professor>& professorList, const string& idToFind);

list<Classroom>::const_iterator findClassroom(const list<Classroom>& classroomList, const string& idToFind);

list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind);

list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear);

list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear, const string& parallelVersion);

list<Course>::iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const int& startPos);

list<Course>::const_iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const list<Course>::const_iterator& startPos);

list<Course>::const_iterator findCourseLastForIdAndYear(const list<Course>& courseList, const string& idToFind, const int& academicYear, const list<Course>::const_iterator& startPos);

bool findCourseTitle(const list<Course>& courseList, const string& titleToFind);

list<string> findCourseOfStudy(string& errorHandling, const list<CourseOfStudy>& courseOfStudyList, const string& idToFind);

list<string> findCourseIdGrouped(const list<Course>& courseList, const string& idToFind);

Date findMaxAcademicYearUnavail(const list<Professor>& professorList);

bool findDistanceSameCourseOfStudy(const vector<pair<Classroom, vector<vector<struct examScheduled>>>>& planningToSearchIn, const list<string>& courseOfStudyToFind, const int& dayRefPosition);

bool comp(Professor professorToCompare, Professor minimum);

bool sortMethodForProf(Professor professorToCompare, Professor minimum);

bool sortMethodForClassroom(Classroom classroomToCompare, Classroom minimum);

bool sortMethodForCourse(struct courseOrgBySemester courseToCompare, struct courseOrgBySemester minimum);

bool sortMethodForPrintSchedule(const struct expandedScheduleForPrint& structToCompare, const struct expandedScheduleForPrint& minimum);

bool sortMethodForPrintWarnings(const struct expandedScheduleForPrint& structToCompare, const struct expandedScheduleForPrint& minimum);

int approXimationFunct(const int& rightVal, const int& leftVal);

#endif //PROGETTO_FINDSOMETHINGINLIST_H
