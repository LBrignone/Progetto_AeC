#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

#include "Date.h"
#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include "Classroom.h"
#include "CourseOfStudy.h"
#include "ErrorHandling.h"
#include "AddFileHandling.h"
#include "InsertFileHandling.h"
#include "UpdateFileHandling.h"
#include "OutputOnDatabaseHandling.h"

#define studentDatabaseName "db_studenti.txt"
#define professorDatabaseName "db_professori.txt"
#define classroomDatabaseName "db_aule.txt"
#define courseDatabaseName "db_corsi.txt"
#define courseOfStudyDatabaseName "db_corsi_studio.txt"
#define examSessionPeriodsDatabaseName "db_periodi_esami.txt"
#define unavailabilityDatabaseFile "db_indisponibilità.txt"

using namespace std;

int main(int argc, char** argv) {
    t_errorCodes errorIdentifier = OK;
    bool okSchedule = true;
    int functionReturn = OK, funcReturnDbFile = OK, academicYearInt;
    string commandIdentifier, actionIdentifier, fileNameFromCommandLine, academicYearFromCommandLine, academicYearFromCommandLineAndExamPeriod;
    string errorLine, errorLineDummy;
    Date academicYear;
    list<Student> databaseOfStudents;
    list<Professor> databaseOfProfessors;
    list<Classroom> databaseOfClassrooms;
    list<Course> databaseOfCourses;
    list<CourseOfStudy> databaseOfCoursesOfStudy;
    map<Date, vector<Date>> databaseOfExamSession;

    if (argc < 3) {
        errorIdentifier = ERR_arguments_number;
        errorLine = "number of argument is less than required";
    }
    commandIdentifier = argv[1];
    switch (argc) {
        case 3:{
            fileNameFromCommandLine = argv[2];
            break;
        }
        case 4:{
            academicYearFromCommandLine = argv[2];
            fileNameFromCommandLine = argv[3];
            break;
        }
        case 5:{
            actionIdentifier = argv[2];
            academicYearFromCommandLine = argv[3];
            fileNameFromCommandLine = argv[4];
            break;
        }
        case 7:{
            actionIdentifier = argv[2];
            for (int i = 0; i < 4; i++) {
                academicYearFromCommandLineAndExamPeriod.append(argv[i + 3]);
                if (i != 3) {
                    academicYearFromCommandLineAndExamPeriod.append(" ");
                }
            }
            break;
        }
        default:{
            errorIdentifier = ERR_arguments_number;
            errorLine = "number of argument is higher than the possible number required (3, 5 or 7)";
            break;
        }
    }

    if (errorIdentifier == OK) {
        switch (commandIdentifier[1]) {
            case 'a': {
                switch (commandIdentifier[3]) {
                    case 's': {
                        if (fileNameFromCommandLine == studentDatabaseName) {
                            funcReturnDbFile = StudentInputFile(errorLine, fileNameFromCommandLine, databaseOfStudents, true);
                        } else {
                            funcReturnDbFile = StudentInputFile(errorLine, studentDatabaseName, databaseOfStudents, true);
                            if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                                (funcReturnDbFile == ERR_empty_file)) {
                                funcReturnDbFile = OK;
                                functionReturn = StudentInputFile(errorLine, fileNameFromCommandLine, databaseOfStudents, false);
                            }
                        }
                        if (functionReturn == OK || functionReturn == ERR_not_found) {
                            functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, databaseOfStudents);
                        }
                        break;
                    }
                    case 'd': {
                        if (fileNameFromCommandLine == professorDatabaseName) {
                            funcReturnDbFile = ProfessorInputFile(errorLine, fileNameFromCommandLine, databaseOfProfessors, true);
                        } else {
                            funcReturnDbFile = ProfessorInputFile(errorLine, professorDatabaseName, databaseOfProfessors, true);
                            if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                                (funcReturnDbFile == ERR_empty_file)) {
                                funcReturnDbFile = OK;
                                functionReturn = ProfessorInputFile(errorLine, fileNameFromCommandLine, databaseOfProfessors, false);
                            }
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, databaseOfProfessors);
                        }
                        break;
                    }
                    case 'a': {
                        if (fileNameFromCommandLine == classroomDatabaseName) {
                            funcReturnDbFile = ClassroomInputFile(errorLine, fileNameFromCommandLine, databaseOfClassrooms, true);
                        } else {
                            funcReturnDbFile = ClassroomInputFile(errorLine, classroomDatabaseName, databaseOfClassrooms, true);
                            if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                                (funcReturnDbFile == ERR_empty_file)) {
                                funcReturnDbFile = OK;
                                functionReturn = ClassroomInputFile(errorLine, fileNameFromCommandLine, databaseOfClassrooms, false);
                            }
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateClassroomDatabaseFile(errorLine, classroomDatabaseName, databaseOfClassrooms);
                        }
                        break;
                    }
                    case 'c': {
                        // it is necessary to recall in first place the professor's database, because it will be used when reading the course's database
                        // and perform proper controls, BUT if the file exists or not is not a binding condition
                        ProfessorInputFile(errorLine, professorDatabaseName, databaseOfProfessors, true);
                        if (fileNameFromCommandLine == courseDatabaseName) {
                            funcReturnDbFile = CourseInputFile(errorLine, fileNameFromCommandLine, databaseOfCourses, databaseOfProfessors, true);
                        } else {
                            funcReturnDbFile = CourseInputFile(errorLine, courseDatabaseName, databaseOfCourses, databaseOfProfessors, true);
                            if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                                (funcReturnDbFile == ERR_empty_file)) {
                                funcReturnDbFile = OK;
                                functionReturn = CourseInputFile(errorLine, fileNameFromCommandLine, databaseOfCourses, databaseOfProfessors, false);
                            }
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, databaseOfCourses);
                        }
                        break;
                    }
                    case 'f': {
                        if (fileNameFromCommandLine == courseOfStudyDatabaseName) {
                            funcReturnDbFile = CourseOfStudyInputFile(errorLine, fileNameFromCommandLine, databaseOfCoursesOfStudy, true);
                        } else {
                            funcReturnDbFile = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, databaseOfCoursesOfStudy, true);
                            if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                                (funcReturnDbFile == ERR_empty_file)) {
                                funcReturnDbFile = OK;
                                functionReturn = CourseOfStudyInputFile(errorLine, fileNameFromCommandLine, databaseOfCoursesOfStudy, false);
                            }
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateCourseOfStudyDatabaseFile(errorLine, courseOfStudyDatabaseName, databaseOfCoursesOfStudy);
                        }
                        break;
                    }
                    default: {
                        errorIdentifier = ERR_wrong_identifier;
                        errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
                        break;
                    }
                }
                break;
            }
            case 'u': {
                switch (commandIdentifier[3]) {
                    case 's': {
                        if (fileNameFromCommandLine != studentDatabaseName) {
                            funcReturnDbFile = StudentInputFile(errorLine, studentDatabaseName, databaseOfStudents, true);
                            if (funcReturnDbFile == OK) {
                                functionReturn = StudentToUpdateFile(errorLine, fileNameFromCommandLine, databaseOfStudents);
                            } else {
                                errorLine += "\nImpossible to update  \"" + (string) studentDatabaseName + "\"  without database to start from";
                            }
                        } else {
                            errorIdentifier = ERR_update_database;
                            errorLine = "Error: can't update \"" + (string) studentDatabaseName + "\" with the same database file";
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, databaseOfStudents);
                        }
                        break;
                    }
                    case 'd': {
                        if (fileNameFromCommandLine != professorDatabaseName) {
                            funcReturnDbFile = ProfessorInputFile(errorLine, professorDatabaseName, databaseOfProfessors, true);
                            if (funcReturnDbFile == OK) {
                                functionReturn = ProfessorToUpdateFile(errorLine, fileNameFromCommandLine, databaseOfProfessors);
                            } else {
                                errorLine += "\nImpossible to update \"" + (string) professorDatabaseName + "\" without database to start from";
                            }
                        } else {
                            errorIdentifier = ERR_update_database;
                            errorLine = "Error: can't update \"" + (string) professorDatabaseName + "\" with the same database file";
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, databaseOfProfessors);
                        }
                        break;
                    }
                    case 'a': {
                        if (fileNameFromCommandLine != classroomDatabaseName) {
                            funcReturnDbFile = ClassroomInputFile(errorLine, classroomDatabaseName, databaseOfClassrooms, true);
                            if (funcReturnDbFile == OK) {
                                functionReturn = ClassroomToUpdateFile(errorLine, fileNameFromCommandLine, databaseOfClassrooms);
                            } else {
                                errorLine += "\nImpossible to update \"" + (string) classroomDatabaseName + "\" without database to start from";
                            }
                        } else {
                            errorIdentifier = ERR_update_database;
                            errorLine = "Error: can't update \"" + (string) courseDatabaseName + "\" with same database file";
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateClassroomDatabaseFile(errorLine, classroomDatabaseName, databaseOfClassrooms);
                        }
                        break;
                    }
                    default: {
                        errorIdentifier = ERR_wrong_identifier;
                        errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
                        break;
                    }
                }
                break;
            }
            case 'i': {
                switch (commandIdentifier[3]) {
                    case 'c': {
                        // the existence of professor's database is not a constraint for the insertion or modification of courses,
                        // so the return is checked only for file correctness
                        funcReturnDbFile = ProfessorInputFile(errorLine, professorDatabaseName, databaseOfProfessors, true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                            (funcReturnDbFile == ERR_empty_file)) {
                            funcReturnDbFile = OK;
                            // also the presence of course of study's database isn't a constraint to the correct functioning of
                            // courses insertion, but if it is present it is necessary to perform some actions on itself too
                            // if a course is set as "non_attivo" if the same course is used in some course of study then:
                            // - if all other academic years, for that same course is "attivo" then in course of study that course is
                            //   COPIED in non-active list
                            // - if all years for which is defined are "non_attivo" then it is REMOVED from its semester and inserted
                            //   in non-active list
                            funcReturnDbFile = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, databaseOfCoursesOfStudy, true);
                            if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) ||
                                (funcReturnDbFile == ERR_empty_file)) {
                                funcReturnDbFile = OK;
                                funcReturnDbFile = CourseInputFile(errorLine, courseDatabaseName, databaseOfCourses, databaseOfProfessors, true);
                                if (funcReturnDbFile == OK) {
                                    functionReturn = CourseToInsertFile(errorLine, fileNameFromCommandLine,
                                                                        databaseOfCourses, databaseOfProfessors, databaseOfCoursesOfStudy);
                                } else {
                                    errorLine +=
                                            "\nCan't perform an insertion or modification without the course's database file \"" +
                                            (string) courseDatabaseName + "\"";
                                }
                            } else {
                                errorLine += "\nCan't perform the insertion command, because the file \"" +
                                             (string) courseOfStudyDatabaseName + "\" has been found corrupted";
                            }
                        } else {
                            errorLine += "\nCan't perform the insertion command, because the file \"" +
                                         (string) courseOfStudyDatabaseName + "\" has been found corrupted";
                        }
                        if (functionReturn == OK) {
                            functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, databaseOfCourses);
                            if (functionReturn == OK) {
                                functionReturn = updateCourseOfStudyDatabaseFile(errorLine, courseOfStudyDatabaseName,
                                                                                 databaseOfCoursesOfStudy);
                            } else {
                                errorLine += "\nCan't update the " + (string) courseOfStudyDatabaseName +
                                             " due to an error updating " + (string) courseDatabaseName;
                            }
                        }
                        break;
                    }
                    default: {
                        errorIdentifier = ERR_wrong_identifier;
                        errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
                        break;
                    }
                }
                break;
            }
            case 's': {
                if (actionIdentifier == "current_a") {
                    funcReturnDbFile = ExamSessionInputFile(errorLine, examSessionPeriodsDatabaseName,
                                                            databaseOfExamSession, true);
                    if (((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file))
                        && (fileNameFromCommandLine != examSessionPeriodsDatabaseName)) {
                        funcReturnDbFile = OK;
                        functionReturn = ExamSessionInputFile(errorLine, academicYearFromCommandLineAndExamPeriod,
                                                              databaseOfExamSession, false);
                    } else {
                        errorIdentifier = ERR_file_name;
                        errorLine += "\nCan't update \"" + (string) examSessionPeriodsDatabaseName + "\"";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateExamSessionDatabaseFile(errorLine, examSessionPeriodsDatabaseName,
                                                                       databaseOfExamSession);
                    }
                } else if (actionIdentifier == "set_availability") {
                    funcReturnDbFile = ProfessorUnavailabilityInputFile(errorLine, unavailabilityDatabaseFile,
                                                                        databaseOfProfessors, "", true);
                    if (((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file))
                        && (fileNameFromCommandLine != examSessionPeriodsDatabaseName)) {
                        funcReturnDbFile = OK;
                        functionReturn = ProfessorUnavailabilityInputFile(errorLine, fileNameFromCommandLine,
                                                                          databaseOfProfessors, academicYearFromCommandLine,
                                                                          false);
                    } else {
                        errorIdentifier = ERR_file_name;
                        errorLine += "\nCan't update \"" + (string) unavailabilityDatabaseFile + "\"";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateUnavailabilityDatabaseFile(errorLine, unavailabilityDatabaseFile,
                                                                          databaseOfProfessors);
                    }
                } else {
                    errorIdentifier = ERR_wrong_identifier;
                    errorLine = "ERROR: no matching action for command identifier: " + commandIdentifier + " " +
                                actionIdentifier;
                }
                break;
            }
            case 'g': {
                map<Date, vector<Date>>::const_iterator itDatabaseOfExamSession;

                fileNameFromCommandLine = fileNameFromCommandLine.substr(0, fileNameFromCommandLine.find('.'));
                try {
                    academicYearInt = stoi(academicYearFromCommandLine.substr(0, 4));
                    academicYear.setYear(academicYearInt);
                }
                catch (const invalid_argument& excepFromStoi) {
                    errorIdentifier = ERR_stoi_conversion;
                    errorLine = "ERROR: can't convert academic year given for exam's scheduling to int";
                }
                if (errorIdentifier == OK) {
                    funcReturnDbFile = ProfessorInputFile(errorLineDummy, professorDatabaseName, databaseOfProfessors,
                                                          true);
                    if (funcReturnDbFile != OK) {
                        okSchedule = false;
                        errorLine += errorLineDummy + "\n";
                    }
                    funcReturnDbFile = ClassroomInputFile(errorLineDummy, classroomDatabaseName, databaseOfClassrooms,
                                                          true);
                    if (funcReturnDbFile != OK) {
                        okSchedule = false;
                        errorLine += errorLineDummy + "\n";
                    }
                    funcReturnDbFile = CourseInputFile(errorLineDummy, courseDatabaseName, databaseOfCourses,
                                                       databaseOfProfessors, true);
                    if (funcReturnDbFile != OK) {
                        okSchedule = false;
                        errorLine += errorLineDummy + "\n";
                    }
                    funcReturnDbFile = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, databaseOfCoursesOfStudy,
                                                              true);
                    if (funcReturnDbFile != OK) {
                        okSchedule = false;
                        errorLine += errorLineDummy + "\n";
                    }
                    funcReturnDbFile = ExamSessionInputFile(errorLine, examSessionPeriodsDatabaseName, databaseOfExamSession,
                                                            true);
                    if (funcReturnDbFile != OK) {
                        okSchedule = false;
                        errorLine += errorLineDummy + "\n";
                    } else {
                        itDatabaseOfExamSession = databaseOfExamSession.find(academicYear);
                        if (itDatabaseOfExamSession == databaseOfExamSession.cend()) {
                            okSchedule = false;
                            errorLine += "Can't find the specified academic year (" + academicYear.getAcademicYear() + ") in "
                                        + (string)examSessionPeriodsDatabaseName + "\n";
                        }
                    }
                    funcReturnDbFile = ProfessorUnavailabilityInputFile(errorLine, unavailabilityDatabaseFile,
                                                                        databaseOfProfessors, "", true);
                    if (funcReturnDbFile != OK) {
                        okSchedule = false;
                        errorLine += errorLineDummy + "\n";
                    }
                    if (okSchedule) {
                        int i = 0;

                        while ((i < 3) && okSchedule) {
                            SessionScheduler examPlanning(errorLine, academicYearInt, databaseOfCourses,
                                                          databaseOfProfessors, databaseOfClassrooms,
                                                          databaseOfCoursesOfStudy, itDatabaseOfExamSession->second[i * 2],
                                                          itDatabaseOfExamSession->second[(i * 2) + 1],i);
                            if (errorLine.empty()) {
                                switch (i) {
                                    case 0:{
                                        examPlanning.groupedCoursesScheduling(i, 0,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        examPlanning.groupedCoursesScheduling(i, 1,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        examPlanning.groupedCoursesScheduling(i, -1,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        break;
                                    }
                                    case 1:{
                                        examPlanning.groupedCoursesScheduling(i, 1,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        examPlanning.groupedCoursesScheduling(i, 0,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        examPlanning.groupedCoursesScheduling(i, -1,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        break;
                                    }
                                    case 2: {
                                        examPlanning.groupedCoursesScheduling(i, 0,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        examPlanning.groupedCoursesScheduling(i, 1,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        examPlanning.groupedCoursesScheduling(i, -1,
                                                                              itDatabaseOfExamSession->second[i * 2],
                                                                              databaseOfProfessors, academicYearInt);
                                        break;
                                    }
                                    default:{
                                        errorLine = "ERROR: wrong semester to cycle on for scheduling";
                                        okSchedule = false;
                                        break;
                                    }
                                }
                                if (okSchedule) {
                                    examPlanning.outputSessionFile(fileNameFromCommandLine, i,
                                                                   itDatabaseOfExamSession->second[i * 2]);
                                    examPlanning.outputWarningFile(fileNameFromCommandLine, i);
                                }
                                i++;
                            } else {
                                okSchedule = false;
                            }
                        }
                        break;
                    } else {
                        errorLine = "ERROR: one or more database's file/s are missing\n" + errorLine;
                    }
                }
            }
            default: {
                errorIdentifier = ERR_wrong_identifier;
                errorLine = "ERROR: no matching action for command identifier: " + commandIdentifier;
                break;
            }
        }
    }
    if ((funcReturnDbFile != OK) || (functionReturn != OK) || (errorIdentifier != OK) || !okSchedule) {
        cerr << errorLine;
    } else {
        cout << "program ended successfully";
    }
    return 0;
}
