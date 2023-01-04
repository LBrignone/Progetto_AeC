//
// Created by Luca Brignone on 27/08/22.
//

#include "FindSomethingInList.h"

// STUDENT
// given the id of a student a search in the student list is performed by mean of the given id
// returns an iterator that identify the presence of the given id
list<Student>::const_iterator findStudent(const list<Student>& studentList, const string& idToFind) {
    list<Student>::const_iterator itStudentList;
    bool found = false;

    itStudentList = studentList.cbegin();
    while ((itStudentList != studentList.cend()) && !found) {
        if (itStudentList->getId() == idToFind) {
            found = true;
        } else {
            itStudentList++;
        }
    }
    return itStudentList;
}

// PROFESSOR
// given the id of a professor a search in the professor list is performed by mean of the given id
// return an iterator that identify the presence of the given id
list<Professor>::const_iterator findProfessor(const list<Professor>& professorList, const string& idToFind) {
    list<Professor>::const_iterator itProfessorList;
    bool found = false;

    itProfessorList = professorList.cbegin();
    while ((itProfessorList != professorList.cend()) && !found) {
        if (itProfessorList->getId() == idToFind) {
            found = true;
        } else {
            itProfessorList++;
        }
    }
    return itProfessorList;
}

// CLASSROOM
// given the id of a classroom a search in the classroom list is performed by mean of the given id
// return an iterator that identify the presence of the given id
list<Classroom>::const_iterator findClassroom(const list<Classroom>& classroomList, const string& idToFind) {
    list<Classroom>::const_iterator itClassroomList;
    bool found = false;

    itClassroomList = classroomList.cbegin();
    while ((itClassroomList != classroomList.cend()) && !found) {
        if (itClassroomList->getId() == idToFind) {
            found = true;
        } else {
            itClassroomList++;
        }
    }
    return itClassroomList;
}

// COURSE 1
// given the id of a course a search in the course list is performed by mean of the given id
// return an iterator that identify the presence of last element represented by the id
list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind) {
    list<Course>::const_iterator itCourseList;
    bool found = false;

    itCourseList = courseList.cbegin();
    while ((itCourseList != courseList.cend()) && !found) {
        if (itCourseList->getId() == idToFind) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return itCourseList;
}

// COURSE 2
// given the id and academic year of a course a search in the course list is performed by mean of the given id AND academic year
// return an iterator that identify the presence of the given id and academic year
list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear) {
    list<Course>::const_iterator itCourseList;
    bool found = false;

    itCourseList = courseList.cbegin();
    while ((itCourseList != courseList.cend()) && !found) {
        if ((itCourseList->getId() == idToFind) && (itCourseList->getStartYear() == academicYear)) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return itCourseList;
}

// COURSE 3
// given the id and academic year of a course a search in the course list is performed by mean of the given id, academic year AND version
// return an iterator that identify the presence of the given id, academic year and version
list<Course>::const_iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear , const string& parallelVersion) {
    list<Course>::const_iterator itCourseList;
    bool found = false;

    itCourseList = courseList.cbegin();
    while (itCourseList != courseList.cend() && !found) {
        if ((itCourseList->getId() == idToFind) && (itCourseList->getStartYear() == academicYear) && (itCourseList->getParallelCoursesId() == parallelVersion)) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return itCourseList;
}

// COURSE 4
// given the id of a course and a starting position a search in the course list is performed by mean of the given id from the starting position
// return an iterator that identify the presence of last element represented by the id
list<Course>::iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const int& startPos) {
    list<Course> copyOfCourseList = courseList;
    list<Course>::iterator itCourseList;
    list<Course>::iterator lastInsertion;
    bool found = false;

    itCourseList = copyOfCourseList.begin();
    if (startPos != 0) {
        for (int i = 0; i < startPos; i++) {
            itCourseList++;
        }
    }
    while ((itCourseList != copyOfCourseList.end()) && !found) {
        if (itCourseList->getId() != idToFind) {
            itCourseList++;
        } else {
            found = true;
        }
    }
    return itCourseList;
}

