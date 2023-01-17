//
// Created by Luca Brignone on 11/11/22.
//

#include "FieldVerificationForScheduling.h"

// the function below verify if all fields of a newly introduced course exists
bool courseFieldVerification (string& errorHandling, const list<Course>& courseListToVerify, list<Professor>& professorList) {
    t_errorCodes errorIdentifier = OK;
    int regularProfessor, versionNumber;
    list<Course>::const_iterator itCourseListToVerify;
    list<string>::const_iterator itGroupedCoursesToVerify;
    list<AssociateProfessor>::const_iterator itAssociateProfessorToVerify;

    itCourseListToVerify = courseListToVerify.cbegin();
    while ((itCourseListToVerify != courseListToVerify.end()) && (errorIdentifier == OK)) {
        regularProfessor = 0;
        versionNumber = 0;
        if (itCourseListToVerify->getStartYear() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the academic year has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getCfu() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the cfu has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getParallelCoursesId().empty()) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the version id has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getTitle().empty()) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the title has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getParallelCoursesNumber() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the number of parallel versions has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getCourseLessonH() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the lesson hour has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getCourseExerciseH() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exercise hour has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getCourseLabH() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the laboratory hour has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExamType() == "NO_TYPE") {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exam's method has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExamClassroomType() == '\0') {
            errorIdentifier = ERR_course_format;
            errorHandling = "the classroom's type has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getEntranceTime() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the entrance time has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExitTime() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exit time has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExamDuration() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exam duration has not been set for course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getPartecipants() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the number of participants has not been set for course with id: " + itCourseListToVerify->getId();
        }
        itAssociateProfessorToVerify = itCourseListToVerify->getListAssistant().cbegin();
        while ((itAssociateProfessorToVerify != itCourseListToVerify->getListAssistant().cend()) && (errorIdentifier == OK)) {
            string tmpErrorLine;
            if (itAssociateProfessorToVerify->getProfessorPointer() == professorList.cend()) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the professor id has not been set for course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            } else if (!professorFieldVerification(tmpErrorLine, *itAssociateProfessorToVerify->getProfessorPointer())) {
                    errorIdentifier = ERR_course_format;
                    errorHandling = "the professor number " + to_string(regularProfessor) + " has " + tmpErrorLine;
            }
            if (itAssociateProfessorToVerify->getLessonH() == -1) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the lesson hour has not been set for course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (itAssociateProfessorToVerify->getExerciseH() == -1) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the exercise hour has not been set for course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (itAssociateProfessorToVerify->getLabH() == -1) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the laboratory hour has not been set for course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (regularProfessor == 0) {
                if (!itAssociateProfessorToVerify->getIsMain()) {
                    errorIdentifier = ERR_course_format;
                    errorHandling = "the regular professor has not been set for course with id: " + itCourseListToVerify->getId() +
                                    " version number: " + to_string(versionNumber);
                }
                if (itAssociateProfessorToVerify->getToCheck()) {
                    errorIdentifier = ERR_course_format;
                    errorHandling = "one professor id either as regular professor or as the firs field in professor's hour organization has not been set for course with id: " +
                                    itCourseListToVerify->getId()  + " version number: " + to_string(versionNumber);
                }
            }
            itAssociateProfessorToVerify++;
            regularProfessor++;
        }
        if ((!itCourseListToVerify->getListGroupedId().empty()) && (errorIdentifier == OK)) {
            list<string> copyGroupedCourses = itCourseListToVerify->getListGroupedId();

            itGroupedCoursesToVerify = copyGroupedCourses.cbegin();
            while (itGroupedCoursesToVerify != copyGroupedCourses.cend()) {
                list<Course>::const_iterator itGroupedCoursesFind;
                itGroupedCoursesFind = findCourse(courseListToVerify, itCourseListToVerify->getId(), itCourseListToVerify->getStartYear());
                if (itGroupedCoursesFind == courseListToVerify.cend()) {
                    errorIdentifier = ERR_course_format;
                    errorHandling = "can't find the grouped course with id: " + *itGroupedCoursesToVerify + " for course with id: " + itCourseListToVerify->getId();
                }
                itGroupedCoursesToVerify++;
            }
        }
        versionNumber++;
        itCourseListToVerify++;
    }

    return errorIdentifier == OK;
}

