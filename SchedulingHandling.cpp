//
// Created by Luca Brignone on 12/10/22.
//

#include "SchedulingHandling.h"

int schedulingInitializer(string& errorHandling, const int& sessionNumber, const Date& sessionBegin, const Date& sessionEnd,
                          const list<Professor>& professorList, const list<Classroom>& classroomList, const list<Course>& courseList,
                          const list<CourseOfStudy>& courseOfStudyList) {
    string errorLine;
    Date copyOfSessionBegin(sessionBegin);
    list<Course> copyOfCourseList(courseList);
    map<Date, pair<Date, vector<examScheduled>>> sessionSchedule;
    pair<Date, pair<Date, vector<examScheduled>>> toInsertInSchedule;

    while(copyOfSessionBegin != sessionEnd) {
        schedulingPermutation(errorLine, sessionNumber, copyOfSessionBegin, professorList, classroomList, copyOfCourseList, courseOfStudyList, toInsertInSchedule);
        copyOfSessionBegin++;
    }
}

int schedulingPermutationOnDay(string& errorHandling, const int& sessionNumber, const Date& dayToSchedule, const list<Professor>& professorList,
                               const list<Classroom>& classroomList, list<Course>& Course, const list<CourseOfStudy>& courseOfStudyList,
                               pair<Date, pair<Date, vector<examScheduled>>>& examSchedulingPerDay) {
    // start here
}