// COURSE 5
// given the id of a course a search in the course list is performed by mean of the given id
// return an iterator that identify the presence of last element represented by the id
list<Course>::const_iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const list<Course>::const_iterator& startPos) {
    list<Course>::const_iterator itCourseList;
    bool found = false;

    itCourseList = startPos;
    while ((itCourseList != courseList.end()) && !found) {
        if (itCourseList->getId() != idToFind) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return itCourseList;
}

// COURSE 6
// given the id and academic year of a course a search in the course list is performed by mean of the given id AND academic year
// return an iterator that identify the presence of last element represented by the id AND academic year
list<Course>::const_iterator findCourseLastForIdAndYear(const list<Course>& courseList, const string& idToFind, const int& academicYear, const list<Course>::const_iterator& startPos) {
    list<Course>::const_iterator itCourseList;
    bool found = false;

    itCourseList = startPos;
    while ((itCourseList != courseList.cend()) && !found) {
        if ((itCourseList->getId() != idToFind) || (itCourseList->getStartYear() != academicYear)) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return itCourseList;
}

// this function is going to work only on database so all the data should be correct at the time of using it
// the function returns a list of courses of study as ids, and the semester in which they are scheduled as last element
list<string> findCourseOfStudy(string& errorHandling, const list<CourseOfStudy>& courseOfStudyList, const string& idToFind) {
    bool errorInCheck = false;
    int j = 0, semester = -2, endedCourse = -2;
    vector<int> vectorOfSemesterForCourse;
    list<string> listOfCoursesOfStudyForCourse;
    list<CourseOfStudy>::const_iterator itCourseOfStudyList;

    itCourseOfStudyList = courseOfStudyList.cbegin();
    while(itCourseOfStudyList != courseOfStudyList.cend()) {
        if (itCourseOfStudyList->getGraduationType() == "BS") {
            for (int i = -1; i < 6; i++) {
                semester = itCourseOfStudyList->findCourse(i, idToFind);
                if (semester == -2) {
                    i = 6;
                } else {
                    vectorOfSemesterForCourse.push_back(semester % 2);
                    listOfCoursesOfStudyForCourse.push_back(itCourseOfStudyList->getCourseOfStudyId());
                }
            }
        } else if (itCourseOfStudyList->getGraduationType() == "MS") {
            for (int i = -1; i < 4; i++) {
                semester = itCourseOfStudyList->findCourse(i, idToFind);
                if (semester == -2) {
                    i = 4;
                } else {
                    vectorOfSemesterForCourse.push_back(semester % 2);
                    listOfCoursesOfStudyForCourse.push_back(itCourseOfStudyList->getCourseOfStudyId());
                }
            }
        }
        itCourseOfStudyList++;
    }
    if (vectorOfSemesterForCourse[0] != -1) {
        semester = vectorOfSemesterForCourse[0];
    } else {
        endedCourse = -1;
    }
    while ((j < ((vectorOfSemesterForCourse.size() - 1))) && !errorInCheck) {
        j++;
        if ((vectorOfSemesterForCourse[j - 1] != vectorOfSemesterForCourse[j]) &&
            ((vectorOfSemesterForCourse[j - 1] != -1) || (vectorOfSemesterForCourse[j] != -1))) {
            listOfCoursesOfStudyForCourse.clear();
            errorHandling = "ERROR: the course " + idToFind + "appears to be in more than one semester";
            errorInCheck = true;
        } else {
            if (vectorOfSemesterForCourse[j] != -1) {
                semester = vectorOfSemesterForCourse[j];
            } else {
                endedCourse = -1;
            }
        }
    }
    if (!listOfCoursesOfStudyForCourse.empty()) {
        listOfCoursesOfStudyForCourse.push_back(to_string(semester));
        listOfCoursesOfStudyForCourse.push_back(to_string(endedCourse));
    }
    return listOfCoursesOfStudyForCourse;
}

list<string> findCourseIdGrouped(const list<Course>& courseList, const string& idToFind) {
    list<string> toReturn;
    list<Course>::const_iterator itCourseList;

    itCourseList = courseList.cbegin();
    while (itCourseList != courseList.cend()) {
        if (std::find(itCourseList->getListGroupedId().begin(), itCourseList->getListGroupedId().end(), idToFind) != itCourseList->getListGroupedId().end()) {
            toReturn.push_back(itCourseList->getId());
        }
        itCourseList++;
    }
    return toReturn;
}

// MAX UNAVAIL DATE
Date findMaxAcademicYearUnavail(const list<Professor>& professorList) {
    Date tmpMax;
    list<Professor>::const_iterator itListProfessor;

    itListProfessor = professorList.cbegin();
    while (itListProfessor != professorList.cend()) {
        if (tmpMax < itListProfessor->getMaxDateForUnavail()) {
            tmpMax = itListProfessor->getMaxDateForUnavail();
        }
        itListProfessor++;
    }
    return tmpMax;
}

bool findDistanceSameCourseOfStudy(const vector<pair<Classroom, vector<vector<examScheduled>>>>& planningToSearchIn, const list<string>& courseOfStudyToFind, const int& dayRefPosition) {
    bool constrain1Violated = false;
    int position = 0, slot = 0;
    list<string>::const_iterator itCourseOfStudyListFromToFind, itCourseOfStudyListFromScheduling;
    vector<pair<Classroom, vector<vector<examScheduled>>>>::const_iterator itPlanningToSearchIn;

    position = dayRefPosition - 2;
    if (position < 0) {
        position = 0;
    }
    itPlanningToSearchIn = planningToSearchIn.begin();
    while (position < (dayRefPosition + 2)) {
        while (itPlanningToSearchIn != planningToSearchIn.cend()) {
            while (slot < 5) {
                itCourseOfStudyListFromToFind = courseOfStudyToFind.begin();
                while (itCourseOfStudyListFromToFind != courseOfStudyToFind.end()) {
                    itCourseOfStudyListFromScheduling = find(itPlanningToSearchIn->second[position][slot]._assignedCourseOfStudy.begin(), itPlanningToSearchIn->second[position][slot]._assignedCourseOfStudy.end(), *itCourseOfStudyListFromToFind);
                    if (itCourseOfStudyListFromScheduling != itPlanningToSearchIn->second[position][slot]._assignedCourseOfStudy.end()) {
                        constrain1Violated = true;
                        itCourseOfStudyListFromToFind = courseOfStudyToFind.end();
                    } else {
                        itCourseOfStudyListFromToFind++;
                    }
                }
                if (!constrain1Violated) {
                    slot++;
                } else if (position == dayRefPosition) {
                    slot = 0;
                    position++;
                } else {
                    slot = 6;
                }
            }
            if (slot != 6) {
                itPlanningToSearchIn++;
            } else {
                itPlanningToSearchIn = planningToSearchIn.cend();
            }
        }
        if (slot != 6) {
            position++;
            slot = 0;
        } else {
            position = dayRefPosition + 2;
        }
    }
    return slot == 6;
}

// MIN UNAVAIL DATE
bool comp(Professor professorToCompare, Professor minimum) {
    return (professorToCompare.getMinDateForUnavail() < minimum.getMinDateForUnavail());
}

bool sortMethodForProf(Professor professorToCompare, Professor minimum) {
    return (professorToCompare < minimum);
}

bool sortMethodForClassroom(Classroom classroomToCompare, Classroom minimum) {
    return (classroomToCompare.getExamCapacity() < minimum.getExamCapacity());
}

bool sortMethodForCourse(struct courseOrgBySemester courseToCompare, struct courseOrgBySemester minimum) {
    return (courseToCompare._course.getPartecipants() < minimum._course.getPartecipants());
}

bool sortMethodForPrintSchedule(const struct expandedScheduleForPrint& structToCompare, const struct expandedScheduleForPrint& minimum) {
    bool toReturn = false;

    if (structToCompare._relateCourse.compare(minimum._relateCourse) < 0) {
        toReturn = true;
    } else if (structToCompare._relateCourse.compare(minimum._relateCourse) > 0) {
        toReturn = false;
    } else {
        if (structToCompare._version.compare(minimum._version) < 0) {
            toReturn = true;
        } else if (structToCompare._version.compare(minimum._version) > 0) {
            toReturn = false;
        } else {
            if (structToCompare._assignedCourseOfStudy.compare(minimum._assignedCourseOfStudy) < 0) {
                toReturn = true;
            } else {
                toReturn = false;
            }
        }
    }
    return toReturn;
}

bool sortMethodForPrintWarnings(const struct expandedScheduleForPrint& structToCompare, const struct expandedScheduleForPrint& minimum) {
    bool toReturn = false;

    if (structToCompare._assignedCourseOfStudy.compare(minimum._assignedCourseOfStudy) < 0) {
        toReturn = true;
    } else if (structToCompare._assignedCourseOfStudy.compare(minimum._assignedCourseOfStudy) > 0) {
        toReturn = false;
    } else {
        if (structToCompare._relateCourse.compare(minimum._relateCourse) < 0) {
            toReturn = true;
        } else {
            toReturn = false;
        }
    }
    return toReturn;
}

int approXimationFunct(const int& rightVal, const int& leftVal) {
    int tmp = rightVal/leftVal, resto = rightVal % leftVal;
    if (resto != 0) {
        tmp += 1;
    }
    return tmp;
}