bool professorFieldVerification(string& errorHandling, const Professor& professorToVerify) {
    t_errorCodes errorIdentifier = OK;
// the professor's id is not controlled because if the professor is in the database's list the id is automatically assigned
    if (professorToVerify.getName().empty()) {
        errorIdentifier = ERR_professor_format;
        errorHandling = "the professor's name has not been set for" + professorToVerify.getId();
    }
    if (professorToVerify.getSurname().empty()) {
        errorIdentifier = ERR_professor_format;
        errorHandling = "the professor's surname not been set for" + professorToVerify.getId();
    }
    if (professorToVerify.getMail().empty()) {
        errorIdentifier = ERR_professor_format;
        errorHandling = "the professor's mail not been set for" + professorToVerify.getId();
    }

    return errorIdentifier == OK;
}

bool classroomFieldVerification(string& errorHandling, const list<Classroom>& databaseClassroomToVerify) {
    t_errorCodes errorIdentifier = OK;
    list<Classroom>::const_iterator itClassroomList;

    itClassroomList = databaseClassroomToVerify.cbegin();
    while ((itClassroomList != databaseClassroomToVerify.cend()) && (errorIdentifier == OK)) {
        if (itClassroomList->getType() == '\0') {
            errorIdentifier = ERR_classroom_format;
            errorHandling = "the classroom's type has not been set for " + itClassroomList->getId();
        }
        if (itClassroomList->getClassroomName().empty()) {
            errorIdentifier = ERR_classroom_format;
            errorHandling = "the classroom's name has not been set for " + itClassroomList->getId();
        }
        if (itClassroomList->getCapacity() == -1) {
            errorIdentifier = ERR_classroom_format;
            errorHandling = "the classroom's capacity has not been set for " + itClassroomList->getId();
        }
        if (itClassroomList->getExamCapacity() == -1) {
            errorIdentifier = ERR_classroom_format;
            errorHandling = "the classroom's exam capacity has not been set for " + itClassroomList->getId();
        }
        itClassroomList++;
    }

    return errorIdentifier == OK;
}

list<string> regroupingCoursesForCommonCourse(const list<Course>& courseToSchedule, const Course& courseToFind) {
    list<string> toReturn, toRegroup;
    list<string>::iterator itToReturn;

    toReturn.push_back(courseToFind.getId());
    itToReturn = toReturn.begin();
    while (itToReturn != toReturn.end()) {
        list<Course>::const_iterator itCourseToSchedule = findCourse(courseToSchedule, *itToReturn);

        if (itCourseToSchedule != courseToSchedule.cend()) {
            list<string> copyGroupedCourses;

            copyGroupedCourses = itCourseToSchedule->getListGroupedId();
            toReturn.insert(toReturn.end(), copyGroupedCourses.begin(), copyGroupedCourses.end());
            toRegroup = findCourseIdGrouped(courseToSchedule, *itToReturn);
            toReturn.insert(toReturn.end(), toRegroup.begin(), toRegroup.end());
            myUnique(toReturn);
        }
        itToReturn++;
    }
    return toReturn;
}

