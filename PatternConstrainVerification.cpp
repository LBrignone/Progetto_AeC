//
// Created by Luca Brignone on 04/09/22.
//

#include "PatternConstrainVerification.h"

bool parallelVersionProgression (string& errorHandling, int prevVersionid, const string& versionToVerify) {
    int tmpVersionNumber;
    try {
        tmpVersionNumber = stoi(versionToVerify.substr(1, versionToVerify.size() - 1));
    }
    catch (const invalid_argument& cantConvert) {
        errorHandling = "impossible to convert to int the numerical part of version id: " + versionToVerify;
        return false;
    }
    if (tmpVersionNumber == (prevVersionid + 1)) {
        return true;
    } else {
        errorHandling = "the given version id (" + versionToVerify + ") is not consecutive to the previous version id";
        return false;
    }
}

string generateVersion (int versionToGenerate) {
    stringstream tmpVersionId;
    string tmp;

    tmpVersionId << setfill('0') << setw(3) << to_string(versionToGenerate + 1);
    tmp = "P" + tmpVersionId.str();
    return tmp;
}

bool versionCoherencyTest (string& errorHandling,int versionProgression, const string& versionToVerify) {
    int lValue;
    errorHandling = "";
    try {
        lValue = stoi(versionToVerify.substr(1, versionToVerify.size() - 1));
    }
    catch ( const invalid_argument& excepFromStoi) {
        errorHandling = "Error: incorrect element impossible to convert the given version id to int: " + versionToVerify;
        return false;
    }

    return lValue == versionProgression;
}

// the function below verify if all fields of a newly introduced course exists
bool courseFieldVerification (string& errorHandling, list<Course>& courseListToVerify, list<Professor>& professorList) {
    t_errorCodes errorIdentifier = OK;
    int regularProfessor, versionNumber;
    list<Course>::iterator itCourseListToVerify;
    list<AssociateProfessor>::iterator itAssociateProfessorToVerify;

    itCourseListToVerify = courseListToVerify.begin();
    while (itCourseListToVerify != courseListToVerify.end()) {
        regularProfessor = 0;
        versionNumber = 0;
        if (itCourseListToVerify->getParallelCoursesNumber() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the number of parallel versions has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExamType() == "NO_TYPE") {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exam's method has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExamClassroomType() == '\0') {
            errorIdentifier = ERR_course_format;
            errorHandling = "the classroom's type has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getEntranceTime() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the entrance time has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExitTime() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exit time has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getExamDuration() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the exam duration has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        if (itCourseListToVerify->getPartecipants() == -1) {
            errorIdentifier = ERR_course_format;
            errorHandling = "the number of partecipants has not been set for the newly introduced course with id: " + itCourseListToVerify->getId();
        }
        itAssociateProfessorToVerify = itCourseListToVerify->getListAssistant().begin();
        while ((itAssociateProfessorToVerify != itCourseListToVerify->getListAssistant().end()) && (errorIdentifier == OK)) {
            if (itAssociateProfessorToVerify->getProfessorPointer() == professorList.end()) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the professor id has not been set for the newly introduced course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (itAssociateProfessorToVerify->getLessonH() == -1) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the lesson hour has not been set for the newly introduced course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (itAssociateProfessorToVerify->getExerciseH() == -1) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the exercise hour has not been set for the newly introduced course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (itAssociateProfessorToVerify->getLabH() == -1) {
                errorIdentifier = ERR_course_format;
                errorHandling = "the laboratory hour has not been set for the newly introduced course with id: " + itCourseListToVerify->getId() +
                                " version number: " + to_string(versionNumber);
            }
            if (regularProfessor == 0) {
                if (!itAssociateProfessorToVerify->getIsMain()) {
                    errorIdentifier = ERR_course_format;
                    errorHandling = "the regular professor has not been set for the newly introduced course with id: " + itCourseListToVerify->getId() +
                                    " version number: " + to_string(versionNumber);
                }
                if (itAssociateProfessorToVerify->getToCheck()) {
                    errorIdentifier = ERR_course_format;
                    errorHandling = "one professor id either as regular professor or as the firs field in professor's hour organization has not been set for the newly introduced course with id: " +
                                    itCourseListToVerify->getId()  + " version number: " + to_string(versionNumber);
                }
            }
            itAssociateProfessorToVerify++;
            regularProfessor++;
        }
        versionNumber++;
    }

    if (errorIdentifier == OK) {
        return true;
    } else {
        return false;
    }
}

// here the vector of dates created in "ExamSessionInputFile" is verified wrt coherency between the academic year and the year of exam sessions
bool examSessionAcademicYearCoherencyTest (string& errorHandling, int academicYearStd, const vector<Date>& sessionToVerify) {
    t_errorCodes errorIdentifier = OK;
    int dateFieldSession = 0;

    while ((dateFieldSession < 6) && (errorIdentifier == OK)) {
        if ((sessionToVerify.at(dateFieldSession).getYear() != academicYearStd) || sessionToVerify.at(dateFieldSession).getYear() != (academicYearStd + 1))) {
            errorIdentifier = ERR_academic_year;
            if ((dateFieldSession % 2) == 0) {
                errorHandling = "the year set as ending session number " + to_string(dateFieldSession / 2) + " is not compatible with academic year " +
                                to_string(academicYearStd);
            } else {
                errorHandling = "the year set as starting session number " + to_string(dateFieldSession / 2) + " is not compatible with academic year" +
                                to_string(academicYearStd);
            }
        }
        dateFieldSession++;
    }
    if (errorIdentifier == OK) {
        return true;
    } else {
        return false;
    }
}

