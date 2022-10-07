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
                        updateStudentDatabaseFile(errorLine, studentDatabaseName, listOfStudents);
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
                    break;
                }
                default:{
                    errorLine = "Error: no matching actions for command identifier: " + inputFromCommandLine.substr(0, 4);
                    break;
                }
            }
            break;
        }
        case 'u': {
            switch (inputFromCommandLine[3]) {
                case 's':{
                    if (inputFromCommandLine != studentDatabaseName) {
                        functionReturn = StudentToUpdateFile(errorLine, courseOfStudyDatabaseName, listOfCoursesOfStudy, true);
                        if (functionReturn == 0) {
                            functionReturn = CourseOfStudyInputFile(errorLine, inputFromCommandLine, listOfCoursesOfStudy, false);
                        }
                    } else {
                        errorLine = "Error: can't update \"db_studenti.txt\" with the same database file"
                    }
                    break;
                }
                case 'd':{
                    break;
                }
                case 'a':{
                    break;
                }
                default:{
                    break;
                }
            }
            break;
        }
        case 'i': {
            switch (inputFromCommandLine[3]) {
                case 'c':{
                    break;
                }
                default:{
                    break;
                }
            }
            break;
        }
        case 's':{
            break;
        }
        case 'g':
        default: {
            break;
        }
    }
    if (functionReturn != numeric_limits<unsigned int>::max()) {
        cerr << errorLine;
    } else {
        cout << "program ended successfully";
    }
    return 0;
}