// this function is used to verify the consistency of a grouped course's list with regard to course's semester with other
// courses in the list and the rule that impose 2 days distance between courses organized in the same course of study, other
// than create the expanded list of courses related with the version and course of study
int groupedCoursesVerification(string& errorHandling, const list<string>& groupedCourses, const list<Course>& coursesToSchedule, const list<CourseOfStudy>& databaseCourseOfStudy, list<struct courseOrgBySemester>& courseListToSchedule, int& semester) {
    t_errorCodes errorIdentifier = OK;
    int numberOfVersions = 0;
    string errorLine;
    courseOrgBySemester elementListStructGroupedCourse;
    list<string> courseOfStudyRelatedToCourse;
    list<pair<string, bool>> dummyAssignedCourseOfStudy;
    list<string>::const_iterator itGroupedCourses, itCourseOfStudyRelatedToCourse;
    list<Course>::const_iterator  itCoursesToSchedule;

    semester = -2;
    itGroupedCourses = groupedCourses.cbegin();
    while ((itGroupedCourses != groupedCourses.cend()) && (errorIdentifier == OK)) {
        itCoursesToSchedule = findCourse(coursesToSchedule, *itGroupedCourses);
        if (itCoursesToSchedule != coursesToSchedule.end()) {
            numberOfVersions = itCoursesToSchedule->getParallelCoursesNumber();
            courseOfStudyRelatedToCourse = findCourseOfStudy(errorLine, databaseCourseOfStudy, *itGroupedCourses);
            if (courseOfStudyRelatedToCourse.empty()) {
                errorIdentifier = ERR_grouped_id;
                errorHandling = errorLine;
            } else {
                if (!itCoursesToSchedule->isActiveCourse()) {
                    // in case the course is inactive the correct semester is "-1"
                    // here the proper controls are performed regarding the coherency and proper memorization regarding the semester
                    if (semester == -2) {
                        if (courseOfStudyRelatedToCourse.back() == "-1") {
                            semester = -1;
                            courseOfStudyRelatedToCourse.pop_back();
                            courseOfStudyRelatedToCourse.pop_back();
                        } else {
                            errorIdentifier = ERR_semester;
                            errorHandling =
                                    "ERROR: the course " + *itGroupedCourses + " is inactive and it has no valid semester";
                        }
                    } else if ((semester != stoi(courseOfStudyRelatedToCourse.back())) &&
                               (courseOfStudyRelatedToCourse.back() == "-1")) {
                        errorIdentifier = ERR_semester;
                        errorHandling = "ERROR: the course " + *itGroupedCourses + "'s semester (" +
                                        courseOfStudyRelatedToCourse.back() +
                                        ") is incoherent with previous course's semester (" + to_string(semester) + ")";
                    } else if ((semester != stoi(courseOfStudyRelatedToCourse.back())) &&
                               (courseOfStudyRelatedToCourse.back() == "-2")) {
                        errorIdentifier = ERR_semester;
                        errorHandling = "ERROR: the course " + *itGroupedCourses + " is inactive and it has no valid semester";
                    } else {
                        courseOfStudyRelatedToCourse.pop_back();
                        courseOfStudyRelatedToCourse.pop_back();
                    }
                } else if (itCoursesToSchedule->isActiveCourse()) {
                    // in case the course is active the first semester is "0" and the second is "1"
                    // here the course is active, but the last element proposes an inactive status hence a pop is done and the new last
                    // element is taken into account controlling if it's valid and the coherent with previous course's semester
                    courseOfStudyRelatedToCourse.pop_back();
                    if (semester == -2) {
                        if (courseOfStudyRelatedToCourse.back() != "-2") {
                            semester = stoi(courseOfStudyRelatedToCourse.back());
                            courseOfStudyRelatedToCourse.pop_back();
                        } else {
                            errorIdentifier = ERR_semester;
                            errorHandling =
                                    "ERROR: the course " + *itGroupedCourses + " is active but it has no valid semester";
                        }
                    } else if (semester != stoi(courseOfStudyRelatedToCourse.back())) {
                        errorIdentifier = ERR_semester;
                        errorHandling = "ERROR: the course " + *itGroupedCourses + "'s semester (" +
                                        courseOfStudyRelatedToCourse.back() +
                                        ") is incoherent with previous course's semester (" + to_string(semester) + ")";
                    } else if (courseOfStudyRelatedToCourse.back() == "-2") {
                        errorIdentifier = ERR_semester;
                        errorHandling = "ERROR: the course " + *itGroupedCourses + " is active but it has no valid semester";
                    } else {
                        courseOfStudyRelatedToCourse.pop_back();
                    }
                }
            }
            if (errorIdentifier == OK) {
                for (itCourseOfStudyRelatedToCourse = courseOfStudyRelatedToCourse.begin(); itCourseOfStudyRelatedToCourse !=  courseOfStudyRelatedToCourse.end(); itCourseOfStudyRelatedToCourse++) {
                    dummyAssignedCourseOfStudy.emplace_back(*itCourseOfStudyRelatedToCourse, false);
                }
                for (int i = 0; i < numberOfVersions; i++) {
                    elementListStructGroupedCourse._course = *itCoursesToSchedule;
                    elementListStructGroupedCourse._assignedCourseOfStudy = dummyAssignedCourseOfStudy;
                    courseListToSchedule.push_back(elementListStructGroupedCourse);
                    itCoursesToSchedule++;
                }
                dummyAssignedCourseOfStudy.clear();
            }
        }

        itGroupedCourses++;
    }
    return errorIdentifier;
}

void myUnique(list<string>& courseList) {
    list<string>::iterator itCourseList;

    itCourseList = courseList.begin();
    while (itCourseList != courseList.end()) {
        list<string>::iterator itCourseListInner;

        itCourseListInner = courseList.begin();
        while (itCourseListInner != courseList.end()) {
            if ((itCourseList != itCourseListInner) && (*itCourseList == *itCourseListInner)) {
                itCourseListInner = courseList.erase(itCourseListInner);
            } else {
                itCourseListInner++;
            }
        }
        itCourseList++;
    }
}
