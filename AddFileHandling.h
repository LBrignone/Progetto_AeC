//
// Created by Luca Brignone on 22/08/22.
//

#ifndef PROGETTO_ADDFILEHANDLING_H
#define PROGETTO_ADDFILEHANDLING_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ErrorHandling.h"
#include "findSomethingInList.h"
#include "PatternConstrainVerification.h"

using namespace std;

int StudentInputFile(string& errorHandling, const string& studentsFileName, list<Student>& studentList, const bool& isDb);

int ProfessorInputFile(string& errorHandling, const string& professorFileName, list<Professor>& professorList, const bool& isDb);

int ClassroomInputFile(string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList, const bool& isDb);

int CourseInputFile(string& errorHandling, const string& courseFileName, list<Course>& courseList, list<Professor>& tmpProfessorList, const bool& isDb);

int CourseOfStudyInputFile(string& errorHandling, const string& courseOfStudyFileName, list<CourseOfStudy>& studyCoursesList, const bool& isDb);

int ExamSessionInputFile(string& errorHandling, const string& examSessionStringFileName, map<Date, vector<Date>>& examSessionPerAcademicYear, bool readDatabase);

int ProfessorUnavailabilityInputFile(string& errorHandling, const string& professorUnavailabilityFile, list<Professor>& professorList, const string& academicYear, const bool& isDb);

#endif //PROGETTO_ADDFILEHANDLING_H
