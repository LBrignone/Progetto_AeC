//
// Created by Luca Brignone on 11/11/22.
//

#include "SessionScheduler.h"

SessionScheduler::SessionScheduler(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor, const list<Classroom>& databaseClassroom) {
    string errorLine;
    vector<list<CourseOrgBySemester>> placeHolderForCourses;
    vector<vector<examScheduled>> placeHolderForCalendar;
    list<Classroom> copyOfClassroomList = databaseClassroom;
    list<Classroom>::const_iterator itClassroomList;

    if (this->coursesForGivenAcademicYEar(errorLine, databaseCourses, refAcademicYear, databaseProfessor)) {
        errorHandling = "ERROR: can't construct the class \"SessionScheduler\"\n" + errorLine;
    }
    for (int i = -1; i < 2; i++) {
        _groupedCoursesToPlan[i] = placeHolderForCourses;
    }

    copyOfClassroomList.sort(sortMethodForClassroom);
    for (itClassroomList = copyOfClassroomList.cbegin(); itClassroomList != copyOfClassroomList.cend(); itClassroomList++) {
        _datesPlanning.emplace_back(*itClassroomList, placeHolderForCalendar);
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
                courseExtended.sort(sortMethodForCourse());
                _groupedCoursesToPlan[semesterRef].push_back(courseExtended);
            } else {
                errorIdentifier = static_cast<t_errorCodes>(errorReturn);
            }
        }
        itInternalCourseList++;
    }
    return errorIdentifier;
}

int SessionScheduler::sessionScheduleFromDate(string& errorHandling, const Date& startDate, const Date& stopDate, const int& sessionNumber) {
    t_errorCodes errorIdentifier;
    bool errorInScheduling = false;
    int sessionDuration;
    vector<examScheduled> dummyElementForInit(5);
    vector<pair<Classroom, vector<vector<examScheduled>>>>::iterator itDatesPlanning;

    sessionDuration = stopDate - startDate + 1 - ((stopDate - startDate + 1) / 7);
    if (sessionDuration < 13) {
        errorHandling = "ERRROR:  ";
        errorIdentifier = ERR_exam_scheduling;
    }
    for (itDatesPlanning = _datesPlanning.begin(); itDatesPlanning != _datesPlanning.end(); itDatesPlanning++) {
        itDatesPlanning->second.insert(itDatesPlanning->second.end(), sessionDuration, dummyElementForInit);
    }
}

