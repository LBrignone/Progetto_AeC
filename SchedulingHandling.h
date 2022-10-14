//
// Created by Luca Brignone on 12/10/22.
//

#ifndef PROGETTO_SCHEDULINGHANDLING_H
#define PROGETTO_SCHEDULINGHANDLING_H

#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ErrorHandling.h"
#include "findSomethingInList.h"
#include "OutputOnDatabaseHandling.h"
#include "PatternConstrainVerification.h"

typedef struct examScheduled {
    Classroom assignedClassroom;
    CourseOfStudy assignedCourseOfStudy;
    Course relateCourse;
    string version;
};

int schedulingInitializer(string& errorHandling, const int& sessionNumber, const Date& sessionBegin, const Date& sessionEnd,
                          const list<Professor>& professorList, const list<Classroom>& classroomList, const list<Course>& Course,
                          const list<CourseOfStudy>& courseOfStudyList);

int schedulingPermutationOnDay(string& errorHandling, const int& sessionNumber, const Date& dayToSchedule, const list<Professor>& professorList,
                               const list<Classroom>& classroomList, list<Course>& Course, const list<CourseOfStudy>& courseOfStudyList,
                               pair<Date, pair<Date, vector<examScheduled>>>& examSchedulingPerDay);

int schedulingPermutationOnTimeSlot(const Date& timeSlotBegin, const list<Professor>& professorList, list<Course>& availCourseList,
                                    list<Classroom>& updatedAvailClassroom, const list<CourseOfStudy>& courseOfStudyList,
                                    pair<Date, vector<examScheduled>>& examSchedulingPerSlotHour);

#endif //PROGETTO_SCHEDULINGHANDLING_H
