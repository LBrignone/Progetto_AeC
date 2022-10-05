//
// Created by Luca Brignone on 24/09/22.
//

#ifndef PROGETTO_FILLDATABASELIST_H
#define PROGETTO_FILLDATABASELIST_H

#include <list>

#include "Course.h"
#include "AssociateProfessor.h"
#include "findSomethingInList.h"
#include "PatternConstrainVerification.h"

using namespace std;

bool fillCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCoursesList, list<Professor>& professorList);

bool insertCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCourseList, list<Professor>& profesorList);

bool fillAssociateProfessor (string& errorHandling, list<AssociateProfessor>& associateProfessorListDb, const list<AssociateProfessor>& associateProfessorListDummy, list<Professor>::iterator professorListEnd);

bool insertAssociateProfessor (string& errorHandling, const list<AssociateProfessor>& associateProfessorListDb, list<AssociateProfessor>& associateProfessorListDummy, list<Professor>::iterator professorListEnd);

#endif //PROGETTO_FILLDATABASELIST_H
