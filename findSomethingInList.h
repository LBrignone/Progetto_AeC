//
// Created by Luca Brignone on 27/08/22.
//

#ifndef PROGETTO_FINDSOMETHINGINLIST_H
#define PROGETTO_FINDSOMETHINGINLIST_H

#include <list>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Classroom.h"
#include "Professor.h"

list<Student>::const_iterator findStudent(const list<Student>& studentList, const string& idToFind);

list<Professor>::const_iterator findProfessor(const list<Professor>& professorList, const string& idToFind);

list<Classroom>::const_iterator findClassroom(const list<Classroom>& classroomList, const string& idToFind);

list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind);

list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear);

list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear, const string& parallelVersion);

list<Course>::iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const int& startPos);

list<Course>::const_iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const list<Course>::const_iterator& startPos);

Date findMaxAcademicYearUnavail(const list<Professor>& professorList);

bool comp(Professor professorToCompare, Professor minimum);

#endif //PROGETTO_FINDSOMETHINGINLIST_H
