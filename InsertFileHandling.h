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
#include "CourseOfStudy.h"
#include "FillDatabaseList.h"
#include "FindSomethingInList.h"
#include "PatternConstrainVerification.h"

int CourseToInsertFile(string& errorHandling, const string& courseFileName, list<Course>& databaseCourseList, list<Professor>& professorList, list<CourseOfStudy>& courseOfStudy);

#endif //PROGETTO_INSERTFILEHANDLING_H
