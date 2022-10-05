//
// Created by Luca Brignone on 04/10/22.
//

#ifndef PROGETTO_OUTPUTONDATABASEHANDLING_H
#define PROGETTO_OUTPUTONDATABASEHANDLING_H

#include <map>
#include <list>
#include <fstream>
#include <iostream>

#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ErrorEnumerator.h"

using namespace std;



int updateStudentDatabase(string& errorHandling, string& databaseFileName, const list<Student>& updatedStudentList);

#endif //PROGETTO_OUTPUTONDATABASEHANDLING_H
