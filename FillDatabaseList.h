//
// Created by Luca Brignone on 24/09/22.
//

#ifndef PROGETTO_FILLDATABASELIST_H
#define PROGETTO_FILLDATABASELIST_H

#include <list>

#include "Course.h"
#include "AssociateProfessor.h"
#include "FindSomethingInList.h"
#include "PatternConstrainVerification.h"

using namespace std;

bool fillCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCoursesList, list<Professor>& professorList);

bool insertCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCourseList, const list<Professor>& profesorList);

bool fillAssociateProfessor (string& errorHandling, list<AssociateProfessor>& associateProfessorListDb, const list<AssociateProfessor>& associateProfessorListDummy, const list<Professor>& professorList);

bool insertAssociateProfessor (string& errorHandling, const list<AssociateProfessor>& associateProfessorListDb, list<AssociateProfessor>& associateProfessorListDummy, const list<Professor>& professorList);

#endif //PROGETTO_FILLDATABASELIST_H
