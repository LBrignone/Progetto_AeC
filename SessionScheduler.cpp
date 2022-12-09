//
// Created by Luca Brignone on 11/11/22.
//

#include "SessionScheduler.h"

SessionScheduler::SessionScheduler(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor) {
    string errorLine;
    vector<pair<list<CourseOrgBySemester>, bool>> placeHolder;
    if (this->coursesForGivenAcademicYEar(errorLine, databaseCourses, refAcademicYear, databaseProfessor)) {
        errorHandling = "ERROR: can't construct the class \"SessionScheduler\"\n" + errorLine;
    }
    for (int i = -1; i < 2; i++) {
        _groupedCoursesToPlan[i] = placeHolder;
    }
}

bool SessionScheduler::coursesForGivenAcademicYEar(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor) {
    list<Course>::const_iterator itDatabaseCourse;
    Date tmpAcademicYear(1, 1, refAcademicYear);

    itDatabaseCourse = databaseCourses.cbegin();
    while (itDatabaseCourse != databaseCourses.cend()) {
        if (itDatabaseCourse->getStartYear() == refAcademicYear) {
            _coursesToSchedule.push_back(*itDatabaseCourse);
        }
        itDatabaseCourse++;
    }
    if (_coursesToSchedule.empty()) {
        errorHandling = "ERROR: can't find any course planned for tha academic year " + tmpAcademicYear.getAcademicYear();
    } else {
        if (!courseFieldVerification(errorHandling, _coursesToSchedule, databaseProfessor)) {
            _coursesToSchedule.clear();
        }
    }
    return !_coursesToSchedule.empty();
}

// this method is used to create a map ordered by semester that contains the expanded list of grouped courses (all versions
// for each course of study that makes use of it) and a flag (bool) used for schedule the exam
int SessionScheduler::groupingCoursesBySemester(string& errorHandling, const list<CourseOfStudy>& databaseCourseOfStudy) {
    t_errorCodes errorIdentifier = OK;
    int errorReturn, semesterRef;
    list<string> coursesAlreadyUsed, coursesToExtend;
    list<CourseOrgBySemester> courseExtended;
    list<string>::const_iterator itCoursesAlreadyUsed;
    list<Course>::const_iterator itInternalCourseList;

    itInternalCourseList = _coursesToSchedule.cbegin();
    while ((itInternalCourseList != _coursesToSchedule.cend()) && (errorIdentifier == OK)) {
        itCoursesAlreadyUsed = find(coursesAlreadyUsed.cbegin(), coursesAlreadyUsed.cend(), itInternalCourseList->getId());
        if (itCoursesAlreadyUsed == coursesAlreadyUsed.cend()) {
            coursesToExtend = regroupingCoursesForCommonCourse(_coursesToSchedule, itInternalCourseList->getId());
            coursesAlreadyUsed.insert(coursesAlreadyUsed.cend(), coursesToExtend.cbegin(), coursesToExtend.cend());
            errorReturn = groupedCoursesVerification(errorHandling, coursesToExtend, _coursesToSchedule, databaseCourseOfStudy, courseExtended, semesterRef);
            if (errorReturn == OK) {
                _groupedCoursesToPlan[semesterRef].push_back(make_pair(courseExtended, false));
            } else {
                errorIdentifier = static_cast<t_errorCodes>(errorReturn);
            }
        }
        itInternalCourseList++;
    }
    return errorIdentifier;
}

int sessionScheduleFromDate(string& errorHandling, const string& academicYearToSchedule, const Date& startDate, const Date& stopDate, const int& sessionNumber) {

}
