//
// Created by Luca Brignone on 04/09/22.
//

#ifndef PROGETTO_UPDATEFILEHANDLING_H
#define PROGETTO_UPDATEFILEHANDLING_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "findSomethingInList.h"
#include "Classroom.h"
#include "Professor.h"
#include "Student.h"

using namespace std;

typedef enum {ERR_open_file, ERR_file_format, OK = 255} t_typeErrorDefinitionReadingUpdateFile;


int StudentToUpdateFile (string& errorHandling, const string& studentsFileName, list<Student>& studentList);

int ProfessorToUpdateFile (string& errorHandling, const string& professorFileName, list<Professor>& professorList);

int ClassroomToUpdateFile (string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList);

#endif //PROGETTO_UPDATEFILEHANDLING_H
