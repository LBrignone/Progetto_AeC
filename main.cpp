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


using namespace std;

int main(int argc, char** argv) {
    t_errorCodes errorIdentifier;
    int functionReturn;
    string errorLine;
    map<Date, vector<Date>> examSession;
    list<Student> listOfStudents;
    list<Professor> listOfProfessors;
    list<Classroom> listOfClassrooms;
    list<Course> listOfCourses;
    list<CourseOfStudy> listOfCoursesOfStudy;

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
                    if (inputFromCommandLine == studentDatabaseName) {
                        functionReturn = StudentInputFile(errorLine, inputFromCommandLine, listOfStudents, true);
                    } else {
                        functionReturn = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if (functionReturn == 0) {
                            functionReturn = StudentInputFile(errorLine, inputFromCommandLine, listOfStudents, false);
                        }
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
                        functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, listOfStudents);
                    }
                    break;
                }
                case 'd':{
                    if (inputFromCommandLine == professorDatabaseName) {
                        functionReturn = ProfessorInputFile(errorLine, inputFromCommandLine, listOfProfessors, true);
                    } else {
                        functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if (functionReturn == 0) {
                            functionReturn = ProfessorInputFile(errorLine, inputFromCommandLine, listOfProfessors, false);
                        }
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
                        functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, listOfProfessors);
                    }
                    break;
                }
                case 'a':{
                    if (inputFromCommandLine == classroomDatabaseName) {
                        functionReturn = ClassroomInputFile(errorLine, inputFromCommandLine, listOfClassrooms, true);
                    } else {
                        functionReturn = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if (functionReturn == 0) {
                            functionReturn = ClassroomInputFile(errorLine, inputFromCommandLine, listOfClassrooms, false);
                        }
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
                        functionReturn = updateClassroomDatabaseFile(errorLine, classroomDatabaseName, listOfClassrooms);
                    }
                    break;
                }
                case 'c':{
                    // it is necessary to recall in first place the professor's database, because it will be used when reading the course's database
                    // and perform proper controls
                    ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                    if (inputFromCommandLine == courseDatabaseName) {
                        functionReturn = CourseInputFile(errorLine, inputFromCommandLine, listOfCourses, listOfProfessors, true);
                    } else {
                        functionReturn = CourseInputFile(errorLine, courseDatabaseName, listOfCourses, listOfProfessors,  true);
                        if (functionReturn == 0) {
                            functionReturn = CourseInputFile(errorLine, inputFromCommandLine, listOfCourses, listOfProfessors, false);
                        }
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
                        functionReturn = updateCourseDatabaseFile(errorLine, courseDatabaseName, listOfCourses);
                    }
                    break;
                }
                case 'f':{
                    if (inputFromCommandLine == courseOfStudyDatabaseName) {
                        functionReturn = CourseOfStudyInputFile(errorLine, inputFromCommandLine, listOfCoursesOfStudy, true);
                    } else {
                        functionReturn = CourseOfStudyInputFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy, true);
                        if (functionReturn == 0) {
                            functionReturn = CourseOfStudyInputFile(errorLine, inputFromCommandLine, listOfCoursesOfStudy, false);
                        }
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
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
                    if (inputFromCommandLine != studentDatabaseName) {
                        functionReturn = StudentInputFile(errorLine, studentDatabaseName, listOfStudents, true);
                        if (functionReturn == numeric_limits<unsigned int>::max()) {
                            functionReturn = StudentToUpdateFile(errorLine, courseOfStudyDatabaseName, listOfStudents);
                        } else {
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update  \"db_studenti.txt\"  without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"db_studenti.txt\" with the same database file";
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
                        functionReturn = updateStudentDatabaseFile(errorLine, studentDatabaseName, listOfStudents);
                    }
                    break;
                }
                case 'd':{
                    if (inputFromCommandLine != professorDatabaseName) {
                        functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if (functionReturn == numeric_limits<unsigned int>::max()) {
                            functionReturn = ProfessorToUpdateFile(errorLine, professorDatabaseName, listOfProfessors);
                        } else {
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update \"db_professori.txt\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"db_professori.txt\" with the same database file";
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
                        functionReturn = updateProfessorDatabaseFile(errorLine, professorDatabaseName, listOfProfessors);
                    }
                    break;
                }
                case 'a':{
                    if (inputFromCommandLine != courseDatabaseName) {
                        functionReturn = ClassroomInputFile(errorLine, classroomDatabaseName, listOfClassrooms, true);
                        if (functionReturn == numeric_limits<unsigned int>::max()) {
                            functionReturn = ClassroomToUpdateFile(errorLine, classroomDatabaseName, listOfClassrooms);
                        } else {
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update \"db_aule.txt\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't update \"db_corsi.txt\" with the same database file";
                    }
                    if (functionReturn == numeric_limits<unsigned int>::max()) {
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
                    if (inputFromCommandLine != classroomDatabaseName) {
                        functionReturn = ProfessorInputFile(errorLine, professorDatabaseName, listOfProfessors, true);
                        if (functionReturn == numeric_limits<unsigned int>::max()) {
                            functionReturn = ClassroomToUpdateFile(errorLine, classroomDatabaseName, listOfClassrooms);
                        } else {
                            errorIdentifier = ERR_open_file;
                            errorLine = "Error: impossible to update \"db_aule.txt\" without database to start from";
                        }
                    } else {
                        errorIdentifier = ERR_update_database;
                        errorLine = "Error: can't insert or modify a course in \"db_corsi.txt\" with the same database file";
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
    if ((functionReturn != numeric_limits<unsigned int>::max()) || errorIdentifier) {
        cerr << errorLine;
    } else {
        cout << "program ended successfully";
    }
    return 0;
}
