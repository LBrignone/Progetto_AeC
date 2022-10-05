//
// Created by Luca Brignone on 04/09/22.
//

#include "UpdateFileHandling.h"


// STUDENT
// this function takes and manage a file that has for lines an updated version of existing students
int StudentToUpdateFile (string& errorHandling, const string& studentsFileName, list<Student>& studentList) {
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;
    Student studentRecovery;
    bool noDb = false, errorInFormat = false;

    if (!studentList.empty()) {
        fileName.open(studentsFileName, 'r');
        if (!fileName.is_open()) {
            errorHandling = "Error: file: " + studentsFileName + " not found";
            return (int) ERR_open_file;
        } else {
            while (getline(fileName, readFromFile) && !errorInFormat) {
                stringstream updateStudentLine;
                string readFromLine;
                int patternfield = 0;
                list<Student>::iterator studentFound;

                updateStudentLine.str() = readFromFile;
                while (getline(updateStudentLine, readFromLine, ';') && !errorInFormat) {
                    if (!readFromLine.empty()) {
                        switch (patternfield) {
                            case 0: {
                                if (readFromLine[0] == 's') {
                                    try {
                                        stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                        studentFound = findStudent(studentList, readFromLine);
                                        if (studentFound == studentList.end()) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + studentsFileName + " row: " +
                                                            to_string(lineOfFile) +
                                                            " can't find the given student id in the list of students: " +
                                                            readFromFile;
                                        }
                                        patternfield++;
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling =
                                                "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) +
                                                " can't convert student id number to int";
                                    }
                                } else {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) +
                                            " the given student id desn't match the pattern (s000000): " + readFromFile;
                                }
                                break;
                            }
                            case 1: {
                                studentRecovery.setName(studentFound->getName());
                                studentFound->setName(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 2: {
                                studentRecovery.setName(studentFound->getSurname());
                                studentFound->setSurname(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 3: {
                                studentRecovery.setMail(studentFound->getMail());
                                if (!studentFound->setMail(readFromLine)) {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) +
                                            " the given mail doesn't match the pattern axcepted as a mail (<string>@<string>.<string>): " +
                                            readFromFile;
                                }
                                patternfield++;
                                break;
                            }
                            default: {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + studentsFileName +
                                                "number of element for the pattern of the line greater than " +
                                                to_string(4);
                                break;
                            }
                        }
                    } else {
                        if (patternfield == 0) {
                            errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " the first field of the line MUST specify the student id";
                            errorInFormat = true;
                        } else {
                            patternfield++;
                        }
                    }
                }
                if (patternfield < 4) {
                    studentFound->setName(studentRecovery.getName());
                    studentFound->setSurname(studentRecovery.getSurname());
                    studentFound->setMail(studentRecovery.getMail());
                    errorInFormat = true;
                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile) + " the number of fields in pattern is less than expected: " +
                                    to_string(4);
                } else {
                    lineOfFile++;
                }
            }
        }
    } else {
        errorHandling = "no db_studenti.txt file on which performe an update";
        noDb = true;
    }
    if (!errorInFormat && !noDb){
        return true;
    } else {
        return false;
    }
}

