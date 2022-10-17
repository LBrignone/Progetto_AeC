//
// Created by Luca Brignone on 14/10/22.
//

#ifndef PROGETTO_SCHEDULINGCHECKS_H
#define PROGETTO_SCHEDULINGCHECKS_H

#include <list>
#include <string>

#include "Course.h"
#include "CourseOfStudy.h"

int courseIdISInSemester(const string& idToFind, const int& semesterSession, const list<CourseOfStudy>& courseOfStudyList);

#endif //PROGETTO_SCHEDULINGCHECKS_H
