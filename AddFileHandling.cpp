//
// Created by Luca Brignone on 22/08/22.
//

#include "AddFileHandling.h"

int StudentInputFile (string& errorHandling, const string& studentsFileName, list<Student>& studentList, const bool& isDb) {
    ifstream fileName;
    string readFromLine, readFromFile;
    int lineOfFile = 0, patterField = 0;
    bool errorInFormat = false;

    fileName.open(studentsFileName, 'r');
    if (!fileName.is_open()) {
        errorHandling = "Error: file: " + studentsFileName + " not found.";
        return (int)ERR_open_file;
    } else {
        while ((getline(fileName , readFromFile)) && !errorInFormat) {
            stringstream tmp(readFromFile);
            Student dummyStudent;

            while((getline(tmp, readFromLine, ';')) && !errorInFormat) {
                switch (patterField) {
                    case 0:{
                        if (isDb) {
                            if (!dummyStudent.setId(readFromLine)) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " incorrect id element: " + readFromLine;
                            } else {
                                if (!studentList.empty()) {
                                    if (dummyStudent < studentList.back()) {
                                        errorInFormat = true;
                                        errorHandling =
                                                "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " inchoerent id element: " + readFromLine;
                                    }
                                }
                            }
                        } else {
                            if (studentList.empty()) {
                                if (dummyStudent.generateNewId("")) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                                }
                            } else {
                                if (dummyStudent.generateNewId(studentList.back().getId())) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                                }
                            }
                        }
                        break;
                    }
                    case 1:{
                        dummyStudent.setName(readFromLine);
                        break;
                    }
                    case 2:{
                        dummyStudent.setSurname(readFromLine);
                        break;
                    }
                    case 3:{
                        if (!dummyStudent.setMail(readFromLine)) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " incorrect mail element: " + readFromLine;
                        }
                        break;
                    }
                    default:{
                        errorInFormat = true;
                        errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " unexpected element number greater than " + to_string(4);
                    }
                }
                patterField++;
            }
            if(patterField == 4)
            {
                studentList.push_back(dummyStudent);
                patterField = 0;
            } else {
                errorInFormat = true;
                errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " unexpected element number less than " + to_string(4);
            }
            lineOfFile++;
        }
    }
    if((errorInFormat)) {
        return (int) ERR_file_format;
    } else {
        return (int) OK;
    }
}

int ProfessorInputFile(string& errorHandling, const string& professorFileName, list<Professor>& professorList, const bool& isDb) {
    ifstream fileName;
    string readFromFile, readFromLine;
    int lineOfFile = 0, patternField = 0;
    bool errorInFormat = false, profIdExist = false;
    list<Professor>::iterator itOFProfessorList;

    fileName.open(professorFileName, 'r');
    if (!fileName.is_open()) {
        errorHandling = "Error: file: " + professorFileName + " not found.";
        return (int)ERR_open_file;
    } else {
        while ((getline(fileName , readFromFile)) && !errorInFormat) {
            stringstream tmp(readFromFile);
            Professor dummyProfessor;

            if (isDb) {
                patternField = 1;
            } else {
                patternField = 0;
            }
            while((getline(tmp, readFromLine, ';')) && !errorInFormat) { // continua se non ho raggiunto la fine del file e NON ho errori di formato

                switch (patternField) {
                    case 0:{
                        if (!dummyProfessor.setId(readFromLine)) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                        } else {
                            if (!professorList.empty()) { // se la lista non è vuota allora
                                if (dummyProfessor < professorList.back()) { // verifico l'ordinamennto corretto degli id: se l'ultimo id della lista è maggiore (>) di quello che vogli inserire do errore
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " inchoerent id element: " + readFromLine;
                                }
                            }
                        }




                            //if (professorList.empty()) {
                            //    if (!dummyProfessor.generateNewId("")) {
                            //        errorInFormat = true;
                            //        errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                            //    }
                            //} else {
                            //    if (!dummyProfessor.generateNewId(professorList.back().getId())) {
                            //        errorInFormat = true;
                            //        errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                            //    }
                            //}
                        break;
                    }
                    case 1:{
                        dummyProfessor.setName(readFromLine);
                        break;
                    }
                    case 2:{
                        dummyProfessor.setSurname(readFromLine);
                        break;
                    }
                    case 3:{
                        if (!dummyProfessor.setMail(readFromLine)) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " incorrect mail element: " + readFromLine;
                        }
                        break;
                    }
                    default:{
                        errorInFormat = true;
                        errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number greater than " + to_string(4);
                    }
                }
                patternField++;
            }
            if(patternField == 4) {
                if (isDb) {
                    professorList.push_back(dummyProfessor);
                } else {
                    dummyProfessor.setId("d000001");
                    while (!profIdExist) {
                        itOFProfessorList = findProfessor(professorList, dummyProfessor.getId());
                        if (itOFProfessorList != professorList.end()){
                            if (!itOFProfessorList->getMail().empty()){
                                dummyProfessor++;
                            } else {
                                itOFProfessorList->setName(dummyProfessor.getName());
                                itOFProfessorList->setSurname(dummyProfessor.getSurname());
                                itOFProfessorList->setMail(dummyProfessor.getMail());
                                profIdExist = true;
                            }
                        } else {
                            professorList.push_back(dummyProfessor);
                            profIdExist = true;
                        }
                    }
                }
            } else {
                errorInFormat = true;
                errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number less than " + to_string(4);
            }
            lineOfFile++;
        }
    }
    if (errorInFormat) {
        return (int) ERR_file_format;
    } else {
        return (int) OK;
    }
}

int ClassroomInputFile(string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList, const bool& isDb) {
    ifstream fileName;
    string readFromFile, readFromLine;
    int lineOfFile = 0, patterField = 0;
    bool errorInFormat = false;

    fileName.open(classroomFileName, 'r');
    if (!fileName.is_open()) {
        errorHandling = "Error: file: " + classroomFileName + " not found.";
        return (int) ERR_open_file;
    } else {
        while ((getline(fileName, readFromFile)) && !errorInFormat) {
            stringstream tmp(readFromFile);
            Classroom dummyClassroom;

            while ((getline(tmp, readFromLine, ';')) && !errorInFormat) {
                switch (patterField) {
                    case 0:{
                        if (isDb) {
                            if (!dummyClassroom.setId(readFromLine)) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                            } else {
                                if (!classroomList.empty()) {
                                    if (dummyClassroom < classroomList.back()) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + classroomFileName + " row: "+ to_string(lineOfFile + 1) + " inchoerent id element: " + readFromLine;
                                    }
                                }
                            }
                        } else {
                            if (classroomList.empty()){ // se la lista di aule (il database in memoria) non è vuoto
                                if (!dummyClassroom.generateNewId("")) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                                }
                            } else {
                                if (!dummyClassroom.generateNewId(classroomList.back().getId())) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                                }
                            }
                        }
                        break;
                    }
                    case 1:{
                        if (!dummyClassroom.setType(readFromLine[0])){
                            errorInFormat = true;
                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " incorrect classroom type element: " + readFromLine;
                        }
                        break;
                    }
                    case 2:{
                        dummyClassroom.setClassroomName(readFromLine);
                        break;
                    }
                    case 3:{
                        if (!dummyClassroom.setCapacity(stoi(readFromLine))) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " incorrect classroom capacity element: " + readFromLine;
                        }
                        break;
                    }
                    case 4:{
                        if (!dummyClassroom.setExamCapacity(stoi(readFromLine))) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " incorrect classroom exam capacity element: " + readFromLine;
                        }
                        break;
                    }
                    default:{
                        errorInFormat = true;
                        errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number greater than: " + to_string(4);
                        break;
                    }
                }
                patterField++;
            }
            lineOfFile++;
            if (patterField == 4) {
                classroomList.push_back(dummyClassroom);
                patterField = 0;
            } else {
                errorInFormat = true;
                errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number less than: " + to_string(4);
            }
        }
    }
    if (errorInFormat) {
        return (int) ERR_file_format;
    } else {
        return (int) OK;
    }
}

