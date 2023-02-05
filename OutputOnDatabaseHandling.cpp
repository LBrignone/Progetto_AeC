//
// Created by Luca Brignone on 04/10/22.
//

#include "OutputOnDatabaseHandling.h"

int updateStudentDatabaseFile(string& errorHandling, const string& databaseStudentFileName, const list<Student>& updatedStudentList) {
    t_errorCodes errorIdentifier = OK;
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
                itListStudent->operator<<(fileName);
                itListStudent++;
                if (itListStudent != updatedStudentList.end()) {
                    fileName << endl;
                }
            }
            if (fileName.is_open()) {
                fileName.close();
            }
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateProfessorDatabaseFile(string& errorHandling, const string& databaseProfessorFileName, const list<Professor>& updatedProfessorList) {
    t_errorCodes errorIdentifier = OK;
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
                itListProfessor->operator<<(fileName);
                itListProfessor++;
                if (itListProfessor != updatedProfessorList.end()) {
                    fileName << endl;
                }
            }
            if (fileName.is_open()) {
                fileName.close();
            }
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateClassroomDatabaseFile(string& errorHandling, const string& databaseClassroomFileName, const list<Classroom>& updatedClassroomList) {
    t_errorCodes errorIdentifier = OK;
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
                itListClassroom->operator<<(fileName);
                itListClassroom++;
                if (itListClassroom != updatedClassroomList.end()) {
                    fileName << endl;
                }
            }
            if (fileName.is_open()) {
                fileName.close();
            }
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateCourseOfStudyDatabaseFile(string& errorHandling, const string& databaseCourseOfStudyFileName, const list<CourseOfStudy>& updatedCourseOfStudyList) {
    t_errorCodes errorIdentifier = OK;
    bool wroteSomething = false;
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
                wroteSomething = true;
                itListCourseOfStudy->operator<<(fileName);
                itListCourseOfStudy++;
                if (itListCourseOfStudy != updatedCourseOfStudyList.end()) {
                    fileName << endl;
                }
            }
            if (!wroteSomething) {
                errorIdentifier = ERR_write;
                errorHandling = "Error: courses of study's list is empty";
            }
            if (fileName.is_open()) {
                fileName.close();
            }
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateCourseDatabaseFile(string& errorHandling, const string& databaseCourseFileName, const list<Course>& updatedCourseList) {
    t_errorCodes errorIdentifier = OK;
    ofstream fileName;
    bool firstVersion = true;
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
                if ((tmpCourseId != itListCourse->getId()) || tmpCourseAA != itListCourse->getStartYear()) {
                    itListCourse--;
                    itListCourse->printCourseOrganizationAcademicYearClosing(fileName);
                    fileName << endl;
                    itListCourse++;
                }
                if (tmpCourseId != itListCourse->getId()) {
                    tmpCourseId = itListCourse->getId();
                    itListCourse->printCourseOrganization(fileName);
                    firstVersion = true;
                    tmpCourseAA = itListCourse->getStartYear();
                    itListCourse->printCourseOrganizationAcademicYearOpening(fileName);
                } else if (tmpCourseAA != itListCourse->getStartYear()) {
                    firstVersion = true;
                    tmpCourseAA = itListCourse->getStartYear();
                    itListCourse->printCourseOrganizationAcademicYearOpening(fileName);
                }
                itListCourse->printCourseOrganizationVersionOpening(fileName, firstVersion);
                firstVersion = false;
                itListCourse->operator<<(fileName);
                itListCourse++;
            }
            itListCourse--;
            itListCourse->printCourseOrganizationAcademicYearClosing(fileName);
            if (fileName.is_open()) {
                fileName.close();
            }
        }
    } else {
        errorIdentifier = ERR_empty_field;
        errorHandling = "Error: missing file element";
    }
    return (int) errorIdentifier;
}