// here the beginning of each session is verified to be before the ending of same session
bool examSessionBeginEndVerification(string& errorHandling, const vector<Date>& sessionToVerify) {
    t_errorCodes errorIdentifier = OK;
    int sessionIdentifier = 0;

    while ((sessionIdentifier < 3) && (errorIdentifier == OK)) {
        // the start date of the session is compared with the finish date
        // if the start date comes after the finish date that's an error
        if (sessionToVerify.at(sessionIdentifier * 2) > sessionToVerify.at((sessionIdentifier * 2) + 1)) {
            errorIdentifier = ERR_session_planning;
            errorHandling = "the session number " + to_string(sessionIdentifier) + "has dates that doesn't respect the proper order (start before stop)";
        }
        sessionIdentifier++;
    }
    if (errorIdentifier == OK) {
        return true;
    } else {
        return false;
    }
}

// here is verified the correctness of exam session's ordering (session 1 before 2 and 3, session 2 before 3)
bool examSessionOrderVerification(string& errorHandling, const vector<Date>& sessionToVerify) {
    t_errorCodes errorIdentifier = OK;
    int sessionIdentifier = 0;

    while ((sessionIdentifier < 2) && (errorIdentifier == OK)) {
        if (sessionIdentifier == 0) {
            if (sessionToVerify.at(sessionIdentifier * 2) > sessionToVerify.at((sessionIdentifier * 2) + 4)) {
                errorIdentifier = ERR_session_planning;
                errorHandling = "the session number " + to_string(sessionIdentifier) + " begins after the beginning of session number " + to_string(sessionIdentifier + 2);
            }
            if (sessionToVerify.at((sessionIdentifier * 2) + 1) > sessionToVerify.at((sessionIdentifier * 2) + 4)) {
                errorIdentifier = ERR_session_planning;
                errorHandling = "the session number " + to_string(sessionIdentifier) + " ends after the beginning of session number " + to_string(sessionIdentifier + 2);
            }
        }
        if (sessionToVerify.at(sessionIdentifier * 2) > sessionToVerify.at((sessionIdentifier * 2) + 2)) {
            errorIdentifier = ERR_session_planning;
            errorHandling = "the session number " + to_string(sessionIdentifier) + " begins after the beginning of session number " + to_string(sessionIdentifier + 1);
        }
        if (sessionToVerify.at((sessionIdentifier * 2) + 1) > sessionToVerify.at((sessionIdentifier * 2) + 2)) {
            errorIdentifier = ERR_session_planning;
            errorHandling = "the session number " + to_string(sessionIdentifier) + " ends after the beginning of session number " + to_string(sessionIdentifier + 1);
        }
        sessionIdentifier++;
    }
    if (errorIdentifier == OK) {
        return true;
    } else {
        return false;
    }
}

bool sessionDurationConstrainVerification(string& errorHandling, const vector<Date>& sessionToVerify) {
    t_errorCodes errorIdentifier = OK;
    int examDurationInDays, sessionIdentifier = 0;

    while ((sessionIdentifier < 3) && (errorIdentifier == OK)) {
        if ((sessionIdentifier == 0) || (sessionIdentifier == 1)) {
            examDurationInDays = sessionToVerify.at(sessionIdentifier * 2 + 1) - sessionToVerify.at(sessionIdentifier * 2);
            if (((examDurationInDays / 7) != 6) || ((examDurationInDays % 7) != 0)) {
                errorIdentifier = ERR_exam_duration;
                errorHandling = "the session number " + to_string(sessionIdentifier) + " has a duration which is different from the canonical 6 weeks";
            }
        }
        if (sessionIdentifier == 2) {
            examDurationInDays = sessionToVerify.at(sessionIdentifier * 2 + 1) - sessionToVerify.at(sessionIdentifier * 2);
            if (((examDurationInDays / 7) != 4) || ((examDurationInDays % 7) != 0)) {
                errorIdentifier = ERR_exam_duration;
                errorHandling = "the session number " + to_string(sessionIdentifier) + " has a duration which is different from the canonical 4 weeks";
            }
        }
        sessionIdentifier++;
    }
}

// the start and stop date's control is performed through the list of already inserted/appended unavailable date, in particular it is controlled:
// - the date couple is already present
// - the start date or stop date falls in a previous range
bool unavailabilityDatesVerification (const AvailForExam& dateToVerify, const list<AvailForExam>& datesToVerifyWith) {
    t_errorCodes errorIdentifier = OK;
    list<AvailForExam>::const_iterator itListUnavailDates;

    itListUnavailDates = datesToVerifyWith.begin();
    while ((itListUnavailDates != datesToVerifyWith.end()) && (errorIdentifier == OK)) {
        if ((itListUnavailDates->start == dateToVerify.start) || (itListUnavailDates->stop == dateToVerify.stop)) {
            errorIdentifier = ERR_unavailability_format;
        }
        if (((itListUnavailDates->start <= dateToVerify.stop) && (itListUnavailDates->start >= dateToVerify.start)) && !problemInDatesSet) {
            errorIdentifier = ERR_unavailability_format;
        }
        if (((itListUnavailDates->stop <= dateToVerify.stop) && (itListUnavailDates->stop >= dateToVerify.start)) && !problemInDatesSet) {
            errorIdentifier = ERR_unavailability_format;
        }
            itListUnavailDates++;
    }
    if (errorIdentifier == OK) {
        // if there's no incoherent date value the return is TRUE
        return true;
    } else {
        // if the given unavailability date to insert has overlapping or equal value(s) to one alredy in database
        //the return is FALSE
        return false;
    }
}