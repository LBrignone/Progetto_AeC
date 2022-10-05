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
#include "findSomethingInList.h"

using namespace std;

int main(int argc, char** argv) {
    map<Date, vector<Date>> examSession;
    list<Student> ListOfStudents;
    list<Professor> ListOfProfessors;
    list<Classroom> ListOfClassrooms;
    list<Course> ListOFCourses;
    list<CourseOfStudy> ListOfCoursesOfStudy;


    if (argc != 2) {
        cerr << "numero di argomenti passati diverso dal numero richiesto";
        return -1;
    }

    string inputFromCommandLine = argv[1];
    string fileNameFormCommandLine = inputFromCommandLine.substr(5, (inputFromCommandLine.size() - 5));
    switch (inputFromCommandLine[1]) {
        case 'a': {
            switch (inputFromCommandLine[3]) {
                case 's':{
                    break;
                }
                case 'd':{
                    break;
                }
                case 'a':{
                    break;
                }
                case 'c':{
                    break;
                }
                case 'f':{
                    break;
                }
                default:{
                    break;
                }
            }
            break;
        }
        case 'u': {
            switch (inputFromCommandLine[3]) {
                case 's':{
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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
