//
// Created by Luca Brignone on 11/11/22.
//

#include "SessionScheduler.h"

SessionScheduler::SessionScheduler(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor, const list<Classroom>& databaseClassroom) {
    string errorLine;
    vector<vector<CourseOrgBySemester>> placeHolderForCourses;
    vector<vector<examScheduled>> placeHolderForCalendar;
    list<Classroom> copyOfClassroomList = databaseClassroom;
    list<Classroom>::const_iterator itClassroomList;

    if (this->coursesForGivenAcademicYear(errorLine, databaseCourses, refAcademicYear, databaseProfessor)) {
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

bool SessionScheduler::coursesForGivenAcademicYear(string& errorHandling, const list<Course>& databaseCourses, const int& refAcademicYear, list<Professor>& databaseProfessor) {
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
    vector<CourseOrgBySemester> courseExtendedVector;
    list<string>::const_iterator itCoursesAlreadyUsed;
    list<CourseOrgBySemester>::const_iterator itCourseExtended;
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
                for (itCourseExtended = courseExtended.cbegin(); itCourseExtended !=  courseExtended.cend(); itCourseExtended++) {
                    courseExtendedVector.push_back(*itCourseExtended);
                }
                _groupedCoursesToPlan[semesterRef].push_back(courseExtendedVector);
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

void SessionScheduler::groupedCoursesScheduling(const int& sessionNumber, const int& semesterToSchedule, const Date& startDate, list<Professor>& databaseProfessorList, const int& academicYearRef) {
    bool firstAppeal = false, secondAppeal = false;
    int day = 0, slot = 0;
    list<Professor> copyDatabaseProfessorList;
    map<int, vector<vector<CourseOrgBySemester>>> copyOfGroupedCoursesToPlan;
    vector<pair<Classroom, vector<vector<examScheduled>>>> copyOfDatesPlanning;
    vector<vector<CourseOrgBySemester>>::iterator itGroupedCourseToPlanVector;

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
        int groupNumber = 0, courseNumber = 0;

        if (secondAppeal) {
            day = 13;
        }
        if (firstAppeal) {
            day = 0;
        }
        for (itGroupedCourseToPlanVector = copyOfGroupedCoursesToPlan[semesterToSchedule].begin(); itGroupedCourseToPlanVector != copyOfGroupedCoursesToPlan[semesterToSchedule].end(); itGroupedCourseToPlanVector++) {
            bool endSchedulingGroup = false, errorInScheduling = false, forcedExit = false;
            int relaxedConstrain = 0, coursesPositioned = 0, coursesPositionedMax = 0, dayMax = 0, slotMax = 0;
            int freeClassroomToUse;
            vector<CourseOrgBySemester>::iterator itGroupedCoursesToPlanList;

            groupNumber++;
            itGroupedCoursesToPlanList = itGroupedCourseToPlanVector->begin();
            while (!endSchedulingGroup) {
                courseNumber++;
                itGroupedCoursesToPlanList->_constrainDeactivevated[0] = false;
                errorInScheduling = false;
                if (!constrain_1(copyOfDatesPlanning, day, copyOfGroupedCoursesToPlan, semesterToSchedule, groupNumber, courseNumber)) {
                    if (relaxedConstrain < 1) {
                        errorInScheduling = true;
                    }
                }
                if (!constrain_2(copyOfDatesPlanning, day, slot, relaxedConstrain, copyOfGroupedCoursesToPlan,
                                 semesterToSchedule, groupNumber, courseNumber)) {
                        errorInScheduling = true;
                }
                if (!constrain_3(copyOfDatesPlanning, academicYearRef, startDate, day, slot,
                                 itGroupedCoursesToPlanList->_course, copyDatabaseProfessorList)) {
                    if (relaxedConstrain >= 3) {
                        itGroupedCoursesToPlanList->_constrainDeactivevated[3] = true;
                    } else {
                        errorInScheduling = true;
                    }
                }
                if (!constrain_4(copyOfDatesPlanning, itGroupedCoursesToPlanList->_course, day,
                                 slot, freeClassroomToUse)) {
                    itGroupedCoursesToPlanList->_constrainDeactivevated[0] = true;
                    if (relaxedConstrain >= 4) {
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
                        coursePositioning(copyOfDatesPlanning, itGroupedCoursesToPlanList->_course, freeClassroomToUse, day, slot);
                        itGroupedCoursesToPlanList++;
                        if (itGroupedCoursesToPlanList == itGroupedCourseToPlanVector->end()) {
                            endSchedulingGroup = true;
                        }
                    }
                } else {
                    if (!itGroupedCoursesToPlanList->_constrainDeactivevated[0]) {
                        coursePositioning(copyOfDatesPlanning, itGroupedCoursesToPlanList->_course, freeClassroomToUse, day, slot);
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

// this private method handles the controls of constrain 1, regarding the two days distance between courses having tha same
// course of study, it returns TRUE if the constrain is not respected, while returns False in the opposite case
bool SessionScheduler::constrain_1(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning, const int& dayRef,
                                   map<int, vector<vector<CourseOrgBySemester>>>& copyCoursesForConstrainViolation,
                                   const int& semesterRef, const int& groupRef, const int& courseRef) {
    bool constrain1Violated = false;
    int position = 0, positionMax = 0, slot = 0, classroom = 0;
    list<string>::const_iterator itCourseOfStudyFromFind;
    list<pair<string, bool>>::iterator itIdCourseOfStudyToFind;

    position = dayRef - CONSTRAIN_1_DISTANCE;
    positionMax = dayRef + CONSTRAIN_1_DISTANCE + 1;
    if (position < 0) {
        position = 0;
    }
    if (positionMax > copyOfDatesPlanning[classroom].second.size() - 1) {
        positionMax = (int) copyOfDatesPlanning[classroom].second.size() - 1;
    }
    while (position < positionMax) {
        while (slot < MAX_SLOT_PER_DAY) {
            while (classroom < copyOfDatesPlanning.size()) {
                itIdCourseOfStudyToFind = copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._assignedCourseOfStudy.begin();
                while (itIdCourseOfStudyToFind != copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._assignedCourseOfStudy.end()) {
                    itCourseOfStudyFromFind = find(copyOfDatesPlanning[classroom].second[position][slot]._assignedCourseOfStudy.begin(), copyOfDatesPlanning[classroom].second[position][slot]._assignedCourseOfStudy.end(),
                                                   itIdCourseOfStudyToFind->first);
                    if (itCourseOfStudyFromFind != copyOfDatesPlanning[classroom].second[position][slot]._assignedCourseOfStudy.end()) {
                        if (copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._course.getId() != copyOfDatesPlanning[classroom].second[position][slot]._relateCourse) {
                            constrain1Violated = true;
                            itIdCourseOfStudyToFind->second = true;
                            copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._constrainDeactivevated[1] = true;

                            int semesterCourse = -1, groupCourse = 0, courseForCourseOfStudy = 0;

                            string idCourseError = copyOfDatesPlanning[classroom].second[position][slot]._relateCourse;
                            while (semesterCourse < 2) {
                                while (groupCourse < copyCoursesForConstrainViolation[semesterCourse].size()) {
                                    while (courseForCourseOfStudy < copyCoursesForConstrainViolation[semesterCourse][groupCourse].size()) {
                                        if (copyCoursesForConstrainViolation[semesterCourse][groupCourse][courseForCourseOfStudy]._course.getId() == idCourseError) {
                                            copyCoursesForConstrainViolation[semesterCourse][groupCourse][courseForCourseOfStudy].setCourseOfStudyError(*itCourseOfStudyFromFind);
                                        }
                                        courseForCourseOfStudy++;
                                    }
                                    courseForCourseOfStudy = 0;
                                    groupCourse++;
                                }
                                groupCourse = 0;
                                semesterCourse++;
                            }
                        }
                    } else {
                        itIdCourseOfStudyToFind++;
                    }
                }
                classroom++;
            }
            classroom = 0;
            slot++;
        }
        slot = 0;
        position++;
    }
    return constrain1Violated;
}

// this private method returns TRUE if the rule 2 is not respected, and FALSE for the opposite outcome
bool SessionScheduler::constrain_2(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                                   const int& dayRef, const int& slotRef, const int& constrainRelaxed,
                                   map<int, vector<vector<CourseOrgBySemester>>>& copyCoursesForConstrainViolation,
                                   const int& semesterRef, const int& groupRef, const int& courseRef) {
    bool constrain2Error = false, constrain2Violated = false;
    int position = 0, positionMax = 0, slot = 0, classroom = 0;

    position = dayRef - CONSTRAIN_2_DISTANCE;
    positionMax = dayRef + CONSTRAIN_2_DISTANCE + 1;
    if (position < 0) {
        position  = 0;
    }
    if (positionMax > copyOfDatesPlanning.front().second.size()) {
        positionMax = (int) copyOfDatesPlanning.front().second.size();
    }

    while (position < positionMax) {
        while (slot < MAX_SLOT_PER_DAY) {
            while (classroom < copyOfDatesPlanning.size()) {
                if ((copyOfDatesPlanning[classroom].second[position][slot]._relateCourse == copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._course.getId())
                    && (copyOfDatesPlanning[classroom].second[position][slot]._version == copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._course.getParallelCoursesId())) {
                    copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._constrainDeactivevated[2] = true;
                    constrain2Violated = true;
                    if (position == dayRef) {
                        if ((slot >= (slotRef - CONSTRAIN_2_DISTANCE_RELAXED)) && (slot <= (slotRef + CONSTRAIN_2_DISTANCE_RELAXED))) {
                            constrain2Error = true;
                            classroom = (int) copyOfDatesPlanning.size() + 1;
                        }
                    }
                } else {
                    classroom++;
                }
            }
            if (classroom != (int) copyOfDatesPlanning.size() + 1) {
                classroom = 0;
                slot++;
            } else {
                slot = 6;
            }
        }
        if (slot != 6) {
            slot = 0;
            position++;
        } else {
            position = positionMax;
        }
    }
    if (constrainRelaxed < 2) {
        return constrain2Violated;
    } else {
        return constrain2Error;
    }
}

// this private method verify the unavailability of professors related to given course, and if all of them are available
// proceed with the placement of the exam date in their unavailability dates
// the return is TRUE if all professor are available and the placement has resulted in a good ending, while is FALSE in the
// opposite circumstances
bool SessionScheduler::constrain_3(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                                   const int& academicYearRef, const Date& startSessionDate, const int& dateIncrement,
                                   const int& slotRef, const Course& courseToInsert, list<Professor>& professorListToVerifyAndUpdate) {
    bool professorUnavailable = false;
    int hourSlot = 8 + ((slotRef - 1) * 2), examDuration = 0;
    Date unavailabilityToAssignStart, unavailabilityToAssignStop;
    list<AssociateProfessor>::const_iterator itCourseToInsert;
    list<Professor>::const_iterator itProfessorListToVerifyAndUpdateConst;
    list<Professor>::iterator itProfessorListToVerifyAndUpdate;

    unavailabilityToAssignStart = startSessionDate + dateIncrement;
    unavailabilityToAssignStart.setHour(hourSlot);
    examDuration = courseToInsert.getEntranceTime() + courseToInsert.getExamDuration() + courseToInsert.getExitTime();
    unavailabilityToAssignStop = unavailabilityToAssignStart;
    unavailabilityToAssignStop.setHour(hourSlot + examDuration);
    itCourseToInsert = courseToInsert.getListAssistant().cbegin();
    while (itCourseToInsert != courseToInsert.getListAssistant().cend()) {
        itProfessorListToVerifyAndUpdateConst = findProfessor(professorListToVerifyAndUpdate, itCourseToInsert->getProfessorPointer()->getId());
        itProfessorListToVerifyAndUpdate = constItToNonConstIt(professorListToVerifyAndUpdate, itProfessorListToVerifyAndUpdateConst);
        if (!itProfessorListToVerifyAndUpdate->isAvailExamProgramming(unavailabilityToAssignStart, academicYearRef)) {
            itCourseToInsert = courseToInsert.getListAssistant().cend();
            professorUnavailable = true;
        }
    }
    if (!professorUnavailable) {
        itProfessorListToVerifyAndUpdateConst = findProfessor(professorListToVerifyAndUpdate, itCourseToInsert->getProfessorPointer()->getId());
        itProfessorListToVerifyAndUpdate = constItToNonConstIt(professorListToVerifyAndUpdate, itProfessorListToVerifyAndUpdateConst);
        itProfessorListToVerifyAndUpdate->appendUnavailabilityForExam(unavailabilityToAssignStart, unavailabilityToAssignStop);
    }
    return !professorUnavailable;
}

bool SessionScheduler::constrain_4(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                                   const Course& courseToInsert, const int& dayRef, const int& slotRef, int& classroomChosen) {
    bool coursePositioned = false;
    int classroom = -2, slot = slotRef, slotOccupancy = 0, slotOccupancyMax = ceil((courseToInsert.getEntranceTime() + courseToInsert.getExamDuration() + courseToInsert.getExitTime()) / 2);

    while (classroom < copyOfDatesPlanning.size()) {
        if (courseToInsert.getPartecipants() <= copyOfDatesPlanning[classroom].first.getCapacity()){
            while (slot < copyOfDatesPlanning[classroom].second[dayRef].size()) {
                if (copyOfDatesPlanning[classroom].second[dayRef][slot].isEmpty()) {
                    slotOccupancy++;
                } else {
                    slotOccupancy = 0;
                }
                if (slotOccupancy == slotOccupancyMax) {
                    slot = (int) copyOfDatesPlanning[classroom].second[dayRef].size();
                    coursePositioned = true;
                } else {
                    if (slot == 4) {
                        slot = 0;
                        slotOccupancy = 0;
                    } else {
                        slot++;
                    }
                }
            }
        }
        classroom++;
    }
    classroomChosen = classroom;
    return coursePositioned;
}

bool SessionScheduler::coursePositioning(vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                                         const Course& courseToInsert, const int& classroomChosen, const int& dayRef, const int& slotRef) {
    copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef]._relateCourse = courseToInsert.getId();
    copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef]._version = courseToInsert.getParallelCoursesId();
    copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef]._assignedCourseOfStudy = courseToInsert.getListGroupedId();
    copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef]._classroom = copyOfDatesPlanning[classroomChosen].first.getId();
}

void outputSessionFile(const string fileBaseName, const int& sessionNumber) {
    string fileCompleteName = fileBaseName + "_" + to_string(sessionNumber) + ".txt";
    fstream fileSessionName;

    fileSessionName.open(fileCompleteName, fstream::out);
}
