//
// Created by Luca Brignone on 04/09/22.
//

#include "ConstConversion.hpp"
#include "UpdateFileHandling.h"

// STUDENT
// this function takes and manage a file that has for lines an updated version of existing students
int StudentToUpdateFile (string& errorHandling, const string& studentsFileName, list<Student>& studentList) {
    t_errorCodes errorIdentifier = OK;
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;

    if (!studentList.empty()) {
        fileName.open(studentsFileName, ifstream::in);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file: " + studentsFileName + " not found";
        } else {
            while (getline(fileName, readFromFile) && errorIdentifier == OK) {
                int patternfield = 0;
                string readFromLine;
                stringstream updateStudentLine(readFromFile);
                list<Student>::const_iterator itReturnFromFindConst;
                list<Student>::iterator itReturnFromFind;

                while (getline(updateStudentLine, readFromLine, ';') && errorIdentifier == OK) {
                    if (!readFromLine.empty()) {
                        switch (patternfield) {
                            case 0: {
                                if (readFromLine[0] == 's') {
                                    try {
                                        stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                        itReturnFromFindConst = findStudent(studentList, readFromLine);
                                        itReturnFromFind = constItToNonConstIt(studentList, itReturnFromFindConst);
                                        if (itReturnFromFindConst == studentList.cend()) {
                                            errorIdentifier = ERR_update_database;
                                            errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                                            " can't find the given student id in the list of students: " + readFromFile;
                                        }
                                        patternfield++;
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorIdentifier = ERR_stoi_conversion;
                                        errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                                        " can't convert student id number to int";
                                    }
                                } else {
                                    errorIdentifier = ERR_id_field;
                                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given student id desn't match the pattern (s000000): " + readFromFile;
                                }
                                break;
                            }
                            case 1: {
                                itReturnFromFind->setName(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 2: {
                                itReturnFromFind->setSurname(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 3: {
                                if (!itReturnFromFind->setMail(readFromLine)) {
                                    errorIdentifier = ERR_mail_format;
                                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given mail doesn't match the pattern axcepted as a mail (<string>@<string>.<string>): " +
                                                    readFromFile;
                                }
                                patternfield++;
                                break;
                            }
                            default: {
                                errorIdentifier = ERR_student_format;
                                errorHandling = "Error: file: " + studentsFileName + "number of element for the pattern of the line greater than " +
                                                to_string(4);
                                break;
                            }
                        }
                    } else {
                        if (patternfield == 0) {
                            errorIdentifier = ERR_missing_field;
                            errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                            " the first field of the line MUST specify the student id";
                        } else {
                            patternfield++;
                        }
                    }
                }
                patternfield++;
                if (patternfield < 4) {
                    errorIdentifier = ERR_student_format;
                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                    " the number of fields in pattern is less than expected: " + to_string(4);
                }
                lineOfFile++;
            }
        }
    } else {
        errorIdentifier = ERR_missing_file;
        errorHandling = "no file from which read a student update";
    }
    if (fileName.is_open()) {
        fileName.close();
    }
    return (int) errorIdentifier;
}

// PROFESSORS
// this function takes and manage a file that for lines has an updated version of existing professors
int ProfessorToUpdateFile (string& errorHandling, const string& professorFileName, list<Professor>& professorList) {
    t_errorCodes errorIdentifier = OK;
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;

    if (!professorList.empty()) {
        fileName.open(professorFileName, ifstream::in);
        if (!fileName.is_open()) {
            errorIdentifier =  ERR_open_file;
            errorHandling = "Error: file: " + professorFileName + " not found";
        } else {
            while (getline(fileName, readFromFile) && (errorIdentifier == OK)) {
                int patternfield = 0;
                string readFromLine;
                stringstream updateProfessorLine(readFromFile);
                list<Professor>::const_iterator itReturnFromFindConst;
                list<Professor>::iterator itReturnFromFind;

                while (getline(updateProfessorLine, readFromLine, ';') && (errorIdentifier == OK)) {
                    if (!readFromLine.empty()) {
                        switch (patternfield) {
                            case 0: {
                                if (readFromLine[0] == 'd') {
                                    try {
                                        stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                        itReturnFromFindConst = findProfessor(professorList, readFromLine);
                                        itReturnFromFind = constItToNonConstIt(professorList, itReturnFromFindConst);
                                        if (itReturnFromFindConst == professorList.cend()) {
                                            errorIdentifier = ERR_update_database;
                                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                                            " can't find the given student id in the list of students: " +
                                                            readFromFile;
                                        }
                                        patternfield++;
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorIdentifier = ERR_stoi_conversion;
                                        errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                                        " can't convert student id number to int";
                                    }
                                } else {
                                    errorIdentifier = ERR_id_field;
                                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                                    " the given student id desn't match the pattern (s000000): " + readFromFile;
                                }
                                break;
                            }
                            case 1: {
                                itReturnFromFind->setName(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 2: {
                                itReturnFromFind->setSurname(readFromLine);
                                patternfield++;
                                break;
                            }
                            case 3: {
                                if (!itReturnFromFind->setMail(readFromLine)) {
                                    errorIdentifier = ERR_mail_format;
                                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                                    " the given mail doesn't match the pattern axcepted as a mail (<string>@<string>.<string>): " +
                                                    readFromFile;
                                }
                                patternfield++;
                                break;
                            }
                            default: {
                                errorIdentifier = ERR_professor_format;
                                errorHandling = "Error: file: " + professorFileName +
                                                "number of element for the pattern of the line greater than " +
                                                to_string(4);
                                break;
                            }
                        }
                    } else {
                        if (patternfield == 0) {
                            errorIdentifier = ERR_missing_field;
                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                            " the first field of the line MUST specify the professor id";
                        } else {
                            patternfield++;
                        }
                    }
                }
                patternfield++;
                if (patternfield < 4) {
                    errorIdentifier = ERR_professor_format;
                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile) +
                                    " the number of fields in pattern is less than expected: " + to_string(4);
                }
                lineOfFile++;
            }
        }
    } else {
        errorIdentifier = ERR_missing_file;
        errorHandling = "no db_professori.txt file on which performe an update";
    }
    if (fileName.is_open()) {
        fileName.close();
    }
    return (int) errorIdentifier;
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
    if (fileName.is_open()) {
        fileName.close();
    }
    if (!errorInFormat && !noDb) {
        return true;
    } else {
        return false;
    }
}