int updateExamSessionDatabaseFile(string& errorHandling, const string& databaseExamSessionFileName, const map<Date, vector<Date>>& updatedExamSessionMap) {
    t_errorCodes errorIdentifier = OK;
    int separator = 0;
    ofstream fileName;
    map<Date, vector<Date>>::const_iterator itMapExamSession;

    fileName.open(databaseExamSessionFileName, ofstream::trunc);
    if (!fileName.is_open()) {
        errorIdentifier = ERR_open_file;
        errorHandling = "Error: file " + databaseExamSessionFileName + " not found";
    } else {
        itMapExamSession = updatedExamSessionMap.cbegin();
        while (itMapExamSession != updatedExamSessionMap.cend()) {
            vector<Date>::const_iterator itVectorDates;

            itMapExamSession->first.getAcademicYear(fileName);
            fileName << " ";
            itVectorDates = itMapExamSession->second.cbegin();
            while (itVectorDates != itMapExamSession->second.cend()) {
                itVectorDates->operator<<(fileName);
                switch (separator) {
                    case 0:{
                        fileName << "_";
                        separator++;
                        break;
                    }
                    case 1:{
                        fileName << " ";
                        separator = 0;
                        break;
                    }
                    default:{
                        errorIdentifier = ERR_separator;
                        errorHandling = " Error: separator not consistent with regard to session's date pattern";
                        break;
                    }
                }
                itVectorDates++;
            }
            fileName << endl;
            itMapExamSession++;
        }
    }
    if (fileName.is_open()) {
        fileName.close();
    }

    return (int) errorIdentifier;
}

int updateUnavailabilityDatabaseFile(string& errorHandling, const string& databaseUnavailabilityFileName, list<Professor>& updatedProfessorList) {
    t_errorCodes errorIdentifier = OK;
    bool academicYearToPrint, professorToPrint, endlineToPrint;
    Date minDate, maxDate;
    ofstream fileName;
    Professor minInListProfessor;
    list<Professor>::const_iterator itListProfessor;

    fileName.open(databaseUnavailabilityFileName, ofstream::trunc);
    if (!fileName.is_open()) {
        errorIdentifier = ERR_open_file;
        errorHandling = "Error: file " + databaseUnavailabilityFileName + " not found";
    } else {
        updatedProfessorList.sort(sortMethodForProf);
        minInListProfessor = min_element(updatedProfessorList.begin(), updatedProfessorList.end(), comp);
        minDate = minInListProfessor.getMinDateForUnavail();
        maxDate = findMaxAcademicYearUnavail(updatedProfessorList);
        maxDate.increaseAcademicYear();
        while (minDate != maxDate) {
            academicYearToPrint = true;
            itListProfessor = updatedProfessorList.cbegin();
            while (itListProfessor != updatedProfessorList.cend()) {
                string tmpError;
                Date tmpDate;
                list<AvailForExam>::const_iterator itListUnavailDates;

                itListUnavailDates = itListProfessor->getUnavailListByAcademicYear(tmpError, minDate).begin();
                if (tmpError.empty()) {
                    professorToPrint = true;
                    endlineToPrint = false;
                    while ((itListUnavailDates != itListProfessor->getUnavailListByAcademicYear(tmpError, minDate).end()) && tmpError.empty()) {
                        endlineToPrint = true;
                        if (academicYearToPrint) {
                            minDate.getAcademicYear(fileName);
                            fileName << endl;
                            academicYearToPrint = false;
                        }
                        if (professorToPrint) {
                            fileName << itListProfessor->getId() << ";";
                            professorToPrint = false;
                        }
                        if (itListUnavailDates != itListProfessor->getUnavailListByAcademicYear(tmpError, minDate).begin()) {
                            fileName << ";";
                        }
                        tmpDate = itListUnavailDates->start;
                        tmpDate.operator<<(fileName);
                        fileName << "|";
                        tmpDate = itListUnavailDates->stop;
                        tmpDate.operator<<(fileName);
                        itListUnavailDates++;
                    }
                    if (endlineToPrint){
                        fileName << endl;
                    }
                }
                itListProfessor++;
            }
            minDate.increaseAcademicYear();
        }
        if (fileName.is_open()) {
            fileName.close();
        }
    }
    return (int) errorIdentifier;
}