int CourseInputFile(string& errorHandling, const string& courseFileName, list<Course>& courseList, const list<Professor>& professorList, const bool& isDb) {
    ifstream fileName;
    string readFromFile, readFromLine;
    int lineOfFile = 0, patternField = 0;
    bool errorInFormat = false, errorIncoherentHour = false;

    fileName.open(courseFileName, 'r');
    if (!fileName.is_open()) {
        errorHandling = "Error: file: " + courseFileName + " not found.";
        return (int) ERR_open_file;
    } else {
        if (isDb) {
            while ((getline(fileName, readFromFile)) && !errorInFormat && !errorIncoherentHour) {
                Course dummyCourse;
                stringstream tmp(readFromFile);
                stringstream associateProfessorListFormDb;

                if(getline(tmp, readFromLine, ';')){
                    if(readFromLine == "c") {
                        while ((getline(tmp, readFromLine, ';')) && !errorInFormat) {
                            switch (patternField) {
                                case 0: {
                                    if (!dummyCourse.setId(readFromLine)) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect id element: " + readFromLine;
                                    }
                                    break;
                                }
                                case 1: {
                                    dummyCourse.setTitle(readFromLine);
                                    break;
                                }
                                case 2: {
                                    try {
                                        if (!dummyCourse.setCfu(stoi(readFromLine))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of cfu is below 0 (zero): " + readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert cfu field to int: " + readFromLine;
                                    }
                                    break;
                                }
                                case 3: {
                                    try {
                                        if (!dummyCourse.setCourseLessonH(stoi(readFromLine))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of lesson hour is below 0 (zero): " + readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert lesson hour field to int: " + readFromLine;
                                    }
                                    break;
                                }
                                case 4: {
                                    try {
                                        if (!dummyCourse.setCourseExerciseH(stoi(readFromLine))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of exercise hour is below 0 (zero): " + readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert exercise hour field to int: " + readFromLine;
                                    }
                                    break;
                                }
                                case 5: {
                                    try {
                                        if (!dummyCourse.setCourseLabH(stoi(readFromLine))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of laboratory hour is below 0 (zero): " + readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert laboratory hour field to int: " + readFromLine;
                                    }
                                    break;
                                }
                                default: {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number greater than: " + to_string(7);
                                    break;
                                }
                            }
                            patternField++;
                        }
                    } else if(readFromLine == "a") {
                        string associateProfessorFromDb;

                        while ((getline(tmp, readFromLine, ';')) && !errorInFormat) {
                            switch (patternField) {
                                case 0: {
                                    try {
                                        if (!dummyCourse.setStartYear(stoi(readFromLine.substr(0, 4)))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given accademic year is below 0 (zero): " + readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert accademic year field to Date class (int): " + readFromLine;
                                    }
                                    break;
                                }
                                case 1: {
                                    if (readFromLine == "attivo") {
                                        dummyCourse.setActiveCourse(true);
                                    } else if (readFromLine == "non_attivo"){
                                        dummyCourse.setActiveCourse(false);
                                    } else {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given string doesn't idenfy if the course is or is not active: " + readFromLine;
                                    }
                                    break;
                                }
                                case 2: {
                                    try {
                                        if (!dummyCourse.setParallelCoursesNumber(stoi(readFromLine))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given number of parallel courses is below 0 (zero): " + readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the number of parallel version of the given course to int: " + readFromLine;
                                    }
                                    break;
                                }
                                case 3: {
                                    associateProfessorListFormDb.str() = readFromLine;
                                    break;
                                }
                                case 4: {
                                    string readExamOraganzation;
                                    stringstream strExamOrganization;
                                    int patternOfExamOrganization = 0;

                                    strExamOrganization.str() = readFromLine.substr(1, readFromLine.size() - 2);
                                    while (getline(strExamOrganization,readExamOraganzation, ',') && !errorInFormat) {
                                        switch (patternOfExamOrganization) {
                                            case 0:{
                                                try {
                                                    if (!dummyCourse.setExamDuration(stoi(readExamOraganzation))) {
                                                        errorInFormat = true;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exam duration is below 0 (zero): " + readExamOraganzation;
                                                    }
                                                }
                                                catch (const invalid_argument &excepFromStoi) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the exam duration field to int: " + readExamOraganzation + " (field number: " +
                                                            to_string(patternOfExamOrganization) + ")";
                                                }
                                                break;
                                            }
                                            case 1:{
                                                try {
                                                    if (!dummyCourse.setEntranceTime(stoi(readExamOraganzation))) {
                                                        errorInFormat = true;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given entrance time is below 0 (zero): " + readExamOraganzation;
                                                    }
                                                }
                                                catch (const invalid_argument &excepFromStoi) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert entrance time field to int: " + readExamOraganzation + " (field number: " +
                                                                    to_string(patternOfExamOrganization) + ")";
                                                }
                                                break;
                                            }
                                            case 2:{
                                                try {
                                                    if (!dummyCourse.setExitTime(stoi(readExamOraganzation))) {
                                                        errorInFormat = true;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exit time is below 0 (zero): " + readExamOraganzation;
                                                    }
                                                }
                                                catch (const invalid_argument &excepFromStoi) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert exit time field to int: " + readExamOraganzation + " (field number: " +
                                                                    to_string(patternOfExamOrganization) + ")";
                                                }
                                                break;
                                            }
                                            case 3:{
                                                if (!dummyCourse.setExamType(readExamOraganzation)) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exam type doesn't match the acronym set (S/SO/O/P): " + readExamOraganzation;
                                                }
                                                break;
                                            }
                                            case 4:{
                                                if (!dummyCourse.setExamClassroomType(readExamOraganzation[0])) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given classroom type doesn't match the acronym set (A/L): " + readExamOraganzation;
                                                }
                                                break;
                                            }
                                            case 5: {
                                                try {
                                                    if (!dummyCourse.setPartecipants(stoi(readExamOraganzation))) {
                                                        errorInFormat = true;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given number of students is below 0 (zero): " + readExamOraganzation;
                                                    }
                                                }
                                                catch (const invalid_argument &excepFromStoi) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the number of students field to int: " + readExamOraganzation + " (field number: " +
                                                                    to_string(patternOfExamOrganization) + ")";
                                                }
                                                break;
                                            }
                                            default:{
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number greater than: " + to_string(6);
                                            }
                                        }
                                        patternOfExamOrganization++;
                                    }
                                    break;
                                }
                                case 5: {
                                    string readGroupingCourses;
                                    stringstream strGroupingAssembly;

                                    strGroupingAssembly.str() = readFromLine.substr(1, readFromLine.size() - 2);
                                    while (getline(strGroupingAssembly,readGroupingCourses, ',') && !errorInFormat) {
                                        if (!dummyCourse.appendGroupedId(readGroupingCourses)) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given element of the grouped list of courses doesn't match the pattern (01XXXXX): " + readGroupingCourses;
                                        }
                                    }
                                    break;
                                }
                                default: {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number greater than: " + to_string(7);
                                    break;
                                }
                            }
                            patternField++;
                        }

 //-------------------> the string previously memorized (case 3 of main switch) is now processed, the following rows are all the variables
 //                     needed for that purpose
                        associateProfessorListFormDb.str().substr(1, associateProfessorListFormDb.str().size() - 2);
                        int  level = 0, levelIncrement = 0, levelDecrement = 0;
                        bool isLevelCorrect = false;
                        string mainProfessorCourse;
                        AssociateProfessor dummyAssociateProfessor;
                        Professor dummyProfessorFromNotFound;
                        list<AssociateProfessor> tmpAssociateProfessorList;
                        list<Professor> tmpProfessorList = professorList;
                        list<Professor>::iterator itReturnToFind;   //------------> ITERATORE
                        vector<int> patternFieldForEachLevel {0, 0, 0};
                            // first element of the vector: keeps memory of the pattern at LEVEL 1 (zero), so professor id, and vesion id
                            // second element of the vector: counts the number of times a new version of the course is registered
                            // third element of the vector: keeps memory of the pattern at LEVEL 3, so professor id, lesson hour, exercise hour and lab hour
                            // LEVEL 2 is discarded because doesn't have any meaningful information, due to it rapresentig the inner "[...]"

                        while (getline(associateProfessorListFormDb, associateProfessorFromDb, ',') && !errorInFormat && !errorIncoherentHour) {
                            levelIncrement=0;
                            levelDecrement=0;
                            isLevelCorrect = false;
                            while (!isLevelCorrect){
                                if (associateProfessorFromDb[0] == '[') {
                                    associateProfessorFromDb.substr(1, associateProfessorFromDb.size() - 1);
                                    levelIncrement++;
                                } else if (associateProfessorFromDb[0] == '{') {
                                    associateProfessorFromDb.substr(1, associateProfessorFromDb.size() - 1);
                                    levelIncrement++;
                                } else if (associateProfessorFromDb[associateProfessorFromDb.size() - 1] == '}') {
                                    associateProfessorFromDb.substr(0, associateProfessorFromDb.size() - 1);
                                    levelDecrement ++;
                                } else if (associateProfessorFromDb[associateProfessorFromDb.size() - 1] == ']') {
                                    associateProfessorFromDb.substr(0, associateProfessorFromDb.size() - 1);
                                    levelDecrement ++;
                                }else{
                                    isLevelCorrect = true;
                                }
                            }
                            level+=levelIncrement;

                            switch (level) {
                                case 1:{
                                    switch (patternFieldForEachLevel[level - 1] % 2) {
                                        case 0:{
                                            mainProfessorCourse = associateProfessorFromDb;
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 1:{
                                            if (!dummyCourse.setParallelCoursesId(associateProfessorFromDb)) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + "row: " + to_string(lineOfFile) + "the given version id is is not compatible with the pattern for that field (P000): " + associateProfessorFromDb;
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        default:{
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number there may be an incorrect number or type of brackets, plese controll the regular professor and version"
                                                            " id of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 2:{
                                    // this is necessary only for pattern conformity
                                    break;
                                }
                                case 3:{
                                    switch (patternFieldForEachLevel[level - 1] % 4) {
                                        case 0:{
                                            itReturnToFind = findProfessor(tmpProfessorList, associateProfessorFromDb);
                                            if (patternFieldForEachLevel[level - 1] == 0) {
                                                if (mainProfessorCourse == associateProfessorFromDb) {
                                                    dummyAssociateProfessor.setIsMain(true);
                                                    if (itReturnToFind != tmpProfessorList.end()) {
                                                        dummyAssociateProfessor.setProfessorPointer(itReturnToFind);
                                                    } else {
                                                        // creo e inserisco il professore non trovato nella lista dei professori, sarà da controllare nella lista dei professori
                                                        // se gli altri campi saranno compilati
                                                        if (!dummyProfessorFromNotFound.setId(associateProfessorFromDb)) {
                                                            errorInFormat = true;
                                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "incorrect professor id: " + associateProfessorFromDb;
                                                        }
                                                        tmpProfessorList.push_back(dummyProfessorFromNotFound);
                                                        itReturnToFind = findProfessor(tmpProfessorList, associateProfessorFromDb);
                                                        if (itReturnToFind != tmpProfessorList.end()) {
                                                            dummyAssociateProfessor.setProfessorPointer(itReturnToFind);
                                                        } else {
                                                            errorInFormat = true;
                                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "error ceeating the unexisting professor with id: " + associateProfessorFromDb;
                                                        }
                                                    }
                                                } else {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the regular professor for the version " + dummyCourse.getParallelCoursesId() + " is " + mainProfessorCourse + " which is "
                                                                    "different from the one on first place of  the course organization: " + associateProfessorFromDb;
                                                }
                                            } else {
                                                 dummyAssociateProfessor.setProfessorPointer(findProfessor(tmpProfessorList, associateProfessorFromDb));
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 1:{
                                            try {
                                                if (dummyAssociateProfessor.setLessonH(stoi(associateProfessorFromDb))) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given lesson hour is below 0 (zero): " + associateProfessorFromDb;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the lesson hour field to int: " + associateProfessorFromDb + " (field number: "
                                                                + to_string(patternFieldForEachLevel[level - 1]) + ", related to professor id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ")";
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 2:{
                                            try {
                                                if (dummyAssociateProfessor.setExerciseH(
                                                        stoi(associateProfessorFromDb))) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exercise hour is below 0 (zero): " + associateProfessorFromDb;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the exercise hour field to int: " + associateProfessorFromDb + " (field number: "
                                                                + to_string(patternFieldForEachLevel[level - 1]) + ", related to professor id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ")";
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 3:{

                                            try {
                                                if (dummyAssociateProfessor.setLabH(stoi(associateProfessorFromDb))) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given laboratory hour is below 0 (zero): " + associateProfessorFromDb;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the laboratory hour field to int: " + associateProfessorFromDb + " (field number: "
                                                                + to_string(patternFieldForEachLevel[level - 1]) + ", related to professor id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ")";
                                            }
                                            // faccio la prima push per riempire la lista dei professori associati
                                            if (!errorInFormat) {
                                                tmpAssociateProfessorList.push_back(dummyAssociateProfessor);
                                            }
                                            break;
                                        }
                                        default:{
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number there may be an incorrect number or type of brackets, plese controll the professor (id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ") and version (id: "
                                                            + dummyCourse.getParallelCoursesId() + "of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                            break;
                                        }
                                    }
                                    break;
                                }
                                default:{
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number there may be an incorrect number or type of brackets, plese controll the professor (id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ") and version (id: "
                                                    + dummyCourse.getParallelCoursesId() + "of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                    break;
                                }
                            }
                            level-=levelDecrement;
                            if (level == 0) {
                                patternFieldForEachLevel[2] = 0;
                                if (!errorInFormat) {
                                    if (dummyCourse.setListAssistant(tmpAssociateProfessorList, errorHandling) == 255){
                                        courseList.push_back(dummyCourse);
                                        tmpAssociateProfessorList.clear();
                                    } else {
                                        errorIncoherentHour = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incoherent number of hour, when pushing db temporary list, between the total ammount given to the course and the sum of those of the given professors";
                                    }
                                }
                            }
                        }
                    } else {
                        errorInFormat = true;
                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected starting character it is not \"c\" or \"a\"";
                    }
                    lineOfFile++;
                    patternField = 0;
                } else {
                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " can't recognise the substring of the pattern";
                }
            }
        } else {
//--------> when the given file is not a _db file, it is handled here
         // note that the rows are different from the _db file, but it has a similar structure given the commonality in the given fields
            stringstream associateProfessorListFormFile;
            string associateProfessorFromFile;

            while ((getline(fileName, readFromLine)) && !errorInFormat && !errorIncoherentHour) {
                stringstream tmp(readFromFile);
                Course dummyCourse;

                while ((getline(tmp, readFromLine, ';')) && !errorInFormat && !errorIncoherentHour) {
                    switch (patternField) {
                        case 0:{
                            try {
                                if (!dummyCourse.setStartYear(stoi(readFromLine.substr(0, 4)))) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given accademic year is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert accademic year field to Date class (int): " + readFromLine;
                            }
                            if ((courseList.empty()) && !errorInFormat){
                                if (dummyCourse.generateNewId("")) {
                                    errorInFormat = true;
                                    errorHandling = "Error: unsuccessful id generation";
                                }
                            } else {
                                if (dummyCourse.generateNewId(courseList.back().getId())) {
                                    errorInFormat = true;
                                    errorHandling = "Error: unsuccessful id generation";
                                }
                            }

                            break;
                        }
                        case 1:{
                            dummyCourse.setActiveCourse(true);
                            dummyCourse.setTitle(readFromLine);
                            break;
                        }
                        case 2:{
                            try {
                                if (dummyCourse.setCfu(stoi(readFromLine))) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of cfu is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert cfu field to int: " + readFromLine;
                            }
                            break;
                        }
                        case 3:{
                            try {
                                if (dummyCourse.setCourseLessonH(stoi(readFromLine))) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of lesson hour is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert lesson hour field to int: " + readFromLine;
                            }
                            break;
                        }
                        case 4:{
                            try {
                                if (dummyCourse.setCourseExerciseH(stoi(readFromLine))) {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of exercise hour is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert exercise hour field to int: " + readFromLine;
                            }
                            break;
                        }
                        case 5:{
                            try {
                                if (dummyCourse.setCourseLabH(stoi(readFromLine))) {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given value of laboratory hour is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert laboratory hour field to int: " + readFromLine;
                            }
                            break;
                        }
                        case 6:{
                            try {
                                if (dummyCourse.setParallelCoursesNumber(stoi(readFromLine))) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given number of parallel courses is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the number of parallel version of the given course to int: " + readFromLine;
                            }
                            break;
                        }
                        case 7:{
                            // the "list" of professor with their lesson/exercise/lab hour will be properly handled after this switch
                            associateProfessorListFormFile.str() = readFromLine;
                            break;
                        }
                        case 8:{
                            string readExamOraganzation;
                            stringstream tmpExamOrganization;
                            int patternOfExamOrganization = 0;

                            tmpExamOrganization.str() = readFromLine.substr(1, readFromLine.size() - 2);
                            while (getline(tmpExamOrganization, readExamOraganzation, ',') && !errorInFormat) {
                                switch (patternOfExamOrganization) {
                                    case 0: {
                                        try {
                                            if (!dummyCourse.setExamDuration(stoi(readExamOraganzation))) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exam duration is below 0 (zero): " + readExamOraganzation;
                                            }
                                        }
                                        catch (const invalid_argument &excepFromStoi) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the exam duration field to int: " + readExamOraganzation;
                                        }
                                        break;
                                    }
                                    case 1: {
                                        try {
                                            if (!dummyCourse.setEntranceTime(stoi(readExamOraganzation))) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given entrance time is below 0 (zero): " + readExamOraganzation;
                                            }
                                        }
                                        catch (const invalid_argument &excepFromStoi) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the entrance time field to int: " + readExamOraganzation;
                                        }
                                        break;
                                    }
                                    case 2: {
                                        try {
                                            if (!dummyCourse.setExitTime(stoi(readExamOraganzation))) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exit time is below 0 (zero): " + readExamOraganzation;
                                            }
                                        }
                                        catch (const invalid_argument &excepFromStoi) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the exit time field to int: " + readExamOraganzation;
                                        }
                                        break;
                                    }
                                    case 3: {
                                        if (!dummyCourse.setExamType(readExamOraganzation)) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exam type doesn't match the acronym set (S/SO/O/P): " + readExamOraganzation;
                                        }
                                        break;
                                    }
                                    case 4: {
                                        if (!dummyCourse.setExamClassroomType(readExamOraganzation[0])) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given classroom type doesn't match the acronym set (A/L): " + readExamOraganzation;
                                        }
                                        break;
                                    }
                                    case 5: {
                                        try {
                                            if (!dummyCourse.setPartecipants(stoi(readExamOraganzation))) {
                                                errorInFormat = true;
                                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) +
                                                                "the given number of students is below 0 (zero): " + readExamOraganzation;
                                            }
                                        }
                                        catch (const invalid_argument &excepFromStoi) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) +
                                                            " incorrect element impossible to convert the number of students field to int: " +
                                                            readExamOraganzation;
                                        }
                                        break;
                                    }
                                    default: {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) +
                                                " unexpected element number greater than: " + to_string(6);
                                    }
                                }
                                patternOfExamOrganization++;
                            }
                            break;
                        }
                        case 9:{
                            // here the list of grouped courses is put in place through append
                            string readGroupingCourses;
                            stringstream strGroupingAssembly;
                            // here it is verified if the last field of the pattern is not empty, in that case continue
                            if (readFromLine != "{}") {
                                // before operating on the string "{" and "}" are cutout
                                strGroupingAssembly.str() = readFromLine.substr(1, readFromLine.size() - 2);
                                while (getline(strGroupingAssembly,readGroupingCourses, ',') && !errorInFormat) {
                                    if (!dummyCourse.appendGroupedId(readGroupingCourses)) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given element of the grouped list of courses doesn't match the pattern (01XXXXX): " + readGroupingCourses;
                                    }
                                }
                            }
                            break;
                        }
                        default:{
                            errorInFormat = true;
                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) +
                                            " unexpected element number greater than: " + to_string(10);
                        }
                    }
                    patternField++;
                }
//------------> here the associate professor string is porocessed and properly divided into section
                associateProfessorListFormFile.str().substr(1, associateProfessorListFormFile.str().size() - 2);
                int  level = 0, levelIncrement = 0, levelDecrement = 0, versionCounter = 0;
                bool isLevelCorrect = false;
                string mainProfessorCourse;
                AssociateProfessor dummyAssociateProfessor;
                Professor dummyProfessorFromNotFound;

                list<AssociateProfessor> tmpAssociateProfessorList;
                list<Professor> tmpProfessorList = professorList;
                list<Professor>::iterator itReturnToFind;   //------------> ITERATORE
                vector<int> patternFieldForEachLevel {0, 0, 0};
                // first element of the vector: keeps memory of the pattern at LEVEL 1 (zero), so professor id, and vesion id
                // second element of the vector: is not used but in order to have a direct dependancy with the switch is needed
                // third element of the vector: keeps memory of the pattern at LEVEL 3, so professor id, lesson hour, exercise hour and lab hour
                // LEVEL 2 is discarded because doesn't have any meaningful information, due to it rapresentig the inner "[...]"

                while (getline(associateProfessorListFormFile, associateProfessorFromFile, ',') && !errorInFormat && !errorIncoherentHour) {
                    levelIncrement=0;
                    levelDecrement=0;
                    isLevelCorrect = false;
                    while (!isLevelCorrect){
                        if (associateProfessorFromFile[0] == '[') {
                            associateProfessorFromFile.substr(1, associateProfessorFromFile.size() - 1);
                            levelIncrement++;
                        } else if (associateProfessorFromFile[0] == '{') {
                            associateProfessorFromFile.substr(1, associateProfessorFromFile.size() - 1);
                            levelIncrement++;
                        } else if (associateProfessorFromFile[associateProfessorFromFile.size() - 1] == '}') {
                            associateProfessorFromFile.substr(0, associateProfessorFromFile.size() - 1);
                            levelDecrement ++;
                        } else if (associateProfessorFromFile[associateProfessorFromFile.size() - 1] == ']') {
                            associateProfessorFromFile.substr(0, associateProfessorFromFile.size() - 1);
                            levelDecrement ++;
                        }else{
                            isLevelCorrect = true;
                        }
                    }
                    level+=levelIncrement;

                    switch (level) {
                        case 1:{
                            switch (patternFieldForEachLevel[level - 1] % 2) {
                                case 0:{
                                    mainProfessorCourse = associateProfessorFromFile;
                                    patternFieldForEachLevel[level - 1]++;
                                    break;
                                }
                                case 1:{
                                    if (parallelVersionProgression(errorHandling, versionCounter,
                                                                   associateProfessorFromFile)) {
                                        if (!dummyCourse.setParallelCoursesId(associateProfessorFromFile)) {
                                            errorInFormat = true;
                                            errorHandling =
                                                    "Error: file: " + courseFileName + "row: " + to_string(lineOfFile) +
                                                    "the given version id is not compatible with the pattern for that field (P000): " +
                                                    associateProfessorFromFile;
                                        }
                                        versionCounter++;
                                    } else {
                                        errorInFormat = true;
                                    }
                                    patternFieldForEachLevel[level - 1]++;
                                    break;
                                }
                                default:{
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number there may be an incorrect number or type of brackets, plese controll the regular professor and version"
                                                    " id of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                    break;
                                }
                            }
                            break;
                        }
                        case 2:{
                            break;
                        }
                        case 3:{
                            switch (patternFieldForEachLevel[level - 1] % 4) {
                                case 0:{
                                    itReturnToFind = findProfessor(tmpProfessorList, associateProfessorFromFile);
                                    if (patternFieldForEachLevel[level - 1] == 0) {
                                        if (mainProfessorCourse == associateProfessorFromFile) {
                                            dummyAssociateProfessor.setIsMain(true);
                                            if (itReturnToFind != tmpProfessorList.end()) {
                                                dummyAssociateProfessor.setProfessorPointer(itReturnToFind);
                                            } else {
                                                // creo e inserisco il professore non trovato nella lista dei professori, sarà da controllare nella lista dei professori
                                                // se gli altri campi saranno compilati
                                                if (!dummyProfessorFromNotFound.setId(associateProfessorFromFile)) {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "incorrect professor id: " + associateProfessorFromFile;
                                                }
                                                tmpProfessorList.push_back(dummyProfessorFromNotFound);
                                                itReturnToFind = findProfessor(tmpProfessorList, associateProfessorFromFile);
                                                if (itReturnToFind != tmpProfessorList.end()) {
                                                    dummyAssociateProfessor.setProfessorPointer(itReturnToFind);
                                                } else {
                                                    errorInFormat = true;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "error ceeating the unexisting professor with id: " + associateProfessorFromFile;
                                                }
                                            }
                                        } else {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the regular professor for the version " + dummyCourse.getParallelCoursesId() + " is " + mainProfessorCourse + " which is "
                                                            "different from the one on first place of  the course organization: " + associateProfessorFromFile;
                                        }
                                    } else {
                                        if (itReturnToFind != tmpProfessorList.end()) {
                                            dummyAssociateProfessor.setProfessorPointer(itReturnToFind);
                                        } else {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + "row: " + to_string(lineOfFile + 1) + " can't find professor id " + associateProfessorFromFile + " in professor list";
                                        }                                    }
                                    patternFieldForEachLevel[level - 1]++;
                                    break;
                                }
                                case 1:{
                                    try {
                                        if (dummyAssociateProfessor.setLessonH(stoi(associateProfessorFromFile))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given lesson hour is below 0 (zero): " + associateProfessorFromFile;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the lesson hour field to int: " + associateProfessorFromFile + " (field number: "
                                                        + to_string(patternFieldForEachLevel[level - 1]) + ", related to professor id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ")";
                                    }
                                    patternFieldForEachLevel[level - 1]++;
                                    break;
                                }
                                case 2:{
                                    try {
                                        if (dummyAssociateProfessor.setExerciseH(stoi(associateProfessorFromFile))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given exercise hour is below 0 (zero): " + associateProfessorFromFile;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the exercise hour field to int: " + associateProfessorFromFile + " (field number: "
                                                        + to_string(patternFieldForEachLevel[level - 1]) + ", related to professor id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ")";
                                    }
                                    patternFieldForEachLevel[level - 1]++;
                                    break;
                                }
                                case 3:{
                                    try {
                                        if (dummyAssociateProfessor.setLabH(stoi(associateProfessorFromFile))) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given laboratory hour is below 0 (zero): " + associateProfessorFromFile;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incorrect element impossible to convert the laboratory hour field to int: " + associateProfessorFromFile + " (field number: "
                                                        + to_string(patternFieldForEachLevel[level - 1]) + ", related to professor id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ")";
                                    }
                                    // here the associate professor should be complete with all the data, so below if there is no errors
                                    // a push to a temporary list is made
                                    if (!errorInFormat) {
                                        tmpAssociateProfessorList.push_back(dummyAssociateProfessor);
                                    }
                                    break;
                                }
                                default:{
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number there may be an incorrect number or type of brackets, plese controll the professor (id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ") and version (id: "
                                                    + dummyCourse.getParallelCoursesId() + "of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            errorInFormat = true;
                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " unexpected element number there may be an incorrect number or type of brackets, plese controll the professor (id: " + dummyAssociateProfessor.getProfessorPointer()->getId() + ") and version (id: "
                                            + dummyCourse.getParallelCoursesId() + "of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                            break;
                        }
                    }
                    level-=levelDecrement;
                    if (level == 0) {
                        patternFieldForEachLevel[2] = 0;
                        if (!errorInFormat) {
                            if (dummyCourse.setListAssistant(tmpAssociateProfessorList, errorHandling) == 255){
                                courseList.push_back(dummyCourse);
                                tmpAssociateProfessorList.clear();
                            } else {
                                errorIncoherentHour = true;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + " incoherent number of hour, when pushing db temporary list, between the total ammount given to the course and the sum of those of the given professors";
                            }
                        }
                    }
                }
                lineOfFile++;
                if (versionCounter != courseList.back().getParallelCoursesNumber()) {
                    for (int i = 0; i < versionCounter; i++) {
                        courseList.pop_back();
                    }
                    errorInFormat = true;
                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(lineOfFile + 1) + "the given number of parallel courses is different than the one specified as single parameter: " + to_string(courseList.back().getParallelCoursesNumber());
                }
            }
        }
    }
    if (errorInFormat) {
        return (int) ERR_file_format;
    } else if (errorIncoherentHour) {
        return (int) ERR_hour_set;
    } else {
        return (int) OK;
    }
}

// here the file made of study courses is handled with regard if it is coming from the database or not
int CourseOFStudyInputFile(string& errorHandling, const string& courseOfStudyFileName, list<CourseOfStudy>& studyCoursesList, const bool& isDb) {
    ifstream fileName;
    string readFromFile, readFromLine;
    int lineOfFile = 0, patternField = 0;
    bool errorInFormat = false;

    fileName.open(courseOfStudyFileName, 'r');
    if (!fileName.is_open()) {
        errorHandling = "Error: file: " + courseOfStudyFileName + " not found.";
        return (int) ERR_open_file;
    } else {
        CourseOfStudy dummyStudyCourse;

        if (isDb) {
            patternField = 0;
        } else {
            patternField = 1;
        }
        while (getline(fileName, readFromFile) && !errorInFormat) {
            stringstream courseOfStudyRow;

            courseOfStudyRow.str() = readFromFile;
            while (getline(courseOfStudyRow, readFromLine, ';') && !errorInFormat) {
                switch (patternField) {
                    case 0: {
                        if (dummyStudyCourse.setCourseOfStudyId(readFromLine)) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + courseOfStudyFileName +
                                            "the given study course's id does not match the pattern fiel (C000): " +
                                            readFromLine;
                        }
                        patternField++;
                        break;
                    }
                    case 1: {
                        if (!isDb) {
                            if (studyCoursesList.empty()) {
                                dummyStudyCourse.generateCourseOfStudyId("");
                            } else {
                                dummyStudyCourse.generateCourseOfStudyId(studyCoursesList.back().getCourseOfStudyId());
                            }
                        }
                        if (dummyStudyCourse.setGaraduationType(readFromLine)) {
                            errorInFormat = true;
                            errorHandling = "Error: file: " + courseOfStudyFileName +
                                            "the given graduation time does not match the proper pattern (BS/MS): " +
                                            readFromLine;
                        }
                        patternField++;
                        break;
                    }
                    case 2: {
                        stringstream coursesBySemester;
                        string semesterCourse, tmpError;
                        int level = 0, semester = 0;
                        bool semesterRecon = false;

                        coursesBySemester.str() = readFromLine.substr(1, readFromLine.size() - 2);
                        while (getline(coursesBySemester, semesterCourse, ',') && !errorInFormat) {
                            semesterRecon = false;
                            while (!semesterRecon && !errorInFormat) {
                                if (semesterCourse.front() == '{') {
                                    semesterCourse = semesterCourse.substr(1, semesterCourse.size() - 1);
                                    level++;
                                    semester++;
                                } else if (semesterCourse.back() == '}') {
                                    semesterCourse = semesterCourse.substr(0, semesterCourse.size() - 1);
                                    level--;
                                } else {
                                    if (level == '0') {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseOfStudyFileName + "semester: " +
                                                        to_string(semester) + "with no courses";
                                    } else if ((level < 0) || (level > 1)) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + courseOfStudyFileName + "semester: " +
                                                        to_string(semester) + "with wrong number of brackets";
                                    } else {
                                        semesterRecon = true;
                                    }
                                }
                            }
                            if (!dummyStudyCourse.setListOfCoursesBySemester(tmpError, semester, semesterCourse)) {
                                errorInFormat = true;
                                errorHandling =
                                        "Error: file: " + courseOfStudyFileName + "semester: " + to_string(semester) +
                                        tmpError + semesterCourse;
                            }
                        }
                        patternField++;
                    }
                    case 3: {
                        stringstream idEndedCourses;
                        string endedCourse, tmpError;

                        if ((readFromLine.front() == '[') && (readFromLine.back() == ']')) {
                            idEndedCourses.str() = readFromLine.substr(1, readFromLine.size() - 2);
                            while (getline(idEndedCourses, endedCourse, ',') && !errorInFormat) {
                                if (!dummyStudyCourse.setListOfCoursesBySemester(tmpError, -1, endedCourse)) {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + courseOfStudyFileName + tmpError + " ended course id: " +
                                            endedCourse;
                                }
                            }
                        } else {
                            errorInFormat = true;
                            errorHandling =
                                    "Error: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile + 1) +
                                    " expecting \"[]\" as terminal field";
                        }
                        patternField++;
                    }
                    default: {
                        errorInFormat = true;
                        errorHandling = "Error: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile + 1) +
                                        " unexpected element number for the course of study pattern greater than " +
                                        to_string(3);
                        break;
                    }
                }
            }
            lineOfFile++;
            if(patternField < 4) {
                errorInFormat = true;
                errorHandling = "Error: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile) + "unexpected element number for the course of study pattern lower than " +
                to_string(3);
            }

            if (!errorInFormat) {
                studyCoursesList.push_back(dummyStudyCourse);
            }
        }
    }
}

