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
#include "findSomethingInList.h"
#include "PatternConstrainVerification.h"

using namespace std;

typedef enum {ERR_open_file, ERR_file_format, ERR_hour_set, ERR_string_identifier, ERR_academic_year, ERR_date_field_conversion, ERR_exceeding_session_dates,
              ERR_exceeding_session_number, ERR_inverted_dates, ERR_session_planning, ERR_session_duration, ERR_id_field, ERR_missing_professor,
              ERR_date_overlap, ERR_professor_changed, OK = 255} t_typeErrorDefinitionReadingFile;

int StudentInputFile(string& errorHandling, const string& studentsFileName, list<Student>& studentList, const bool& isDb);

int ProfessorInputFile(string& errorHandling, const string& professorFileName, list<Professor>& professorList, const bool& isDb);

int ClassroomInputFile(string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList, const bool& isDb);

int CourseInputFile(string& errorHandling, const string& courseFileName, list<Course>& courseList, const list<Professor>& professorList, const bool& isDb);

int CourseOFStudyInputFile(string& errorHandling, const string& courseOfStudyFileName, list<CourseOfStudy>& studyCoursesList, const bool& isDb);

int ExamSessionInputFile(string& errorHandling, const string& examSessionStringFileName, map<Date, vector<Date>>& examSessionPerAcademicYear, bool readDatabase);

int ProfessorUnavailability(string& errorHandling, const string& professorUnavailabilityFile, list<Professor>& professorList, const string& academicYear, const bool& isDb);

#endif //PROGETTO_ADDFILEHANDLING_H
