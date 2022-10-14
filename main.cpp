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
#include "SchedulingHandling.h"
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
    t_errorCodes errorIdentifier;
    int functionReturn = OK;
    string commandIdentifier, actionIdentifier, fileNameFromCommandLine, academicYearFromCommandLine, academicYearFromCommandLineAndExamPeriod;
    string errorLine;
    list<Student> listOfStudents;
    list<Professor> listOfProfessors;
    list<Classroom> listOfClassrooms;
    list<Course> listOfCourses;
    list<CourseOfStudy> listOfCoursesOfStudy;
    map<Date, vector<Date>> mapOfExamSession;
    map<Date, map<Date, vector<examScheduled>>> mapExamPlanning;

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
                        functionReturn = StudentInputFile(errorLine, fileNameFromCommandLine, listOfStudents, true);
                    } else {
                        functionReturn = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if ((functionReturn == OK) || (functionReturn == ERR_open_file) || (functionReturn == ERR_empty_file)) {
                            functionReturn = StudentInputFile(errorLine, fileNameFromCommandLine, listOfStudents, false);
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, listOfStudents);
                    }
                    break;
                }
                case 'd':{
                    if (fileNameFromCommandLine == professorDatabaseName) {
                        functionReturn = ProfessorInputFile(errorLine, fileNameFromCommandLine, listOfProfessors, true);
                    } else {
                        functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if ((functionReturn == OK) || (functionReturn == ERR_open_file) || (functionReturn == ERR_empty_file)) {
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
                        functionReturn = ClassroomInputFile(errorLine, fileNameFromCommandLine, listOfClassrooms, true);
                    } else {
                        functionReturn = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if ((functionReturn == OK) || (functionReturn == ERR_open_file) || (functionReturn == ERR_empty_file)) {
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
                    // and perform proper controls
                    ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                    if (fileNameFromCommandLine == courseDatabaseName) {
                        functionReturn = CourseInputFile(errorLine, fileNameFromCommandLine, listOfCourses, listOfProfessors, true);
                    } else {
                        functionReturn = CourseInputFile(errorLine, courseDatabaseName, listOfCourses, listOfProfessors,  true);
                        if ((functionReturn == OK) || (functionReturn == ERR_open_file) || (functionReturn == ERR_empty_file)) {
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
                        functionReturn = CourseOfStudyInputFile(errorLine, fileNameFromCommandLine, listOfCoursesOfStudy, true);
                    } else {
                        functionReturn = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy, true);
                        if ((functionReturn == OK) || (functionReturn == ERR_open_file) || (functionReturn == ERR_empty_file)) {
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
                        functionReturn = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if (functionReturn == OK) {
                            functionReturn = StudentToUpdateFile(errorLine, fileNameFromCommandLine, listOfStudents);
                        } else {
                            errorLine += "\nImpossible to update  \"db_studenti.txt\"  without database to start from";
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
                        functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if (functionReturn == OK) {
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
                        functionReturn = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if (functionReturn == OK) {
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
                    functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                    if ((functionReturn == OK) || (functionReturn == ERR_open_file) || (functionReturn == ERR_empty_file)){
                        functionReturn = CourseInputFile(errorLine, courseDatabaseName, listOfCourses, listOfProfessors, true);
                        if (functionReturn == OK) {
                            functionReturn = CourseToInsertFile(errorLine, fileNameFromCommandLine, listOfCourses, listOfProfessors);
                        } else {
                            errorLine += "\nCan't perform an insertion or modification without the course's database file \"" + (string) courseDatabaseName + "\"";
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, listOfCourses);
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
                schedulingInitializer(errorLine, i, );
            }
            break;
        }
        default: {
            errorIdentifier = ERR_wrong_identifier;
            errorLine = "Error: no matching action for command identifier: " + commandIdentifier;
            break;
        }
    }
    if ((functionReturn != OK) || errorIdentifier) {
        cerr << errorLine;
    } else {
        cout << "program ended successfully";
    }
    return 0;
}
