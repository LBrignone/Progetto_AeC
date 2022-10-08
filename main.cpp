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
#define examSessionPeriods "db_periodi_esami.txt"

using namespace std;

int main(int argc, char** argv) {
    t_errorCodes errorIdentifier;
    int functionReturn = OK;
    string errorLine;
    list<Student> listOfStudents;
    list<Professor> listOfProfessors;
    list<Classroom> listOfClassrooms;
    list<Course> listOfCourses;
    list<CourseOfStudy> listOfCoursesOfStudy;
    map<Date, vector<Date>> examSession;

    if (argc != 2) {
        cerr << "numero di argomenti passati diverso dal numero richiesto";
        return -1;
    }
    string inputFromCommandLine = argv[1];
    string fileNameFromCommandLine = inputFromCommandLine.substr(5, (inputFromCommandLine.size() - 5));
    switch (inputFromCommandLine[1]) {
        case 'a': {
            switch (inputFromCommandLine[3]) {
                case 's':{
                    if (fileNameFromCommandLine == studentDatabaseName) {
                        functionReturn = StudentInputFile(errorLine, fileNameFromCommandLine, listOfStudents, true);
                    } else {
                        functionReturn = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if (functionReturn == 0) {
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
                        if (functionReturn == 0) {
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
                        if (functionReturn == 0) {
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
                        if (functionReturn == 0) {
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
                        if (functionReturn == 0) {
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
                    errorLine = "Error: no matching action for command identifier: " + inputFromCommandLine.substr(0, 4);
                    break;
                }
            }
            break;
        }
        case 'u': {
            switch (inputFromCommandLine[3]) {
                case 's':{
                    if (fileNameFromCommandLine != studentDatabaseName) {
                        functionReturn = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if (functionReturn == OK) {
                            functionReturn = StudentToUpdateFile(errorLine, fileNameFromCommandLine, listOfStudents);
                        } else {
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update  \"db_studenti.txt\"  without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"db_studenti.txt\" with the same database file";
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
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update \"db_professori.txt\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"db_professori.txt\" with the same database file";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, listOfProfessors);
                    }
                    break;
                }
                case 'a':{
                    if (fileNameFromCommandLine != courseDatabaseName) {
                        functionReturn = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if (functionReturn == OK) {
                            functionReturn = ClassroomToUpdateFile(errorLine, fileNameFromCommandLine, listOfClassrooms);
                        } else {
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update \"db_aule.txt\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"db_corsi.txt\" with the same database file";
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateClassroomDatabaseFile(errorLine, classroomDatabaseName, listOfClassrooms);
                    }
                    break;
                }
                default:{
                    errorIdentifier = ERR_wrong_identifier;
                    errorLine = "Error: no matching action for command identifier: " + inputFromCommandLine.substr(0, 4);
                    break;
                }
            }
            break;
        }
        case 'i': {
            switch (inputFromCommandLine[3]) {
                case 'c':{
                    // the existence of professor's database is not a constraint for the insertion or modification of courses,
                    // so the return is checked only for file correctness
                    functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                    if ((functionReturn == OK) || (functionReturn == ERR_open_file)){
                        functionReturn = CourseInputFile(errorLine, courseDatabaseName, listOfCourses, listOfProfessors, true);
                        if (functionReturn == OK) {
                            functionReturn = CourseToInsertFile(errorLine, fileNameFromCommandLine, listOfCourses, listOfProfessors);
                        } else {
                            errorLine = "Error: can't perform an insertion or modification without the course's database file \"db_corsi.txt\"";
                        }
                    }
                    if (functionReturn == OK) {
                        functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, listOfCourses);
                    }
                    break;
                }
                default:{
                    errorIdentifier = ERR_wrong_identifier;
                    errorLine = "Error: no matching action for command identifier: " + inputFromCommandLine.substr(0, 4);
                    break;
                }
            }
            break;
        }
        case 's':{
            functionReturn = ExamSessionInputFile(errorLine, examSessionPeriods, examSession, true);
            if (functionReturn == OK) {
                functionReturn = ExamSessionInputFile(errorLine, fileNameFromCommandLine, examSession, false);
            }
            break;
        }
        case 'g':{
            break;
        }
        default: {
            errorIdentifier = ERR_wrong_identifier;
            errorLine = "Error: no matching action for command identifier: " + inputFromCommandLine.substr(0, 4);
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
