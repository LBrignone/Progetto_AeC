//
// Created by Luca Brignone on 27/08/22.
//

#include "findSomethingInList.h"

// STUDENT
// given the id of a student a search in the student list is performed by mean of the given id
// returns an iterator that identify the presence of the given id
list<Student>::iterator findStudent(const list<Student>& studentList, const string& idToFind) {
    list<Student> copyOfStudentList = studentList;
    list<Student>::iterator itStudentList;
    bool found = false;

    itStudentList = copyOfStudentList.begin();
    while ((itStudentList != copyOfStudentList.end()) && !found) {
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
list<Professor>::iterator findProfessor(const list<Professor>& professorList, const string& idToFind) {
    list<Professor> copyOfProfessorList = professorList;
    list<Professor>::iterator itProfessorList;
    bool found = false;

    itProfessorList = copyOfProfessorList.begin();
    while ((itProfessorList != copyOfProfessorList.end()) && !found) {
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
list<Classroom>::iterator findClassroom(const list<Classroom>& classroomList, const string& idToFind) {
    list<Classroom> copyOfClassroomList = classroomList;
    list<Classroom>::iterator itClassroomList;
    bool found = false;

    itClassroomList = copyOfClassroomList.begin();
    while ((itClassroomList != copyOfClassroomList.end()) && !found) {
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
list<Course>::iterator findCourse(list<Course>& courseList, const string& idToFind) {
    list<Course>::iterator itCourseList;
    list<Course>::iterator lastInsertion;
    bool found = false;

    itCourseList = courseList.begin();
    while ((itCourseList != courseList.end()) && !found) {
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
list<Course>::iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear) {
    list<Course> copyOfCourseList = courseList;
    list<Course>::iterator itCourseList;
    list<Course>::iterator lastInsertion;
    bool found = false;

    while (itCourseList != copyOfCourseList.end()) {
        if ((itCourseList->getId() == idToFind) && (itCourseList->getStartYear() == academicYear)) {
            found = true;
        } else {
            itCourseList++;
        }
    }
    return itCourseList;
}

// COURSE 3
// given the id and academic year of a course a search in the course list is performed by mean of the given id AND academic year
// return an iterator that identify the presence of the given id and academic year
list<Course>::iterator findCourse(const list<Course>& courseList, const string& idToFind, const int& academicYear , const string& parallelVersion) {
    list<Course> copyOfCourseList = courseList;
    list<Course>::iterator itCourseList;
    list<Course>::iterator lastInsertion;
    bool found = false;

    while (itCourseList != copyOfCourseList.end()) {
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
list<Course>::iterator findCourseLastForId(const list<Course>& courseList, const string& idToFind, const list<Course>::iterator & startPos) {
    list<Course> copyOfCourseList = courseList;
    list<Course>::iterator itCourseList;
    list<Course>::iterator lastInsertion;
    bool found = false;

    itCourseList = startPos;
    while ((itCourseList != copyOfCourseList.end()) && !found) {
        if (itCourseList->getId() != idToFind) {
            itCourseList++;
        } else {
            found = true;
        }
    }
    return itCourseList;
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
