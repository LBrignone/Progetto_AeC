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

list<Student>::iterator findStudent(const list<Student>& studentList, const string& idToFind);

list<Professor>::iterator findProfessor(const list<Professor>& professorList, const string& idToFind);

list<Classroom>::iterator findClassroom(const list<Classroom>& classroomList, const string& idToFind);

list<Course>::iterator findCourse(list<Course>& courseList, const string& idToFind);

list<Course>::iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear);

list<Course>::iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear, const string& parallelVersion);

list<Course>::iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const int& startPos);

list<Course>::iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const list<Course>::iterator& startPos);

bool findFirstYearProfessorUnavailability(const list<Professor>::const_iterator& professorToCompare, const list<Professor>::const_iterator& minimum);
#endif //PROGETTO_FINDSOMETHINGINLIST_H
