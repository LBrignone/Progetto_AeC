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

// COURSE 7
// given a course's title a duplicate is searched in the list of courses, if another course has the same title as the one
// we are looking for the return will be TRUE, otherwise it will be FALSE
bool findCourseTitle(const list<Course>& courseList, const string& titleToFind) {
    list<Course>::const_iterator itCourseList;
    bool found = false;

    itCourseList = courseList.cbegin();
    while ((itCourseList != courseList.cend()) && !found) {
        if (itCourseList->getTitle() == titleToFind) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return found;
}

list<CourseOfStudy>::const_iterator findCourseOfStudy(const list<CourseOfStudy>& courseOfStudyList, const string& idToFind){
    bool found = false;
    list<CourseOfStudy>::const_iterator it_courseOfStudyList;

    it_courseOfStudyList = courseOfStudyList.cbegin();
    while ((it_courseOfStudyList != courseOfStudyList.cend()) && !found) {
        if (it_courseOfStudyList->getCourseOfStudyId() == idToFind) {
            found = true;
        } else {
            it_courseOfStudyList++;
        }
    }

    return it_courseOfStudyList;
}

// this function is going to work only on database so all the data should be correct at the time of using it
// the function returns a list of courses of study as ids, and the semester in which they are scheduled as last element
list<string> findCourseOfStudy(string& errorHandling, const list<CourseOfStudy>& courseOfStudyList, const string& idToFind) {
    bool errorInCheck = false;
    int j = 0, semester = -2, validSemester = -2, endedCourse = -2;
    vector<int> vectorOfSemesterForCourse;
    list<string> listOfCoursesOfStudyForCourse;
    list<CourseOfStudy>::const_iterator itCourseOfStudyList;

    itCourseOfStudyList = courseOfStudyList.cbegin();
    while(itCourseOfStudyList != courseOfStudyList.cend()) {
        int i = -1;

        if (itCourseOfStudyList->findCourse(i, idToFind) != -2) {
            listOfCoursesOfStudyForCourse.push_back(itCourseOfStudyList->getCourseOfStudyId());
            if (itCourseOfStudyList->getGraduationType() == "BS") {
                while((i > -2) && (i < 6)) {
                    semester = itCourseOfStudyList->findCourse(i, idToFind);
                    if (semester != -2) {
                        if (semester == -1) {
                            endedCourse = -1;
                        } else {
                            if (validSemester == -2) {
                                validSemester = semester % 2;
                            } else {
                                if (validSemester != (semester % 2)) {
                                    errorInCheck = true;
                                }
                            }
                        }
                        i = semester + 1;
                    } else {
                        i = semester;
                    }
                }
            } else if (itCourseOfStudyList->getGraduationType() == "MS") {
                while((i > -2) && (i < 4)) {
                    semester = itCourseOfStudyList->findCourse(i, idToFind);
                    if (semester != -2) {
                        if (semester == -1) {
                            endedCourse = -1;
                        } else {
                            if (validSemester == -2) {
                                validSemester = semester % 2;
                            } else {
                                if (validSemester != (semester % 2)) {
                                    errorInCheck = true;
                                }
                            }
                        }
                        i = semester + 1;
                    } else {
                        i = semester;
                    }
                }
            }
        }
        itCourseOfStudyList++;
    }
    if (errorInCheck){
        errorHandling = "ERROR: the course " + idToFind + " appears to be in more than one semester";
        listOfCoursesOfStudyForCourse.clear();
    } else {
        if (!listOfCoursesOfStudyForCourse.empty()) {
            listOfCoursesOfStudyForCourse.push_back(to_string(validSemester));
            listOfCoursesOfStudyForCourse.push_back(to_string(endedCourse));
        }
    }
    return listOfCoursesOfStudyForCourse;
}

list<string> findCourseIdGrouped(const list<Course>& courseList, const string& idToFind) {
    list<string> toReturn;
    list<Course>::const_iterator itCourseList;

    itCourseList = courseList.cbegin();
    while (itCourseList != courseList.cend()) {
        list<string> copyGoupedCourses = itCourseList->getListGroupedId();
        if (std::find(copyGoupedCourses.begin(), copyGoupedCourses.end(), idToFind) != copyGoupedCourses.end()) {
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