int ExamSessionInputFile(string& errorHandling, const string& examSessionStringFileName, map<Date, vector<Date>>& examSessionPerAcademicYear, bool readDatabase) {
    ifstream fileName;
    bool errorInFile = false, errorAcademicYear = false, errorCommandIdentifier = false, errorDateField = false, errorExamPeriod = false,
         errorExamSession = false, errorDatesPlacement = false, errorInSessionOrder = false, errorSessionDuration = false;
    bool isFileInput = false, stringInsertionComplete = false;
    int examPeriod, row = 0;
    string startPattern, examDates, academicYear, examSession, errorLine;
    Date beginYear, endYear;
    vector<Date> tmpSessionVector;


    if (readDatabase) {
        fileName.open(examSessionStringFileName, 'r');
        if (!fileName.is_open()) {
            errorInFile = true;
            errorHandling = "Error: file: " + examSessionStringFileName + " not found.";
        } else {
            // the flag below is needed for distinguish the error messages in database readings
            isFileInput = true;
        }
    } else {
        // the passed string is decomposed, and it'll update the database or add a new session
        startPattern = examSessionStringFileName.substr(0, 12);
        examDates = examSessionStringFileName.substr(13, examSessionStringFileName.size() - 13);
        if (startPattern != "-s current_a ") {
            errorCommandIdentifier = true;
            errorHandling = "Error: the string passed by argument doesn't match the pattern used to identify the insertion of exam periods";
        }
    }

    while (((getline(fileName, examDates) && isFileInput) || (!stringInsertionComplete && !isFileInput)) && !errorAcademicYear && !errorExamPeriod && !errorDateField && !errorInFile && !errorCommandIdentifier) {
        examPeriod = 0;
        stringstream examDatesStream;
        pair<Date, vector<Date>> pairToInsert;
        pair<map<Date,vector<Date>>::iterator, bool > itToMapElement;

        academicYear = examDates.substr(0, 9);
        if (academicYear[4] == '-') {
            try {
                beginYear.setYear(stoi(academicYear.substr(0, 4)));
            }
            catch (const invalid_argument& excepFromStoi) {
                errorAcademicYear = true;
                if (isFileInput) {
                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                    "incorrect element impossible to convert the academic start year field to int: " + academicYear.substr(0, 4);
                } else {
                    errorHandling = "Error: incorrect element impossible to convert the academic start year field to int: " +
                                    academicYear.substr(0, 4);
                }
            }
            try {
                endYear.setYear(stoi(academicYear.substr(6, 4)));
            }
            catch (const invalid_argument& excepFromStoi) {
                errorAcademicYear = true;
                if (isFileInput) {
                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                    "incorrect element impossible to convert the academic ending year field to int: " + academicYear.substr(6, 4);
                } else {
                    errorHandling = "Error: incorrect element impossible to convert the academic ending year field to int: " +
                                    academicYear.substr(6, 4);
                }
            }
            if ((endYear < beginYear) || ((endYear - beginYear) > 0)) {
                errorAcademicYear = true;
                if (isFileInput) {
                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                    " the starting year is after the ending academic year";
                } else {
                    errorHandling = "Error: the starting year is after the ending academic year";
                }
            }
        } else {
            errorAcademicYear = true;
            if (isFileInput) {
                errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                " incorrect pattern for academic year" + academicYear;
            } else {
                errorHandling = "Error: incorrect pattern for academic year" + academicYear;
            }
        }
        examDates = examDates.substr(10, examDates.size() - 10);
        examDatesStream.str() = examDates;
        while ((getline(examDatesStream, examSession, ' ')) && !errorAcademicYear && !errorExamPeriod && !errorDateField) {
            string date;
            stringstream examSessionStream;
            int startStopDates = 0;

            examSessionStream.str() = examSession;
            while ((getline(examSessionStream, date, '_')) && !errorDateField && !errorExamPeriod) {
                int dateFieldCount = 0;
                string dateField;
                stringstream dateStream;
                Date dummyExamDate;

                dateStream.str() = date;
                while ((getline(dateStream, dateField, '-')) && !errorDateField) {
                    int pattern;

                    try {
                        pattern = stoi(dateField);
                    }
                    catch (const invalid_argument& excepFromStoi) {
                        errorDateField = true;
                    }
                    switch (dateFieldCount) {
                        case 0: {
                            if (!errorAcademicYear) {
                                dummyExamDate.setYear(pattern);
                            } else {
                                if (isFileInput) {
                                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                                    " incorrect year impossible to convert year field to int: " + dateField;
                                } else {
                                    errorHandling = "Error: incorrect year impossible to convert year field to int: " + dateField;
                                }
                            }
                            break;
                        }
                        case 1: {
                            if (!errorAcademicYear) {
                                dummyExamDate.setMonth(pattern);
                            } else {
                                if (isFileInput) {
                                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                                    " incorrect months impossible to convert month field to int: " + dateField;
                                } else {
                                    errorHandling = "Error: incorrect months impossible to convert month field to int: " + dateField;
                                }
                            }
                            break;
                        }
                        case 2: {
                            if (!errorAcademicYear) {
                                dummyExamDate.setDay(pattern);
                            } else {
                                if (isFileInput) {
                                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                                    " incorrect months impossible to convert day field to int: " + dateField;
                                } else {
                                    errorHandling = "Error: incorrect day impossible to convert day field to int: " + dateField;
                                }
                            }
                            break;
                        }
                        default: {
                            errorHandling = "Error: the date " + date + " doesn't respect the the number valid (3) for that pattern";
                        }
                    }
                    dateFieldCount++;
                }
                startStopDates++;
                if (!errorDateField && !errorExamPeriod) {
                    tmpSessionVector.push_back(dummyExamDate);
                }
            }
            examPeriod++;
            // here the start and stop number is controlled (= 6), if it is uneven there's an error
            if (startStopDates != 2) {
                errorExamSession = true;
                if (isFileInput) {
                    errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                    " has incorrect session's number date";
                } else {
                    errorHandling = "Error: the given string has incorrect session's number date";
                }
            }
        }
        // here the number of sessions is controlled (winter, summer and autumn session) and if there's a mismatch an error is risen
        if (examPeriod != 3) {
            errorExamSession = true;
            if (isFileInput) {
                errorHandling = "Error: file: " + examSessionStringFileName + " row: " + to_string(row) +
                                " has incorrect session's number defined";
            } else {
                errorHandling = "Error: the given string has incorrect session's number defined";
            }
        }
        // the following four ifs are used to verify the coherency and correctness of data coming from input string or database file
        if (examSessionAcademicYearCoherencyTest(errorLine, (beginYear.getYear() - 1), tmpSessionVector)) {
            errorAcademicYear = true;
            if (isFileInput) {
                errorHandling = "Error: file: " + examSessionStringFileName + " has " + errorLine + " in row " +
                                to_string(row);
            } else {
                errorHandling = "Error: the string has " + errorLine;
            }
        }
        if (examSessionBeginEndVerification(errorLine, tmpSessionVector)) {
            errorDatesPlacement = true;
            if (isFileInput) {
                errorHandling = "Error: file: " + examSessionStringFileName + " has " + errorLine + " in row " +
                                to_string(row);
            } else {
                errorHandling = "Error: the string has " + errorLine;
            }
        }
        if (examSessionOrderVerification(errorLine, tmpSessionVector)) {
            errorInSessionOrder = true;
            if (isFileInput) {
                errorHandling = "Error: file: " + examSessionStringFileName + " has " + errorLine + " in row " +
                                to_string(row);
            } else {
                errorHandling = "Error: the string has " + errorLine;
            }
        }
        if (sessionDurationConstrainVerification(errorLine, tmpSessionVector)) {
            errorSessionDuration = true;
            if (isFileInput) {
                errorHandling = "Error: file: " + examSessionStringFileName + " has " + errorLine + " in row " +
                                to_string(row);
            } else {
                errorHandling = "Error: the string has " + errorLine;
            }
        }
        // here map element is created and inserted
        pairToInsert.first = beginYear;
        pairToInsert.second = tmpSessionVector;
        itToMapElement = examSessionPerAcademicYear.insert(pairToInsert);
        // if the element already exist the iterator to relative element is taken, the vector cleared and substituted with the one coming from command line
        if (!itToMapElement.second) {
            itToMapElement.first->second.clear();
            itToMapElement.first->second = pairToInsert.second;
        }
        if (!isFileInput) {
            stringInsertionComplete = true;
        } else {
            row++;
        }
    }
    if (errorInFile) {
        return (int) ERR_open_file;
    } else if (errorCommandIdentifier) {
        return (int) ERR_string_identifier;
    } else if (errorAcademicYear) {
        return (int) ERR_academic_year;
    } else if (errorDateField) {
        return (int) ERR_date_field_conversion;
    } else if (errorExamPeriod) {
        return (int) ERR_exceeding_session_dates;
    } else if (errorExamSession) {
        return (int) ERR_exceeding_session_number;
    } else if (errorDatesPlacement) {
        return (int) ERR_inverted_dates;
    } else if (errorInSessionOrder) {
        return (int) ERR_session_planning;
    } else if (errorSessionDuration) {
        return (int) ERR_session_duration;
    } else {
        return (int) OK;
    }
}

