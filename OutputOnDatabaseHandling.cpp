//
// Created by Luca Brignone on 04/10/22.
//

#include "OutputOnDatabaseHandling.h"

int updateStudentDatabaseFile(string& errorHandling, const string& databaseStudentFileName, const list<Student>& updatedStudentList) {
    t_typeErrorDefinitionReadingFile errorIdentifier = OK;
    ofstream fileName;

    if (!databaseStudentFileName.empty()) {
        fileName.open(databaseStudentFileName, ofstream::trunc);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file " + databaseStudentFileName + " not found";
        } else {
            list<Student>::const_iterator itListStudent;

            itListStudent = updatedStudentList.cbegin();
            while (itListStudent != updatedStudentList.end()) {
                fileName << itListStudent.operator->();
                itListStudent++;
                if (itListStudent != updatedStudentList.end()) {
                    fileName << endl;
                }
            }
        }
        if (fileName.is_open()) {
            fileName.close();
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateProfessorDatabaseFile(string& errorHandling, const string& databaseProfessorFileName, const list<Professor>& updatedProfessorList) {
    t_typeErrorDefinitionReadingFile errorIdentifier = OK;
    ofstream fileName;

    if (!databaseProfessorFileName.empty()) {
        fileName.open(databaseProfessorFileName, ofstream::trunc);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file " + databaseProfessorFileName + " not found";
        } else {
            list<Professor>::const_iterator itListProfessor;

            itListProfessor = updatedProfessorList.cbegin();
            while (itListProfessor != updatedProfessorList.cend()) {
                fileName << itListProfessor.operator->();
                itListProfessor++;
                if (itListProfessor != updatedProfessorList.end()) {
                    fileName << endl;
                }
            }
        }
        if (fileName.is_open()) {
            fileName.close();
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateClassroomDatabaseFile(string& errorHandling, const string& databaseClassroomFileName, const list<Classroom>& updatedClassroomList) {
    t_typeErrorDefinitionReadingFile errorIdentifier = OK;
    ofstream fileName;

    if (!databaseClassroomFileName.empty()) {
        fileName.open(databaseClassroomFileName, ofstream::trunc);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file " + databaseClassroomFileName + " not found";
        } else {
            list<Classroom>::const_iterator itListClassroom;

            itListClassroom = updatedClassroomList.cbegin();
            while (itListClassroom != updatedClassroomList.cend()) {
                fileName << itListClassroom.operator->();
                itListClassroom++;
                if (itListClassroom != updatedClassroomList.end()) {
                    fileName << endl;
                }
            }
        }
        if (fileName.is_open()) {
            fileName.close();
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateCourseOfStudyDatabaseFile(string& errorHandling, const string& databaseCourseOfStudyFileName, const list<CourseOfStudy>& updatedCourseOfStudyList) {
    t_typeErrorDefinitionReadingFile errorIdentifier = OK;
    ofstream fileName;

    if (!databaseCourseOfStudyFileName.empty()) {
        fileName.open(databaseCourseOfStudyFileName, ofstream::trunc);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file " + databaseCourseOfStudyFileName + " not found";
        } else {
            list<CourseOfStudy>::const_iterator itListCourseOfStudy;

            itListCourseOfStudy = updatedCourseOfStudyList.cbegin();
            while (itListCourseOfStudy != updatedCourseOfStudyList.cend()) {
                fileName << itListCourseOfStudy.operator->();
                itListCourseOfStudy++;
                if (itListCourseOfStudy != updatedCourseOfStudyList.end()) {
                    fileName << endl;
                }
            }
        }
        if (fileName.is_open()) {
            fileName.close();
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateCourseDatabaseFile(string& errorHandling, const string& databaseCourseFileName, const list<Course>& updatedCourseList) {
    t_typeErrorDefinitionReadingFile errorIdentifier = OK;
    ofstream fileName;
    bool firstVersion = true, closed = false;
    int tmpCourseAA;
    string tmpCourseId;

    if (!databaseCourseFileName.empty()) {
        fileName.open(databaseCourseFileName, ofstream::trunc);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file " + databaseCourseFileName + " not found";
        } else {
            list<Course>::const_iterator itListCourse;

            itListCourse = updatedCourseList.cbegin();
            tmpCourseId = itListCourse->getId();
            tmpCourseAA = itListCourse->getStartYear();
            itListCourse->printCourseOrganization(fileName);
            itListCourse->printCourseOrganizationAcademicYearOpening(fileName);
            while (itListCourse != updatedCourseList.cend()) {
                if (tmpCourseId != itListCourse->getId()) {
                    tmpCourseId = itListCourse->getId();
                    itListCourse--;
                    itListCourse->printCourseOrganizationAcademicYearClosing(fileName);
                    closed = true;
                    itListCourse++;
                    if (itListCourse != updatedCourseList.cend()) {
                        itListCourse->printCourseOrganization(fileName);
                        closed = false;
                    }
                }
                if (tmpCourseAA != itListCourse->getStartYear()) {
                    tmpCourseAA = itListCourse->getStartYear();
                    itListCourse->printCourseOrganizationAcademicYearOpening(fileName);
                }
                itListCourse->printCourseOrganizationVersionOpening(fileName, firstVersion);
                firstVersion = false;
                fileName << itListCourse.operator->();
                itListCourse++;
                if (itListCourse != updatedCourseList.cend()) {
                    fileName << endl;
                }
            }
            // this error should never happen otherwise all the changes, even if correct, will be discarded resulting in a complete loss of changes
            // moreover the database file will be irremediably modified resulting in corruption of database
            if (!closed) {
                errorIdentifier = ERR_update_database;
                errorHandling = "Error: the update of file's database, named db_corsi.txt, resulted in an incorrect collection of stored data";
            }
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}