void SessionScheduler::groupedCoursesScheduling(const int& sessionNumber, const int& semesterToSchedule, const Date& startDate, list<Professor>& databaseProfessorList) {
    bool firstAppeal = false, secondAppeal = false;
    int day = 0, slot = 0;
    list<Professor> copyDatabaseProfessorList;
    map<int, vector<list<CourseOrgBySemester>>> copyOfGroupedCoursesToPlan;
    vector<pair<Classroom, vector<vector<examScheduled>>>> copyOfDatesPlanning;
    vector<list<CourseOrgBySemester>>::iterator itGroupedCourseToPlanVector;

    copyDatabaseProfessorList = databaseProfessorList;
    copyOfDatesPlanning = _datesPlanning;
    copyOfGroupedCoursesToPlan = _groupedCoursesToPlan;
    if (sessionNumber == semesterToSchedule) {
        firstAppeal = true;
        secondAppeal = true;
    } else {
        secondAppeal = true;
    }

    while (firstAppeal || secondAppeal) {
        if (secondAppeal) {
            day = 13;
        }
        if (firstAppeal) {
            day = 0;
        }
        for (itGroupedCourseToPlanVector = copyOfGroupedCoursesToPlan[semesterToSchedule].begin(); itGroupedCourseToPlanVector != copyOfGroupedCoursesToPlan[semesterToSchedule].end(); itGroupedCourseToPlanVector++) {
            bool endSchedulingGroup = false, errorInScheduling = false, forcedExit = false;
            int relaxedConstrain = 0, coursesPositioned = 0, coursesPositionedMax = 0, dayMax = 0, slotMax = 0;
            Classroom freeClassroomToUse;
            list<CourseOrgBySemester>::iterator itGroupedCoursesToPlanList;

            itGroupedCoursesToPlanList = itGroupedCourseToPlanVector->begin();
            while (!endSchedulingGroup) {
                itGroupedCoursesToPlanList->_constrainDeactivevated[0] = false;
                errorInScheduling = false;
                if (!constrain_1(copyOfDatesPlanning)) {
                    if (relaxedConstrain >= 1) {
                        itGroupedCoursesToPlanList->_constrainDeactivevated[1] = true;
                    } else {
                        errorInScheduling = true;
                    }
                }
                if (!constrain_2(copyOfDatesPlanning)) {
                    if (relaxedConstrain >= 1) {
                        itGroupedCoursesToPlanList->_constrainDeactivevated[2] = true;
                    } else {
                        errorInScheduling = true;
                    }
                }
                if (!constrain_3(copyDatabaseProfessorList, startDate, day)) {
                    if (relaxedConstrain >= 1) {
                        itGroupedCoursesToPlanList->_constrainDeactivevated[3] = true;
                    } else {
                        errorInScheduling = true;
                    }
                }
                if (!constrain_4(freeClassroomToUse)) {
                    itGroupedCoursesToPlanList->_constrainDeactivevated[0] = true;
                    if (relaxedConstrain >= 1) {
                        itGroupedCoursesToPlanList->_constrainDeactivevated[4] = true;
                    } else {
                        errorInScheduling = true;
                    }
                }
                if (relaxedConstrain != 4) {
                    if (errorInScheduling) {
                        copyOfGroupedCoursesToPlan = _groupedCoursesToPlan;
                        copyOfDatesPlanning = _datesPlanning;
                        copyDatabaseProfessorList = databaseProfessorList;
                        slot++;
                        if (slot == (copyOfDatesPlanning.front().second[day].size() - 1)) {
                            slot = 0;
                            day++;
                            if (day == (copyOfDatesPlanning.front().second.size() - 1)) {
                                day = 0;
                                relaxedConstrain++;
                            }
                        }
                        itGroupedCoursesToPlanList = itGroupedCourseToPlanVector->begin();
                    } else {
                        coursePositioning(itGroupedCoursesToPlanList, copyOfDatesPlanning, day, slot, freeClassroomToUse);
                        itGroupedCoursesToPlanList++;
                        if (itGroupedCoursesToPlanList == itGroupedCourseToPlanVector->end()) {
                            endSchedulingGroup = true;
                        }
                    }
                } else {
                    if (!itGroupedCoursesToPlanList->_constrainDeactivevated[0]) {
                        coursePositioning(itGroupedCoursesToPlanList, copyOfDatesPlanning, day, slot, freeClassroomToUse);
                        coursesPositioned++;
                    }
                    itGroupedCoursesToPlanList++;
                    if (itGroupedCoursesToPlanList == itGroupedCourseToPlanVector->end()) {
                        if (!forcedExit) {
                            if (coursesPositioned > coursesPositionedMax) {
                                coursesPositionedMax = coursesPositioned;
                                dayMax = day;
                                slotMax = slot;
                            }
                            copyOfGroupedCoursesToPlan = _groupedCoursesToPlan;
                            copyOfDatesPlanning = _datesPlanning;
                            copyDatabaseProfessorList = databaseProfessorList;
                            slot++;
                            if (slot == (copyOfDatesPlanning.front().second[day].size() - 1)) {
                                slot = 0;
                                day++;
                                if (day == (copyOfDatesPlanning.front().second.size() - 1)) {
                                    day = dayMax;
                                    slot = slotMax;
                                    forcedExit = true;
                                }
                            }
                        } else {
                            endSchedulingGroup = true;
                        }
                    }
                }
            }
            _groupedCoursesToPlan = copyOfGroupedCoursesToPlan;
            _datesPlanning = copyOfDatesPlanning;
            databaseProfessorList = copyDatabaseProfessorList;
        }
        if (firstAppeal) {
            firstAppeal = false;
        } else {
            secondAppeal = false;
        }
    }
}