// PROFESSORS
// this function takes and manage a file that for lines has an updated version of existing professors
int ProfessorToUpdateFile (string& errorHandling, const string& professorFileName, list<Professor>& professorList) {
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;
    Professor professorRecovery;
    bool noDb = false, errorInFormat = false;

    if (!professorList.empty()) {
        fileName.open(professorFileName, 'r');
        if (!fileName.is_open()) {
            errorHandling = "Error: file: " + professorFileName + " not found";
            return (int) ERR_open_file;
        } else {
            while (getline(fileName, readFromFile) && !errorInFormat) {
                stringstream updateProfessorLine;
                string readFromLine;
                int patternfield = 0;
                list<Professor>::iterator professorFound;

                updateProfessorLine.str() = readFromFile;
                while (getline(updateProfessorLine, readFromLine, ';') && !errorInFormat) {
                    if (!readFromLine.empty()) {
                        switch (patternfield) {
                            case 0: {
                                if (readFromLine[0] == 'd') {
                                    try {
                                        stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                        professorFound = findProfessor(professorList, readFromLine);
                                        if (professorFound == professorList.end()) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + professorFileName + " row: " +
                                                            to_string(lineOfFile) +
                                                            " can't find the given student id in the list of students: " +
                                                            readFromFile;
                                        }
                                        patternfield++;
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling =
                                                "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                                " can't convert student id number to int";
                                    }
                                } else {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                            " the given student id desn't match the pattern (s000000): " + readFromFile;
                                }
                                break;
                            }
                            case 1: {
                                professorRecovery.setName(professorFound->getName());
                                professorFound->setName(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 2: {
                                professorRecovery.setSurname(professorFound->getSurname());
                                professorFound->setSurname(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 3: {
                                professorRecovery.setMail(professorFound->getMail());
                                if (!professorFound->setMail(readFromLine)) {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                            " the given mail doesn't match the pattern axcepted as a mail (<string>@<string>.<string>): " +
                                            readFromFile;
                                }
                                patternfield++;
                                break;
                            }
                            default: {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + professorFileName +
                                                "number of element for the pattern of the line greater than " +
                                                to_string(4);
                                break;
                            }
                        }
                    } else {
                        if (patternfield == 0) {
                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) + " the first field of the line MUST specify the professor id";
                            errorInFormat = true;
                        } else {
                            patternfield++;
                        }
                    }
                }
                if (patternfield < 4) {
                    professorFound->setName(professorRecovery.getName());
                    professorFound->setSurname(professorRecovery.getSurname());
                    professorFound->setMail(professorRecovery.getMail());
                    errorInFormat = true;
                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) + " the number of fields in pattern is less than expected: " +
                                    to_string(4);
                } else {
                    lineOfFile++;
                }
            }
        }
    } else {
        errorHandling = "no db_professori.txt file on which performe an update";
        noDb = true;
    }
    if (!errorInFormat && !noDb) {
        return true;
    } else {
        return false;
    }
}

// CLASSROOM
// this function takes and manage a file that for lines has an updated version of existing classrooms
int ClassroomToUpdateFile (string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList) {
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;
    Classroom classroomRecovery;
    bool noDb = false, errorInFormat = false;

    if (!classroomList.empty()) {
        fileName.open(classroomFileName, 'r');
        if (!fileName.is_open()) {
            errorHandling = "Error: file: " + classroomFileName + " not found";
            return (int) ERR_open_file;
        } else {
            while (getline(fileName, readFromFile) && !errorInFormat) {
                stringstream updateClassroomLine;
                string readFromLine;
                int patternfield = 0;
                list<Classroom>::iterator classroomFound;

                updateClassroomLine.str() = readFromFile;
                while (getline(updateClassroomLine, readFromLine, ';') && !errorInFormat) {
                    if (!readFromLine.empty()) {
                        switch (patternfield) {
                            case 0: {
                                if (readFromLine[0] == 'A') {
                                    try {
                                        stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                        classroomFound = findClassroom(classroomList, readFromLine);
                                        if (classroomFound == classroomList.end()) {
                                            errorInFormat = true;
                                            errorHandling = "Error: file: " + classroomFileName + " row: " +
                                                            to_string(lineOfFile + 1) +
                                                            " can't find the given student id in the list of students: " +
                                                            readFromFile;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorInFormat = true;
                                        errorHandling =
                                                "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile) +
                                                " can't convert student id number to int";
                                    }
                                } else {
                                    errorInFormat = true;
                                    errorHandling =
                                            "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                            " the given student id desn't match the pattern (s000000): " + readFromFile;
                                }
                                break;
                            }
                            case 1: {
                                classroomRecovery.setType(classroomFound->getType());
                                if (!classroomFound->setType(readFromLine[0])) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + "the given classroom type desn't match the expected character (A/L): " + readFromLine;
                                }
                                break;
                            }
                            case 2: {
                                classroomRecovery.setClassroomName(classroomFound->getClassroomName());
                                classroomFound->setClassroomName(readFromLine);
                                break;
                            }
                            case 3: {
                                classroomRecovery.setCapacity(classroomFound->getCapacity());
                                try {
                                    if (!classroomFound->setCapacity(stoi(readFromLine))) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + "the given classroom capacity is lower than 0 (zero): " + readFromLine;
                                    }
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + classroomFileName + " row " + to_string(lineOfFile + 1) + " incorrect element impossible to convert classroom capacity field to int: " + readFromLine;
                                }
                                break;
                            }
                            case 4:{
                                classroomRecovery.setExamCapacity(classroomFound->getExamCapacity());
                                try {
                                    if (!classroomFound->setExamCapacity(stoi(readFromLine))) {
                                        errorInFormat = true;
                                        errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + "the given classroom's exam capacity is lower than 0 (zero): " + readFromLine;
                                    }
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    errorInFormat = true;
                                    errorHandling = "Error: file: " + classroomFileName + " row " + to_string(lineOfFile + 1) + " incorrect element impossible to convert classroom's exam capacity field to int: " + readFromLine;
                                }
                                break;
                            }
                            default: {
                                errorInFormat = true;
                                errorHandling = "Error: file: " + classroomFileName +
                                                "number of element for the pattern of the line greater than " +
                                                to_string(5);
                                break;
                            }
                        }
                        patternfield++;
                    } else {
                        if (patternfield == 0) {
                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) + " the first field of the line MUST specify the professor id";
                            errorInFormat = true;
                        } else {
                            patternfield++;
                        }
                    }
                }
                if (patternfield < 5) {
                    classroomFound->setType(classroomRecovery.getType());
                    classroomFound->setClassroomName(classroomRecovery.getClassroomName());
                    classroomFound->setCapacity(classroomRecovery.getCapacity());
                    classroomFound->setExamCapacity(classroomRecovery.getExamCapacity());
                    errorInFormat = true;
                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile) + " the number of fields in pattern is less than expected: " +
                                    to_string(5);
                } else {
                    lineOfFile++;
                }
            }
        }
    } else {
        errorHandling = "no db_aule.txt file on which performe an update";
        noDb = true;
    }
    if (!errorInFormat && !noDb) {
        return true;
    } else {
        return false;
    }
}