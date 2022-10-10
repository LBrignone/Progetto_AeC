//
// Created by Luca Brignone on 04/10/22.
//

#ifndef PROGETTO_OUTPUTONDATABASEHANDLING_H
#define PROGETTO_OUTPUTONDATABASEHANDLING_H

#include <map>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ErrorHandling.h"
#include "findSomethingInList.h"

using namespace std;

int updateStudentDatabaseFile(string& errorHandling, const string& databaseStudentFileName, const list<Student>& updatedStudentList);

int updateProfessorDatabaseFile(string& errorHandling, const string& databaseProfessorFileName, const list<Professor>& updatedProfessorList);

int updateClassroomDatabaseFile(string& errorHandling, const string& databaseClassroomFileName, const list<Classroom>& updatedClassroomList);

int updateCourseOfStudyDatabaseFile(string& errorHandling, const string& databaseCourseOfStudyFileName, const list<CourseOfStudy>& updatedCourseOfStudyList);

int updateCourseDatabaseFile(string& errorHandling, const string& databaseCourseFileName, const list<Course>& updatedCourseList);

int updateExamSessionDatabaseFile(string& errorHandling, const string& databaseExamSessionFileName, const map<Date, vector<Date>>& updatedExamSessionMap);

int updateUnavailabilityDatabaseFile(string& errorHandling, const string& databaseUnavailabilityFileName, const list<Professor>& updatedProfessorList);

#endif //PROGETTO_OUTPUTONDATABASEHANDLING_H
