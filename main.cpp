#include <map>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
    int functionReturn = OK, funcReturnDbFile = OK;
    string commandIdentifier, actionIdentifier, fileNameFromCommandLine, academicYearFromCommandLine, academicYearFromCommandLineAndExamPeriod;
    string errorLine;
    list<Student> listOfStudents;
    list<Professor> listOfProfessors;
    list<Classroom> listOfClassrooms;
    list<Course> listOfCourses;
    list<CourseOfStudy> listOfCoursesOfStudy;
    map<Date, vector<Date>> mapOfExamSession;

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
                if (i != 4) {
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

    switch (commandIdentifier[1]) {
        case 'a': {
            switch (commandIdentifier[3]) {
                case 's':{
                    if (fileNameFromCommandLine == studentDatabaseName) {
                        funcReturnDbFile = StudentInputFile(errorLine, fileNameFromCommandLine, listOfStudents, true);
                    } else {
                        funcReturnDbFile = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                            functionReturn = StudentInputFile(errorLine, fileNameFromCommandLine, listOfStudents, false);
                        }
                    }
                    if (functionReturn == OK || functionReturn == ERR_not_found) {
                        functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, listOfStudents);
                    }
                    break;
                }
                case 'd':{
                    if (fileNameFromCommandLine == professorDatabaseName) {
                        funcReturnDbFile = ProfessorInputFile(errorLine, fileNameFromCommandLine, listOfProfessors, true);
                    } else {
                        funcReturnDbFile = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                            functionReturn = ProfessorInputFile(errorLine, fileNameFromCommandLine, listOfProfessors, false);
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, listOfProfessors);
                    }
                    break;
                }
                case 'a':{
                    if (fileNameFromCommandLine == classroomDatabaseName) {
                        funcReturnDbFile = ClassroomInputFile(errorLine, fileNameFromCommandLine, listOfClassrooms, true);
                    } else {
                        funcReturnDbFile = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                            functionReturn = ClassroomInputFile(errorLine, fileNameFromCommandLine, listOfClassrooms, false);
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateClassroomDatabaseFile(errorLine, classroomDatabaseName, listOfClassrooms);
                    }
                    break;
                }
                case 'c':{
                    // it is necessary to recall in first place the professor's database, because it will be used when reading the course's database
                    // and perform proper controls, BUT if the file exists or not is not a binding condition
                    ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                    if (fileNameFromCommandLine == courseDatabaseName) {
                        funcReturnDbFile = CourseInputFile(errorLine, fileNameFromCommandLine, listOfCourses, listOfProfessors, true);
                    } else {
                        funcReturnDbFile = CourseInputFile(errorLine, courseDatabaseName, listOfCourses, listOfProfessors,  true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                            functionReturn = CourseInputFile(errorLine, fileNameFromCommandLine, listOfCourses, listOfProfessors, false);
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, listOfCourses);
                    }
                    break;
                }
                case 'f':{
                    if (fileNameFromCommandLine == courseOfStudyDatabaseName) {
                        funcReturnDbFile = CourseOfStudyInputFile(errorLine, fileNameFromCommandLine, listOfCoursesOfStudy, true);
                    } else {
                        funcReturnDbFile = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy, true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                            functionReturn = CourseOfStudyInputFile(errorLine, fileNameFromCommandLine, listOfCoursesOfStudy, false);
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateCourseOfStudyDatabaseFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy);
                    }
                    break;
                }
                default:{
                    errorIdentifier = ERR_wrong_identifier;
                    errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
                    break;
                }
            }
            break;
        }
        case 'u': {
            switch (commandIdentifier[3]) {
                case 's':{
                    if (fileNameFromCommandLine != studentDatabaseName) {
                        funcReturnDbFile = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if (funcReturnDbFile == OK) {
                            functionReturn = StudentToUpdateFile(errorLine, fileNameFromCommandLine, listOfStudents);
                        } else {
                            errorLine += "\nImpossible to update  \"" + (string) studentDatabaseName + "\"  without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"" + (string) studentDatabaseName + "\" with the same database file";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, listOfStudents);
                    }
                    break;
                }
                case 'd':{
                    if (fileNameFromCommandLine != professorDatabaseName) {
                        funcReturnDbFile = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if (funcReturnDbFile == OK) {
                            functionReturn = ProfessorToUpdateFile(errorLine, fileNameFromCommandLine, listOfProfessors);
                        } else {
                            errorLine += "\nImpossible to update \"" + (string) professorDatabaseName + "\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"" + (string) professorDatabaseName + "\" with the same database file";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, listOfProfessors);
                    }
                    break;
                }
                case 'a':{
                    if (fileNameFromCommandLine != classroomDatabaseName) {
                        funcReturnDbFile = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if (funcReturnDbFile == OK) {
                            functionReturn = ClassroomToUpdateFile(errorLine, fileNameFromCommandLine, listOfClassrooms);
                        } else {
                            errorLine += "\nImpossible to update \"" + (string)classroomDatabaseName + "\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"" + (string) courseDatabaseName + "\" with same database file";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateClassroomDatabaseFile(errorLine, classroomDatabaseName, listOfClassrooms);
                    }
                    break;
                }
                default:{
                    errorIdentifier = ERR_wrong_identifier;
                    errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
                    break;
                }
            }
            break;
        }
        case 'i': {
            switch (commandIdentifier[3]) {
                case 'c':{
                    // the existence of professor's database is not a constraint for the insertion or modification of courses,
                    // so the return is checked only for file correctness
                    funcReturnDbFile = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                    if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                        // also the presence of course of study's database isn't a constraint to the correct functioning of
                        // courses insertion, but if it is present it is necessary to perform some actions on itself too
                        // if a course is set as "non_attivo" if the same course is used in some course of study then:
                        // - if all other academic years, for that same course is "attivo" then in course of study that course is
                        //   COPIED in non-active list
                        // - if all years for which is defined are "non_attivo" then it is REMOVED from its semester and inserted
                        //   in non-active list
                        funcReturnDbFile = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy, true);
                        if ((funcReturnDbFile == OK) || (funcReturnDbFile == ERR_open_file) || (funcReturnDbFile == ERR_empty_file)) {
                            funcReturnDbFile = CourseInputFile(errorLine, courseDatabaseName, listOfCourses, listOfProfessors, true);
                            if (funcReturnDbFile == OK) {
                                functionReturn = CourseToInsertFile(errorLine, fileNameFromCommandLine, listOfCourses, listOfProfessors, listOfCoursesOfStudy);
                            } else {
                                errorLine += "\nCan't perform an insertion or modification without the course's database file \"" +
                                             (string) courseDatabaseName + "\"";
                            }
                        } else {
                            errorLine += "\nCan't perform the insertion command, because the file \"" + (string) courseOfStudyDatabaseName +
                                         "\" has been found corrupted";
                        }
                    } else {
                        errorLine += "\nCan't perform the insertion command, because the file \"" + (string) courseOfStudyDatabaseName +
                                     "\" has been found corrupted";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, listOfCourses);
                        if (functionReturn == OK) {
                            functionReturn = updateCourseOfStudyDatabaseFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy);
                        } else {
                            errorLine += "\nCan't update the " + (string) courseOfStudyDatabaseName + " due to an error updating " + (string) courseDatabaseName;
                        }
                    }
                    break;
                }
                default:{
                    errorIdentifier = ERR_wrong_identifier;
                    errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
                    break;
                }
            }
            break;
        }
        case 's':{
            if (actionIdentifier == "current_a") {
                functionReturn = ExamSessionInputFile(errorLine, examSessionPeriodsDatabaseName, mapOfExamSession, true);
                if ((functionReturn == OK) && (fileNameFromCommandLine != examSessionPeriodsDatabaseName)) {
                    functionReturn = ExamSessionInputFile(errorLine, academicYearFromCommandLineAndExamPeriod, mapOfExamSession, false);
                } else {
                    errorIdentifier = ERR_file_name;
                    errorLine += "\nCan't proceed updating \"" + (string) examSessionPeriodsDatabaseName + "\" with same database file";
                }
                if (functionReturn == OK) {
                    functionReturn = updateExamSessionDatabaseFile(errorLine, examSessionPeriodsDatabaseName, mapOfExamSession);
                }
            } else if (actionIdentifier == "set_availability"){
                functionReturn = ProfessorUnavailabilityInputFile(errorLine, unavailabilityDatabaseFile, listOfProfessors, "", true);
                if ((functionReturn == OK) && (fileNameFromCommandLine != examSessionPeriodsDatabaseName)) {
                    functionReturn = ProfessorUnavailabilityInputFile(errorLine, fileNameFromCommandLine, listOfProfessors, academicYearFromCommandLine,false);
                } else {
                    errorIdentifier = ERR_file_name;
                    errorLine += "\nCan't update \"" + (string) unavailabilityDatabaseFile + "\" with same database file";
                }
                if (functionReturn == OK) {
                    functionReturn = updateUnavailabilityDatabaseFile(errorLine, unavailabilityDatabaseFile, listOfProfessors);
                }
            } else {
                errorIdentifier = ERR_wrong_identifier;
                errorLine = "Error: no matching action for command identifier: " + commandIdentifier + " " + actionIdentifier;
            }
            break;
        }
        case 'g':{
            for (int i = 0; i < 3; i++) {
            }
            break;
        }
        default: {
            errorIdentifier = ERR_wrong_identifier;
            errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
            break;
        }
    }
    if (((funcReturnDbFile != OK) && (funcReturnDbFile != ERR_open_file)) || (functionReturn != OK) || (errorIdentifier != OK)) {
        cerr << errorLine;
    } else {
        cout << "program ended successfully";
    }
    return 0;
}