int ProfessorUnavailability(string& errorHandling, const string& professorUnavailabilityFile, list<Professor>& professorList, const string& academicYear, const bool& isDb) {
    bool error = false;
    int row = 0;
    ifstream fileName;
    string readFromFile;
    t_typeErrorDefinitionReadingFile errorIdentifier;
    Date beginYear, endYear;
    list<Professor>::iterator itProfessorList;

    // if the academic year passed value isn't an  empty string is necessary to control the correctness of the fields
    if ((!academicYear.empty()) && !isDb) {
        if (academicYear[4] == '-') {
            try {
                beginYear.setYear(stoi(academicYear.substr(0, 4)));
            }
            catch (const invalid_argument& excepFromStoi) {
                error = true;
                errorIdentifier = ERR_academic_year;
                errorHandling = "Error: incorrect element impossible to convert the academic start year field to int: " + readFromFile.substr(0, 4);
            }
            try {
                endYear.setYear(stoi(academicYear.substr(6, 4)));
            }
            catch (const invalid_argument& excepFromStoi) {
                error = true;
                errorIdentifier = ERR_academic_year;
                errorHandling = "Error: incorrect element impossible to convert the academic end year field to int: " + readFromFile.substr(0, 4);
            }
            if ((endYear < beginYear) || ((endYear - beginYear) > 0)) {
                error = true;
                errorIdentifier = ERR_academic_year;
                errorHandling = "Error: the starting year is after the ending academic year";
            }
        } else {
            error = true;
            errorIdentifier = ERR_academic_year;
            errorHandling = "Error: incorrect pattern for academic year" + readFromFile;
        }
    }
    fileName.open(professorUnavailabilityFile, 'r');
    if (!fileName.is_open()) {
        errorHandling = "Error: file: " + professorUnavailabilityFile + " not found.";
        errorIdentifier = ERR_open_file;
    } else {
        while (getline(fileName, readFromFile) && !error) {
            if (isDb && (readFromFile.find(';') == string::npos)) {
                // here the string read from file is coming from database's file, and it hasn't the ";" field, so the field read in this case is the academic year
                if (readFromFile[4] == '-') {
                    try {
                        beginYear.setYear(stoi(readFromFile.substr(0, 4)));
                    }
                    catch (const invalid_argument& excepFromStoi) {
                        error = true;
                        errorIdentifier = ERR_academic_year;
                        errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row + 1) +
                                        "incorrect element impossible to convert the academic start year field to int: " + readFromFile.substr(0, 4);
                    }
                    try {
                        endYear.setYear(stoi(readFromFile.substr(6, 4)));
                    }
                    catch (const invalid_argument& excepFromStoi) {
                        error = true;
                        errorIdentifier = ERR_academic_year;
                        errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row + 1) +
                                        "incorrect element impossible to convert the academic end year field to int: " + readFromFile.substr(0, 4);
                    }
                    if ((endYear < beginYear) || ((endYear - beginYear) > 0)) {
                        error = true;
                        errorIdentifier = ERR_academic_year;
                        errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                        " the starting year is after the ending academic year";
                    }
                } else {
                    error = true;
                    errorIdentifier = ERR_academic_year;
                    errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) + " incorrect pattern for academic year" +
                                    readFromFile;
                }
            } else if (!isDb && (readFromFile.find(';') == string::npos)) {
                // here the string doesn't have a ";" but it isn't coming from a database file, so an error risen
                error = true;
                errorIdentifier = ERR_file_format;
                errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) + " has no separator (;)";
            } else {
                // here the string does contain a ";" so a further deserialization is needed to memorize the different fields
                bool first = true;
                string readFromLine;
                stringstream readFromFileStream;

                readFromFileStream.str() = readFromFile;
                while (getline(readFromFileStream, readFromLine, ';') && !error) {
                    int fieldNumber = 0;

                    if (first) {
                        // here the first field is the professor id
                        stringstream tmp;
                        if ((readFromLine != "") && (readFromLine.size()==7)) {
                            if (readFromLine[0] == 'd') {
                                try {
                                    stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    error = true;
                                    errorIdentifier = ERR_id_field;
                                    errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                    " incorrect element impossible to convert the numerical part of professor id to int: " + readFromLine;
                                }
                                itProfessorList = findProfessor(professorList, readFromLine);
                                if (itProfessorList == professorList.end()) {
                                    error = true;
                                    errorIdentifier = ERR_missing_professor;
                                    errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                    " can't find the given professor in database: " + readFromLine;
                                } else {
                                    if (!itProfessorList->getChangeInUnavail()) {
                                        itProfessorList->setChangeInUnavail(true);
                                    } else {
                                        error = true;
                                        errorIdentifier = ERR_professor_changed;
                                        errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                        " the given professor has already been modified in a previous iteration" + readFromLine;
                                    }

                                }
                            } else {
                                error = true;
                                errorIdentifier = ERR_id_field;
                                errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                " can't find the given professor in database: " + readFromLine;
                            }
                        } else {
                            error = true;
                            errorIdentifier = ERR_missing_professor;
                            errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                            " the given string (string: " + readFromLine + ") is empty or its length doesn't match the required one";
                        }
                        first = false;
                    } else {
                        // the other fields are the unavailability dates related to the previously identified professor
                        int position = 0;
                        string date;
                        stringstream readFromLineStream;
                        AvailForExam unavailPeriod;

                        readFromLineStream.str() = readFromLine;
                        while (getline(readFromLineStream, date, '|') && error) {
                            int dateFieldCount = 0;
                            string dateField;
                            stringstream dateStream;
                            Date dummyUnavailDate;

                            dateStream.str() = date;
                            while ((getline(dateStream, dateField, '-')) && !error) {
                                int pattern;

                                try {
                                    pattern = stoi(dateField);
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    error = true;
                                }
                                switch (dateFieldCount) {
                                    case 0: {
                                        if (!error) {
                                            dummyUnavailDate.setYear(pattern);
                                        } else {
                                            errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                            " incorrect year impossible to convert year field to int: " + dateField;
                                        }
                                        break;
                                    }
                                    case 1: {
                                        if (!error) {
                                            dummyUnavailDate.setMonth(pattern);
                                        } else {
                                            errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                            " incorrect months impossible to convert month field to int: " + dateField;
                                        }
                                        break;
                                    }
                                    case 2: {
                                        if (!error) {
                                            dummyUnavailDate.setDay(pattern);
                                        } else {
                                            errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                            " incorrect months impossible to convert day field to int: " + dateField;
                                        }
                                        break;
                                    }
                                    default: {
                                        errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                        " the date " + date + " doesn't respect the the number valid (3) for that pattern";
                                        break;
                                    }
                                }
                                dateFieldCount++;
                            }
                            // here depending on the "position" the date will be memorized in start or stop
                            switch (position) {
                                case 0:{
                                    unavailPeriod.start = dummyUnavailDate;
                                    position++;
                                    break;
                                }
                                case 1:{
                                    unavailPeriod.stop = dummyUnavailDate;
                                    position = 0;
                                    break;
                                }
                                default:{
                                    error = true;
                                    errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                    " the string has an incorrect number of of dates to identify an unavailability period";
                                    break;
                                }
                            }
                        }
                        fieldNumber++;
                        // the unavailability periods are now pushed in the map related to professor identified previously by mean of iterator
                        if ((unavailPeriod.start <= unavailPeriod.stop) && (((beginYear.getYear() == unavailPeriod.start.getYear()) || (endYear.getYear() == unavailPeriod.start.getYear())) && ((beginYear.getYear() == unavailPeriod.stop.getYear()) || (endYear.getYear() == unavailPeriod.stop.getYear())))) {
                            // before inserting/appending the start and stop date a control is performed
                            if (unavailabilityDatesVerification(unavailPeriod, itProfessorList->getUnavailListByAcademicYear(beginYear))) {
                                // if the return of append is TRUE the inserted element is correctly inserted
                                if (!itProfessorList->appendUnavailability(unavailPeriod, beginYear)) {
                                    // (database update) if the return of append is FALSE the inserted element has a key that already
                                    // exist so a clear is necessary then a new append, with the same data, is performed
                                    itProfessorList->clearMapAcademicYearUnavailability(beginYear);
                                    itProfessorList->appendUnavailability(unavailPeriod, beginYear);
                                }
                            } else {
                                error = true;
                                errorIdentifier = ERR_date_overlap;
                                errorHandling = "Error: file: " + professorUnavailabilityFile + " row: " + to_string(row) +
                                                " the given pair of date (start: " + unavailPeriod.start.getCompleteDate() + ", stop: " +
                                                unavailPeriod.stop.getCompleteDate() + ") may have an overlap with other dates range";
                            }
                        } else {
                            error = true;
                            errorIdentifier = ERR_inverted_dates;
                            errorHandling = "Error: the start and stop dates for field number " + to_string(fieldNumber) + " are inverted";
                        }
                        // reading unavail dates (here the start and stop date, for a single field, is reconstructed, and already present)
                    }
                    // reading separator ;
                }
                // if else: line is professor id + unavail periods
            }
            // still reading line
        }
    }
}