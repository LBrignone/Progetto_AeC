//
// Created by Luca Brignone on 11/11/22.
//

#include "SessionScheduler.h"

SessionScheduler::SessionScheduler(string& errorHandling, const int& refAcademicYear,
                                   const list<Course>& databaseCourses, list<Professor>& databaseProfessor,
                                   const list<Classroom>& databaseClassroom,
                                   const list<CourseOfStudy>& databaseCourseOfStudy, const Date& startRef,
                                   const Date& stopRef, const int& sessionNumber) {
    string errorLine;
    vector<vector<courseOrgBySemester>> placeHolderForCourses;
    vector<vector<examScheduled>> placeHolderForCalendar;
    list<Classroom> copyOfClassroomList = databaseClassroom;
    list<Classroom>::const_iterator itClassroomList;

    if (this->coursesForGivenAcademicYear(errorLine, databaseCourses, refAcademicYear, databaseProfessor)) {
        errorHandling = "ERROR: can't construct object \"SessionScheduler\"\n" + errorLine;
    } else {
        for (int i = -1; i < 2; i++) {
            _groupedCoursesToPlan[i] = placeHolderForCourses;
        }
        if (this->groupingCoursesBySemester(errorLine, databaseCourseOfStudy) == OK) {
            if (!classroomFieldVerification(errorLine, databaseClassroom)) {
                errorHandling = "ERROR: can't construct object \"SessionScheduler\"\n" + errorLine;
            } else {
                copyOfClassroomList.sort(sortMethodForClassroom);
                for (itClassroomList = copyOfClassroomList.cbegin();
                itClassroomList != copyOfClassroomList.cend(); itClassroomList++) {
                    _datesPlanning.emplace_back(*itClassroomList, placeHolderForCalendar);
                }
                if (!this->sessionScheduleFromDate(errorLine, startRef, stopRef, sessionNumber)) {
                    errorHandling = "ERROR: can't construct object \"SessionScheduler\"\n" + errorLine;
                }
            }
        } else {
            errorHandling = "ERROR: can't construct object \"SessionScheduler\"\n" + errorLine;
        }
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
    return _coursesToSchedule.empty();
}

// this method is used to create a map ordered by semester that contains the expanded list of grouped courses (all versions
// for each course of study that makes use of it) and a flag (bool) used for schedule the exam
int SessionScheduler::groupingCoursesBySemester(string& errorHandling, const list<CourseOfStudy>& databaseCourseOfStudy) {
    t_errorCodes errorIdentifier = OK;
    int errorReturn, semesterRef = -2;
    list<string> coursesAlreadyUsed, coursesToExtend;
    list<string>::const_iterator itCoursesAlreadyUsed;
    list<courseOrgBySemester>::const_iterator itCourseExtended;
    list<Course>::const_iterator itInternalCourseList;

    itInternalCourseList = _coursesToSchedule.cbegin();
    while ((itInternalCourseList != _coursesToSchedule.cend()) && (errorIdentifier == OK)) {
        list<courseOrgBySemester> courseExtended;
        vector<courseOrgBySemester> courseExtendedVector;

        itCoursesAlreadyUsed = find(coursesAlreadyUsed.cbegin(), coursesAlreadyUsed.cend(), itInternalCourseList->getId());
        if (itCoursesAlreadyUsed == coursesAlreadyUsed.cend()) {
            coursesToExtend = regroupingCoursesForCommonCourse(_coursesToSchedule, *itInternalCourseList);
            coursesAlreadyUsed.insert(coursesAlreadyUsed.cend(), coursesToExtend.cbegin(), coursesToExtend.cend());
            errorReturn = groupedCoursesVerification(errorHandling, coursesToExtend, _coursesToSchedule, databaseCourseOfStudy, courseExtended, semesterRef);
            if (errorReturn == OK) {
                courseExtended.sort(sortMethodForCourse);
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

bool SessionScheduler::sessionScheduleFromDate(string& errorHandling, const Date& startDate, const Date& stopDate, const int& sessionNumber) {
    bool errorInScheduling = false;
    int sessionDuration;
    vector<examScheduled> dummyElementForInit(MAX_SLOT_PER_DAY);
    vector<pair<Classroom, vector<vector<examScheduled>>>>::iterator itDatesPlanning;

    sessionDuration = stopDate - startDate - ((stopDate - startDate) / 7);
    if (sessionDuration < 13) {
        errorHandling = "ERROR: the session duration doesn't guarantee the possibility of placing the second appeal and other semester's courses";
        errorInScheduling = true;
    } else {
        for (itDatesPlanning = _datesPlanning.begin(); itDatesPlanning != _datesPlanning.end(); itDatesPlanning++) {
            itDatesPlanning->second.insert(itDatesPlanning->second.end(), sessionDuration, dummyElementForInit);
        }
    }
    return !errorInScheduling;
}

void SessionScheduler::groupedCoursesScheduling(const int& sessionNumber, const int& semesterToSchedule, const Date& startDate, list<Professor>& databaseProfessorList, const int& academicYearRef) {
    bool firstAppeal = false, secondAppeal = false;
    int day = 0, slot = 0;
    list<Professor> copyDatabaseProfessorList;
    map<int, vector<vector<courseOrgBySemester>>> copyOfGroupedCoursesToPlan;
    vector<pair<Classroom, vector<vector<examScheduled>>>> copyOfDatesPlanning;
    vector<vector<courseOrgBySemester>>::iterator itGroupedCourseToPlanVector;

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
        Course TOTEST;

        for (itGroupedCourseToPlanVector = copyOfGroupedCoursesToPlan[semesterToSchedule].begin(); itGroupedCourseToPlanVector != copyOfGroupedCoursesToPlan[semesterToSchedule].end(); itGroupedCourseToPlanVector++) {
            bool endSchedulingGroup = false, errorInScheduling = false, forcedExit = false;
            int relaxedConstrain = 0, coursesPositioned = 0, coursesPositionedMax = 0, dayMax = 0, slotMax = 0;
            int freeClassroomToUse = 0;
            vector<courseOrgBySemester>::iterator itGroupedCoursesToPlanList;

            if (secondAppeal) {
                if (sessionNumber != 2) {
                    day = 12;
                } else {
                    day = 0;
                }
            }
            if (firstAppeal) {
                day = 0;
            }
            itGroupedCoursesToPlanList = itGroupedCourseToPlanVector->begin();
            while (!endSchedulingGroup) {
                itGroupedCoursesToPlanList->_constrainDeactivated[0] = false;
                TOTEST = itGroupedCoursesToPlanList->_course;
                errorInScheduling = false;
                if (constrain_1(copyOfDatesPlanning, day, copyOfGroupedCoursesToPlan, semesterToSchedule, groupNumber, courseNumber)) {
                    if (relaxedConstrain < 1) {
                        errorInScheduling = true;
                    }
                }
                TOTEST = itGroupedCoursesToPlanList->_course;
                if (constrain_2(copyOfDatesPlanning, day, slot, relaxedConstrain, copyOfGroupedCoursesToPlan, semesterToSchedule, groupNumber, courseNumber)) {
                        errorInScheduling = true;
                }
                TOTEST = itGroupedCoursesToPlanList->_course;
                if (!constrain_3(copyOfDatesPlanning, academicYearRef, startDate, day, slot, itGroupedCoursesToPlanList->_course, copyDatabaseProfessorList)) {
                    if (relaxedConstrain >= 3) {
                        itGroupedCoursesToPlanList->_constrainDeactivated[3] = true;
                    } else {
                        errorInScheduling = true;
                    }
                }
                TOTEST = itGroupedCoursesToPlanList->_course;
                if (!constrain_4(copyOfDatesPlanning, itGroupedCoursesToPlanList->_course, day, slot, freeClassroomToUse)) {
                    itGroupedCoursesToPlanList->_constrainDeactivated[0] = true;
                    if (relaxedConstrain >= 4) {
                        itGroupedCoursesToPlanList->_constrainDeactivated[4] = true;
                        if (forcedExit) {
                            itGroupedCoursesToPlanList->_constrainDeactivated[1] = false;
                            itGroupedCoursesToPlanList->_constrainDeactivated[2] = false;
                            itGroupedCoursesToPlanList->_constrainDeactivated[3] = false;
                        }
                    } else {
                        errorInScheduling = true;
                    }
                }
                TOTEST = itGroupedCoursesToPlanList->_course;
                if (relaxedConstrain != 4) {
                    if (errorInScheduling) {
                        resetDataFromDatabase(copyOfGroupedCoursesToPlan, copyOfDatesPlanning);
                        copyDatabaseProfessorList = databaseProfessorList;
                        if (slot == (copyOfDatesPlanning.front().second[day].size() - 1)) {
                            slot = 0;
                            if (day == (copyOfDatesPlanning.front().second.size() - 1)) {
                                relaxedConstrain++;
                                if (secondAppeal) {
                                    if (sessionNumber == 2) {
                                        day = 0;
                                    } else {
                                        day = 12;
                                    }
                                }
                                if (firstAppeal) {
                                    day = 0;
                                }
                            } else {
                                day++;
                            }
                        } else {
                            slot++;
                        }
                        TOTEST = itGroupedCoursesToPlanList->_course;
                        courseNumber = 0;
                        itGroupedCoursesToPlanList = itGroupedCourseToPlanVector->begin();
                    } else {
                        list<string> courseOfStudyFromCoure;
                        list<pair<string, bool>>::const_iterator itAssignedCourseOfStudy;

                        for (itAssignedCourseOfStudy = itGroupedCoursesToPlanList->_assignedCourseOfStudy.begin(); itAssignedCourseOfStudy != itGroupedCoursesToPlanList->_assignedCourseOfStudy.end(); itAssignedCourseOfStudy++) {
                            courseOfStudyFromCoure.push_back(itAssignedCourseOfStudy->first);
                        }
                        coursePositioning(copyOfDatesPlanning, itGroupedCoursesToPlanList->_course, freeClassroomToUse, day, slot, courseOfStudyFromCoure);
                        courseNumber++;
                        itGroupedCoursesToPlanList++;
                        if (itGroupedCoursesToPlanList == itGroupedCourseToPlanVector->end()) {
                            endSchedulingGroup = true;
                            courseNumber = 0;
                        }
                    }
                } else {
                    if (!itGroupedCoursesToPlanList->_constrainDeactivated[0]) {
                        list<string> courseOfStudyFromCoure;
                        list<pair<string, bool>>::const_iterator itAssignedCourseOfStudy;

                        for (itAssignedCourseOfStudy = itGroupedCoursesToPlanList->_assignedCourseOfStudy.begin(); itAssignedCourseOfStudy != itGroupedCoursesToPlanList->_assignedCourseOfStudy.end(); itAssignedCourseOfStudy++) {
                            courseOfStudyFromCoure.push_back(itAssignedCourseOfStudy->first);
                        }
                        coursePositioning(copyOfDatesPlanning, itGroupedCoursesToPlanList->_course, freeClassroomToUse, day, slot, courseOfStudyFromCoure);
                        coursesPositioned++;
                        courseNumber++;
                    }
                    itGroupedCoursesToPlanList++;
                    if (itGroupedCoursesToPlanList == itGroupedCourseToPlanVector->end()) {
                        if (!forcedExit) {
                            if (coursesPositioned > coursesPositionedMax) {
                                coursesPositionedMax = coursesPositioned;
                                dayMax = day;
                                slotMax = slot;
                            }
                            resetDataFromDatabase(copyOfGroupedCoursesToPlan, copyOfDatesPlanning);
                            copyDatabaseProfessorList = databaseProfessorList;
                            courseNumber = 0;
                            coursesPositioned = 0;
                            itGroupedCoursesToPlanList = itGroupedCourseToPlanVector->begin();
                            if (slot == (copyOfDatesPlanning.front().second[day].size() - 1)) {
                                slot = 0;
                                if (day == (copyOfDatesPlanning.front().second.size() - 1)) {
                                    day = dayMax;
                                    slot = slotMax;
                                    forcedExit = true;
                                } else {
                                    day++;
                                }
                            } else {
                                slot++;
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
            groupNumber++;
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
                                   map<int, vector<vector<courseOrgBySemester>>>& copyCoursesForConstrainViolation,
                                   const int& semesterRef, const int& groupRef, const int& courseRef) {
    bool constrain1Violated = false;
    int position = 0, positionMax = 0, slot = 0, classroom = 0;
    list<string>::const_iterator itCourseOfStudyFromFind;
    list<pair<string, bool>>::iterator itIdCourseOfStudyToFind;

    string TOTEST;

    position = dayRef - CONSTRAIN_1_DISTANCE;
    positionMax = dayRef + CONSTRAIN_1_DISTANCE + 1;
    if (position < 0) {
        position = 0;
    }
    if (positionMax > copyOfDatesPlanning[classroom].second.size() - 1) {
        positionMax = (int) copyOfDatesPlanning[classroom].second.size();
    }
    while (position < positionMax) {
        while (slot < MAX_SLOT_PER_DAY) {
            while (classroom < copyOfDatesPlanning.size()) {
                itIdCourseOfStudyToFind = copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._assignedCourseOfStudy.begin();
                while (itIdCourseOfStudyToFind != copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._assignedCourseOfStudy.end()) {
                    TOTEST = itIdCourseOfStudyToFind->first;
                    itCourseOfStudyFromFind = find(copyOfDatesPlanning[classroom].second[position][slot]._assignedCourseOfStudy.begin(), copyOfDatesPlanning[classroom].second[position][slot]._assignedCourseOfStudy.end(), itIdCourseOfStudyToFind->first);
                    if (itCourseOfStudyFromFind != copyOfDatesPlanning[classroom].second[position][slot]._assignedCourseOfStudy.end()) {
                        if (copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._course.getId() != copyOfDatesPlanning[classroom].second[position][slot]._relateCourse) {
                            constrain1Violated = true;
                            itIdCourseOfStudyToFind->second = true;
                            copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._constrainDeactivated[1] = true;

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
                    }
                    itIdCourseOfStudyToFind++;
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
                                   map<int, vector<vector<courseOrgBySemester>>>& copyCoursesForConstrainViolation,
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
            while ((classroom < copyOfDatesPlanning.size()) && !constrain2Violated && !constrain2Error) {
                if ((copyOfDatesPlanning[classroom].second[position][slot]._relateCourse == copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._course.getId())
                    && (copyOfDatesPlanning[classroom].second[position][slot]._version == copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._course.getParallelCoursesId())) {
                    copyCoursesForConstrainViolation[semesterRef][groupRef][courseRef]._constrainDeactivated[2] = true;
                    constrain2Violated = true;
                    if (position == dayRef) {
                        if ((slot >= (slotRef - CONSTRAIN_2_DISTANCE_RELAXED)) && (slot <= (slotRef + CONSTRAIN_2_DISTANCE_RELAXED))) {
                            constrain2Error = true;
                        }
                    }
                }
                classroom++;
            }
            if (!constrain2Violated && !constrain2Error) {
                classroom = 0;
                slot++;
            } else {
                slot = 6;
            }
        }
        if (!constrain2Violated && !constrain2Error) {
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
    int hourSlot = 8 + ((slotRef) * 2), examDuration = 0;
    Date unavailabilityToAssignStart, unavailabilityToAssignStop, academicYear(0, 0 , academicYearRef);
    list<AssociateProfessor>::const_iterator itCourseToInsert;
    list<Professor>::const_iterator itProfessorListToVerifyAndUpdateConst;
    list<Professor>::iterator itProfessorListToVerifyAndUpdate;

    unavailabilityToAssignStart = startSessionDate + dateIncrement + (dateIncrement / 6);
    unavailabilityToAssignStart.setHour(hourSlot);
    examDuration = approXimationFunct((courseToInsert.getEntranceTime() + courseToInsert.getExamDuration() + courseToInsert.getExitTime()), 60);
    unavailabilityToAssignStop = unavailabilityToAssignStart;
    unavailabilityToAssignStop.setHour(hourSlot + examDuration);
    itCourseToInsert = courseToInsert.getListAssistant().cbegin();
    while (itCourseToInsert != courseToInsert.getListAssistant().cend()) {
        itProfessorListToVerifyAndUpdateConst = findProfessor(professorListToVerifyAndUpdate, itCourseToInsert->getProfessorPointer()->getId());
        itProfessorListToVerifyAndUpdate = constItToNonConstIt(professorListToVerifyAndUpdate, itProfessorListToVerifyAndUpdateConst);
        if (!itProfessorListToVerifyAndUpdate->isAvailExamProgramming(unavailabilityToAssignStart, unavailabilityToAssignStop, academicYear)) {
            itCourseToInsert = courseToInsert.getListAssistant().cend();
            professorUnavailable = true;
        } else {
            itProfessorListToVerifyAndUpdate->appendUnavailabilityForExam(unavailabilityToAssignStart, unavailabilityToAssignStop);
            itCourseToInsert++;
        }
    }
    return !professorUnavailable;
}

bool SessionScheduler::constrain_4(const vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                                   const Course& courseToInsert, const int& dayRef, const int& slotRef, int& classroomChosen) {
    bool coursePositioned = false;
    int classroom = 0;
    int slot = slotRef, slotOccupancy = 0, slotOccupancyMax = approXimationFunct(approXimationFunct((courseToInsert.getEntranceTime() + courseToInsert.getExamDuration() + courseToInsert.getExitTime()), 60), 2);
    int slotEnd = slotRef + slotOccupancyMax;

    if (slotEnd <= copyOfDatesPlanning[classroom].second[dayRef].size()) {
        while ((classroom < copyOfDatesPlanning.size()) && !coursePositioned) {
            if (courseToInsert.getPartecipants() <= copyOfDatesPlanning[classroom].first.getExamCapacity()) {
                slot = slotRef;
                while ((slot < slotEnd) && !coursePositioned) {
                    if (copyOfDatesPlanning[classroom].second[dayRef][slot].isEmpty()) {
                        slotOccupancy++;
                    } else {
                        slotOccupancy = 0;
                    }
                    if (slotOccupancy == slotOccupancyMax) {
                        classroomChosen = classroom;
                        coursePositioned = true;
                    }
                    slot++;
                }
            }
            classroom++;
        }
    }
    return coursePositioned;
}

void SessionScheduler::coursePositioning(vector<pair<Classroom, vector<vector<examScheduled>>>>& copyOfDatesPlanning,
                                         const Course& courseToInsert, const int& classroomChosen, const int& dayRef,
                                         const int& slotRef, const list<string>& courseOfStudyRelatedToCourse) {
    for (int i = 0; i < approXimationFunct(approXimationFunct((courseToInsert.getEntranceTime() + courseToInsert.getExamDuration() + courseToInsert.getExitTime()), 60), 2); i++) {
        copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef + i]._relateCourse = courseToInsert.getId();
        copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef + i]._version = courseToInsert.getParallelCoursesId();
        copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef + i]._assignedCourseOfStudy = courseOfStudyRelatedToCourse;
        copyOfDatesPlanning[classroomChosen].second[dayRef][slotRef + i]._classroom = copyOfDatesPlanning[classroomChosen].first.getId();
    }
}

void SessionScheduler::outputSessionFile(const string& fileBaseName, const int& sessionNumber, const Date& sessionDateStartRef) {
    int classroom = 0, day = 0, slot = 0;
    string fileCompleteName = fileBaseName + "_s" + to_string(sessionNumber + 1) + ".txt";
    ofstream fileSessionName;
    Date dateToPrint(sessionDateStartRef);
    list<string>::const_iterator itExamScheduled;

    fileSessionName.open(fileCompleteName, ofstream::out);
    while (day < _datesPlanning[classroom].second.size()) {
        list<struct expandedScheduleForPrint> previousSchedule;

        dateToPrint.operator<<(fileSessionName);
        fileSessionName << endl;
        while (slot < _datesPlanning[classroom].second[day].size()) {
            struct expandedScheduleForPrint dummyElementToInsert;
            list<struct expandedScheduleForPrint> dailyScheduleToSortAndPrint;
            list<struct expandedScheduleForPrint>::iterator itDailyScheduleToSortAndPrint, itReturnFromFindDuplicates;


            dateToPrint.setHour(8 + (2 * slot));
            while (classroom < _datesPlanning.size()) {
                itExamScheduled = _datesPlanning[classroom].second[day][slot]._assignedCourseOfStudy.cbegin();
                while (itExamScheduled != _datesPlanning[classroom].second[day][slot]._assignedCourseOfStudy.cend()) {
                    dummyElementToInsert._assignedCourseOfStudy = *itExamScheduled;
                    dummyElementToInsert._relateCourse = _datesPlanning[classroom].second[day][slot]._relateCourse;
                    dummyElementToInsert._version = _datesPlanning[classroom].second[day][slot]._version;
                    dummyElementToInsert._classroom = _datesPlanning[classroom].second[day][slot]._classroom;
                    dailyScheduleToSortAndPrint.push_back(dummyElementToInsert);
                    itExamScheduled++;
                }
                classroom++;
            }
            if (dailyScheduleToSortAndPrint.empty()) {
                previousSchedule.clear();
            }
            dailyScheduleToSortAndPrint.sort(sortMethodForPrintSchedule);
            dateToPrint.getTimeSlot(fileSessionName);
            if (previousSchedule.empty()) {
                if (!dailyScheduleToSortAndPrint.empty()){
                    previousSchedule = dailyScheduleToSortAndPrint;
                    for (itDailyScheduleToSortAndPrint = dailyScheduleToSortAndPrint.begin(); itDailyScheduleToSortAndPrint != dailyScheduleToSortAndPrint.end(); itDailyScheduleToSortAndPrint++) {
                        itDailyScheduleToSortAndPrint->operator<<(fileSessionName);
                    }
                }
            } else {
                for (itDailyScheduleToSortAndPrint = dailyScheduleToSortAndPrint.begin(); itDailyScheduleToSortAndPrint != dailyScheduleToSortAndPrint.end(); itDailyScheduleToSortAndPrint++) {
                    itReturnFromFindDuplicates = find(previousSchedule.begin(), previousSchedule.end(), *itDailyScheduleToSortAndPrint);
                    if (itReturnFromFindDuplicates != previousSchedule.end()) {
                        fileSessionName << ";";
                    } else {
                        itDailyScheduleToSortAndPrint->operator<<(fileSessionName);
                    }
                }
                previousSchedule = dailyScheduleToSortAndPrint;
            }
            fileSessionName << endl;
            classroom = 0;
            slot++;
        }
        slot = 0;
        day++;
        if ((day % 6) == 0) {
            dateToPrint = dateToPrint + 2;
        } else {
            dateToPrint++;
        }
    }
}

void SessionScheduler::outputWarningFile(const string& fileBaseName, const int& sessionNumber) {
    string fileCompleteName = fileBaseName + "_s" + to_string(sessionNumber + 1) + "_warnings.txt";
    vector<expandedScheduleForPrint> copyAndExtensionOfGroupedCoursesToPlan;
    ofstream fileSessionName;

    fileSessionName.open(fileCompleteName, ofstream::out);
    for (map<int, vector < vector < courseOrgBySemester>>>::const_iterator itGroupedCoursesToPlan = _groupedCoursesToPlan.cbegin(); itGroupedCoursesToPlan != _groupedCoursesToPlan.cend(); itGroupedCoursesToPlan++) {
        for (vector < vector < courseOrgBySemester >> ::const_iterator itGroupOfCourses = itGroupedCoursesToPlan->second.cbegin(); itGroupOfCourses < itGroupedCoursesToPlan->second.cend(); itGroupOfCourses++) {
            for (vector<courseOrgBySemester>::const_iterator itCourseInGroup = itGroupOfCourses->cbegin(); itCourseInGroup != itGroupOfCourses->cend(); itCourseInGroup++) {
                for (list<pair<string, bool>>::const_iterator itCourseOfStudyList = itCourseInGroup->_assignedCourseOfStudy.cbegin(); itCourseOfStudyList != itCourseInGroup->_assignedCourseOfStudy.cend(); itCourseOfStudyList++) {
                    expandedScheduleForPrint dummyElementToInsert;

                    dummyElementToInsert._assignedCourseOfStudy = itCourseOfStudyList->first;
                    dummyElementToInsert._relateCourse = itCourseInGroup->_course.getId();
                    if (itCourseOfStudyList->second) {
                        dummyElementToInsert._constrainDeactivated[0] = true;
                    }
                    if (itCourseInGroup->_constrainDeactivated[2]) {
                        dummyElementToInsert._constrainDeactivated[1] = true;
                    }
                    if (itCourseInGroup->_constrainDeactivated[3]) {
                        dummyElementToInsert._constrainDeactivated[2] = true;
                    }
                    if (itCourseInGroup->_constrainDeactivated[4]) {
                        dummyElementToInsert._constrainDeactivated[3] = true;
                    }
                    copyAndExtensionOfGroupedCoursesToPlan.push_back(dummyElementToInsert);
                }
            }
        }
    }
    sort(copyAndExtensionOfGroupedCoursesToPlan.begin(), copyAndExtensionOfGroupedCoursesToPlan.end(), sortMethodForPrintWarnings);
    vector<bool> dummyConstrain = {false, false, false, false};
    string oldCourseOfStudy = copyAndExtensionOfGroupedCoursesToPlan[0]._assignedCourseOfStudy, oldCourse = copyAndExtensionOfGroupedCoursesToPlan[0]._relateCourse;

    for (vector<expandedScheduleForPrint>::const_iterator itCopyAndExtensionOfGroupedCoursesToPlan = copyAndExtensionOfGroupedCoursesToPlan.cbegin(); itCopyAndExtensionOfGroupedCoursesToPlan != copyAndExtensionOfGroupedCoursesToPlan.cend(); itCopyAndExtensionOfGroupedCoursesToPlan++) {
        if ((oldCourseOfStudy != itCopyAndExtensionOfGroupedCoursesToPlan->_assignedCourseOfStudy) || (oldCourse != itCopyAndExtensionOfGroupedCoursesToPlan->_relateCourse)) {
            for (int i = 0; i < 4; i++) {
                if (dummyConstrain[i]) {
                    fileSessionName << oldCourseOfStudy << ";" << oldCourse << ";" << to_string(i + 1) << endl;
                }
            }
            dummyConstrain = itCopyAndExtensionOfGroupedCoursesToPlan->_constrainDeactivated;
            oldCourseOfStudy = itCopyAndExtensionOfGroupedCoursesToPlan->_assignedCourseOfStudy;
            oldCourse = itCopyAndExtensionOfGroupedCoursesToPlan->_relateCourse;
        } else {
            dummyConstrain[0] = dummyConstrain[0] || itCopyAndExtensionOfGroupedCoursesToPlan->_constrainDeactivated[0];
            dummyConstrain[1] = dummyConstrain[1] || itCopyAndExtensionOfGroupedCoursesToPlan->_constrainDeactivated[1];
            dummyConstrain[2] = dummyConstrain[2] || itCopyAndExtensionOfGroupedCoursesToPlan->_constrainDeactivated[2];
            dummyConstrain[3] = dummyConstrain[3] || itCopyAndExtensionOfGroupedCoursesToPlan->_constrainDeactivated[3];
        }
    }
    for (int i = 0; i < 4; i++) {
        if (dummyConstrain[i]) {
            fileSessionName << oldCourseOfStudy << ";" << oldCourse << ";" << to_string(i + 1) << endl;
        }
    }
}

void SessionScheduler::resetDataFromDatabase(map<int, vector<vector<courseOrgBySemester>>>& groupedCourses, vector<pair<Classroom, vector<vector<examScheduled>>>>& datesPlanning) {
    for (map<int, vector<vector<courseOrgBySemester>>>::iterator itGroupedCourses = groupedCourses.begin(); itGroupedCourses != groupedCourses.end(); itGroupedCourses++) {
        for (int j = 0; j < itGroupedCourses->second.size(); j++) {
            for (int k = 0; k < itGroupedCourses->second[j].size(); k++) {
                for (int i = 0; i < itGroupedCourses->second[j][k]._constrainDeactivated.size(); ++i) {
                    itGroupedCourses->second[j][k]._constrainDeactivated[i] = _groupedCoursesToPlan[itGroupedCourses->first][j][k]._constrainDeactivated[i];
                }
                list<pair<string, bool>>::iterator itAssignedCourseOfStudyDatabase = _groupedCoursesToPlan[itGroupedCourses->first][j][k]._assignedCourseOfStudy.begin();

                for (list<pair<string, bool>>::iterator itAssignedCourseOfStudy = itGroupedCourses->second[j][k]._assignedCourseOfStudy.begin(); itAssignedCourseOfStudy != itGroupedCourses->second[j][k]._assignedCourseOfStudy.end(); itAssignedCourseOfStudy++) {
                    if (itAssignedCourseOfStudyDatabase != _groupedCoursesToPlan[itGroupedCourses->first][j][k]._assignedCourseOfStudy.end()) {
                        itAssignedCourseOfStudy->second = itAssignedCourseOfStudyDatabase->second;
                        itAssignedCourseOfStudyDatabase++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < datesPlanning.size(); i++) {
        for (int j = 0; j < datesPlanning[i].second.size(); j++) {
            for (int k = 0; k < datesPlanning[i].second[j].size(); k++) {
                datesPlanning[i].second[j][k]._assignedCourseOfStudy = _datesPlanning[i].second[j][k]._assignedCourseOfStudy;
                datesPlanning[i].second[j][k]._version = _datesPlanning[i].second[j][k]._version;
                datesPlanning[i].second[j][k]._relateCourse = _datesPlanning[i].second[j][k]._relateCourse;
                datesPlanning[i].second[j][k]._classroom = _datesPlanning[i].second[j][k]._classroom;
            }
        }
    }
}
