//
// Created by Luca Brignone on 14/10/22.
//

#include "SchedulingChecks.h"

int courseIdISInSemester(const string& idToFind, const int& semesterSession, const list<CourseOfStudy>& courseOfStudyList) {
    t_errorCodes coherencyTest = OK;
    bool found = false;
    list<CourseOfStudy>::const_iterator itListCourseOfStudy;

    itListCourseOfStudy = courseOfStudyList.cbegin();
    while (itListCourseOfStudy != courseOfStudyList.cend()) {
        list<string> coursesSemester;
        list<string>::const_iterator itListCoursesSemester;

        // WARNING semesterSession must follow the pair as:
        // semester 1 -> 0, semester 2 -> 1, semester 3 -> 2, ended courses -> -1
        coursesSemester = itListCourseOfStudy->getListOfCoursesBySemester(semesterSession);
        itListCoursesSemester = coursesSemester.cbegin();
        while ((itListCoursesSemester != coursesSemester.cend()) && !found) {
            if (*itListCoursesSemester == idToFind) {
                found = true;
            } else {
                itListCoursesSemester++;
            }
        }
        if (!found) {
            itListCourseOfStudy++;
        }
    }
    return (int) coherencyTest;
}
