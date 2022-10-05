//
// Created by Luca Brignone on 06/09/22.
//

#ifndef PROGETTO_INSERTFILEHANDLING_H
#define PROGETTO_INSERTFILEHANDLING_H

#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Course.h"
#include "Professor.h"
#include "FillDatabaseList.h"
#include "findSomethingInList.h"
#include "PatternConstrainVerification.h"

typedef enum {ERR_open_file, ERR_missing_field, ERR_file_format, ERR_parallel_course_number_inherit, ERR_not_found, OK = 255} t_typeErrorDefinitionReadingUpdateFile;

int CourseToInsertFile(string& errorHandling, const string& courseFileName, list<Course>& databaseList, list<Professor>& professorList);

#endif //PROGETTO_INSERTFILEHANDLING_H
