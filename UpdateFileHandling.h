//
// Created by Luca Brignone on 04/09/22.
//

#ifndef PROGETTO_UPDATEFILEHANDLING_H
#define PROGETTO_UPDATEFILEHANDLING_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>

#include "Student.h"
#include "Classroom.h"
#include "Professor.h"
#include "findSomethingInList.h"

using namespace std;

int StudentToUpdateFile (string& errorHandling, const string& studentsFileName, list<Student>& studentList);

int ProfessorToUpdateFile (string& errorHandling, const string& professorFileName, list<Professor>& professorList);

int ClassroomToUpdateFile (string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList);

#endif //PROGETTO_UPDATEFILEHANDLING_H
