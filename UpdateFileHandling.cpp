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
                                    catch (const invalid_argument& excepFromStoi) {
                                        errorIdentifier = ERR_stoi_conversion;
                                        cerr << "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                                        " can't convert student id number to int";
                                    }
                                } else {
                                    errorIdentifier = ERR_id_field;
                                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given student id doesn't match the pattern (s000000): " + readFromFile;
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
                                                    " the given mail doesn't match the pattern accepted as a mail (<string>@<string>.<string>): " +
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
                if (((patternfield < 3) || ((patternfield == 3) && (readFromFile.back() != ';')) ||
                    ((patternfield == 4) && (readFromFile.back() == ';'))) && (errorIdentifier == OK)) {
                    errorIdentifier = ERR_student_format;
                    errorHandling = "Error: file: " + studentsFileName + " row: " + to_string(lineOfFile + 1) +
                                    " the number of fields in pattern is different than expected";
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
                                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) +
                                                            " can't find the given professor id in the list of professors: " +
                                                            readFromFile;
                                        }
                                        patternfield++;
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorIdentifier = ERR_stoi_conversion;
                                        cerr << "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) +
                                                        " can't convert professor id number to int";
                                    }
                                } else {
                                    errorIdentifier = ERR_id_field;
                                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given professor id doesn't match the pattern (d000000): " + readFromFile;
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
                                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given mail doesn't match the pattern accepted as a mail (<string>@<string>.<string>): " +
                                                    readFromFile;
                                }
                                patternfield++;
                                break;
                            }
                            default: {
                                errorIdentifier = ERR_professor_format;
                                errorHandling = "Error: file: " + professorFileName +
                                                "number of element for the pattern of the line greater than expected";
                                break;
                            }
                        }
                    } else {
                        if (patternfield == 0) {
                            errorIdentifier = ERR_missing_field;
                            errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) +
                                            " the first field of the line MUST specify the professor id";
                        } else {
                            patternfield++;
                        }
                    }
                }
                if (((patternfield < 3) || ((patternfield == 3) && (readFromFile.back() != ';')) ||
                     ((patternfield == 4) && (readFromFile.back() == ';'))) && (errorIdentifier == OK)) {
                    errorIdentifier = ERR_professor_format;
                    errorHandling = "Error: file: " + professorFileName + " row: " + to_string(lineOfFile + 1) +
                                    " the number of fields in pattern is different than expected";
                }
                lineOfFile++;
            }
        }
    } else {
        errorIdentifier = ERR_missing_file;
        errorHandling = "no db_professori.txt file on which perform an update";
    }
    if (fileName.is_open()) {
        fileName.close();
    }
    return (int) errorIdentifier;
}

// CLASSROOM
// this function takes and manage a file that for lines has an updated version of existing classrooms
int ClassroomToUpdateFile (string& errorHandling, const string& classroomFileName, list<Classroom>& classroomList) {
    t_errorCodes errorIdentifier = OK;
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;
    Classroom classroomRecovery;

    if (!classroomList.empty()) {
        fileName.open(classroomFileName, ifstream::in);
        if (!fileName.is_open()) {
            errorIdentifier = ERR_open_file;
            errorHandling = "Error: file: " + classroomFileName + " not found";
        } else {
            while (getline(fileName, readFromFile) && (errorIdentifier == OK)) {
                int patternfield = 0;
                string readFromLine;
                stringstream updateClassroomLine(readFromFile);
                list<Classroom>::const_iterator itReturnFromFindConst;
                list<Classroom>::iterator itReturnFromFind;

                while (getline(updateClassroomLine, readFromLine, ';') && (errorIdentifier == OK)) {
                    if (!readFromLine.empty()) {
                        switch (patternfield) {
                            case 0: {
                                if (readFromLine[0] == 'A') {
                                    try {
                                        stoi(readFromLine.substr(1, readFromLine.size() - 1));
                                        itReturnFromFindConst = findClassroom(classroomList, readFromLine);
                                        itReturnFromFind = constItToNonConstIt(classroomList, itReturnFromFindConst);
                                        if (itReturnFromFindConst == classroomList.cend()) {
                                            errorIdentifier = ERR_update_database;
                                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                            " can't find the given classroom id in the list of classrooms: " +
                                                            readFromLine;
                                        }
                                    }
                                    catch (const invalid_argument &excepFromStoi) {
                                        errorIdentifier = ERR_stoi_conversion;
                                        cerr << "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                        " can't convert classroom id number to int";
                                    }
                                } else {
                                    errorIdentifier = ERR_id_field;
                                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given classroom id doesn't match the pattern (A000): " + readFromFile;
                                }
                                break;
                            }
                            case 1: {
                                if (!itReturnFromFind->setType(readFromLine[0])) {
                                    errorIdentifier = ERR_classroom_format;
                                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                    " the given classroom type doesn't match the expected character (A/L): " + readFromLine;
                                }
                                break;
                            }
                            case 2: {
                                itReturnFromFind->setClassroomName(readFromLine);
                                break;
                            }
                            case 3: {
                                try {
                                    if (!itReturnFromFind->setCapacity(stoi(readFromLine))) {
                                        errorIdentifier = ERR_classroom_capacity;
                                        errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                        " the given classroom capacity is lower than 0 (zero): " + readFromLine;
                                    }
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    errorIdentifier = ERR_stoi_conversion;
                                    cerr << "Error: file: " + classroomFileName + " row " + to_string(lineOfFile + 1) +
                                                    " incorrect element impossible to convert classroom capacity field to int: " + readFromLine;
                                }
                                break;
                            }
                            case 4:{
                                try {
                                    if (!itReturnFromFind->setExamCapacity(stoi(readFromLine))) {
                                        errorIdentifier = ERR_classroom_capacity;
                                        if (readFromLine < "0") {
                                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                            "the given classroom's exam capacity is lower than 0 (zero): " + readFromLine;
                                        } else {
                                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                                            " the given classroom's exam capacity (" + readFromLine + ") higher than ordinary capacity (" +
                                                            to_string(itReturnFromFind->getCapacity()) + ")";
                                        }
                                    }
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    errorIdentifier = ERR_stoi_conversion;
                                    cerr << "Error: file: " + classroomFileName + " row " + to_string(lineOfFile + 1) +
                                                    " incorrect element impossible to convert classroom's exam capacity field to int: " + readFromLine;
                                }
                                break;
                            }
                            default: {
                                errorIdentifier = ERR_classroom_format;
                                errorHandling = "Error: file: " + classroomFileName + " number of element for the pattern of the line greater than " +
                                                to_string(5);
                                break;
                            }
                        }
                        patternfield++;
                    } else {
                        if (patternfield == 0) {
                            errorIdentifier = ERR_missing_field;
                            errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                            " the first field of the line MUST specify the classroom id";
                        } else {
                            patternfield++;
                        }
                    }
                }
                if (itReturnFromFind->getExamCapacity() > itReturnFromFind->getCapacity()) {
                    errorIdentifier = ERR_classroom_capacity;
                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                    " the given classroom's exam capacity (" + to_string(itReturnFromFind->getExamCapacity()) +
                                    ") is higher than ordinary capacity (" + to_string(itReturnFromFind->getCapacity()) + ")";
                }
                if (((patternfield < 4) || ((patternfield == 4) && (readFromFile.back() != ';')) ||
                    ((patternfield == 5) && (readFromFile.back() == ';'))) && (errorIdentifier == OK)) {
                    errorIdentifier = ERR_classroom_format;
                    errorHandling = "Error: file: " + classroomFileName + " row: " + to_string(lineOfFile + 1) +
                                    " the number of fields in pattern is different than expected";
                }
                lineOfFile++;
            }
        }
    } else {
        errorIdentifier = ERR_missing_field;
        errorHandling = "no \"db_aule.txt\" file on which perform an update";
    }
    if (fileName.is_open()) {
        fileName.close();
    }
    return (int) errorIdentifier;
}

int CourseOfStudyToUpdateFile (string& errorHandling, const string& courseOfStudyFileName, list<CourseOfStudy>& courseOfStudyList) {
    t_errorCodes errorIdentifier = OK;
    int lineOfFile = 0;
    ifstream fileName;
    string readFromFile;

    if (!courseOfStudyList.empty()) {
        fileName.open(courseOfStudyFileName, ifstream::in);
        if (!fileName.is_open()) {
            errorIdentifier =  ERR_open_file;
            errorHandling = "Error: file: " + courseOfStudyFileName + " not found";
        } else {
            while(getline(fileName,readFromFile) && (errorIdentifier == OK)) {
                int patternField = 0;
                string readFromLine;
                stringstream ss_readFromFile(readFromFile);
                list<string> toControl;
                list<CourseOfStudy>::const_iterator it_courseOfStudyConst;
                list<CourseOfStudy>::iterator it_courseOfStudy;

                while(getline(ss_readFromFile,readFromLine, ';') && (errorIdentifier == OK)) {
                    switch (patternField) {
                        case 0: {
                            if (!readFromLine.empty()) {
                                it_courseOfStudyConst = findCourseOfStudy(courseOfStudyList, readFromLine);
                                if (it_courseOfStudyConst != courseOfStudyList.cend()) {
                                    it_courseOfStudy = constItToNonConstIt(courseOfStudyList, it_courseOfStudyConst);
                                } else {
                                    errorIdentifier = ERR_missing_field;
                                    errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile + 1) +
                                                    "can't find the course of study id: " + readFromLine;
                                }
                            } else {
                                errorIdentifier = ERR_missing_field;
                                errorHandling = "Error: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile + 1) +
                                                " the first field of the line MUST specify the professor id";
                            }
                            patternField++;
                            break;
                        }
                        case 1: {
                            size_t position = 0, prevPosition = 0;
                            string courseId;
                            list<string> tmpSemesterCourse;

                            if ((readFromLine.front() == '[') && (readFromLine.back() == ']')) {
                                int level = 0, semester = 0;
                                readFromLine = readFromLine.substr(1, readFromLine.length() - 2);

                                stringstream ss_id(readFromLine);

                                do {
                                    position = readFromLine.find(',', prevPosition);
                                    if (position == std::string::npos) {
                                        position = readFromLine.length();
                                    }
                                    courseId = readFromLine.substr(prevPosition, position - prevPosition);
                                    prevPosition = position + 1;
                                    if ((!courseId.empty()) || (level != 0)) {
                                        if (courseId.front() == '{') {
                                            courseId = courseId.substr(1, courseId.length() - 1);
                                            semester++;
                                            level++;
                                        }
                                        if (courseId.back() == '}') {
                                            courseId = courseId.substr(0, courseId.length() - 1);
                                            level--;
                                        }
                                        if ((level < 0) || (level > 1)) {
                                            errorIdentifier = ERR_wrong_identifier;
                                            errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile + 1) +
                                                            "course of study: " + it_courseOfStudy->getCourseOfStudyId() +
                                                            " wrong number of parenthesis that separates semesters";
                                        }
                                        if (errorIdentifier == OK) {
                                            if (courseId.empty()) {
                                                tmpSemesterCourse.push_back(courseId);
                                            } else if ((courseId.at(0) == '0') && (courseId.at(1) == '1')) {
                                                int position = 0;

                                                while ((position < 5) && (errorIdentifier == OK)) {
                                                    if ((courseId.at(position + 2) < 'A') || (courseId.at(position + 2) > 'Z')) {
                                                        errorIdentifier = ERR_id_field;
                                                        errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " +
                                                                        to_string(lineOfFile + 1) + "course of study: " +
                                                                        it_courseOfStudy->getCourseOfStudyId() + " semester: " +
                                                                        to_string(semester + 1) + " has incorrect id field: " + courseId;
                                                    } else {
                                                        position++;
                                                    }
                                                }
                                                tmpSemesterCourse.push_back(courseId);
                                            } else {
                                                errorIdentifier = ERR_course_id;
                                                errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " +
                                                                to_string(lineOfFile + 1) + "course of study: " +
                                                                it_courseOfStudy->getCourseOfStudyId() + " semester: " +
                                                                to_string(semester + 1) + " the string " + courseId + " doesn't identify a course";
                                            }
                                        }
                                        if (level == 0) {
                                            list<string> semesterCourseFromDatabase;
                                            list<string>::iterator it_semesterCourseFromDatabase, it_tmpSemesterCourse, it_toControl;

                                            semesterCourseFromDatabase = it_courseOfStudyConst->getListOfCoursesBySemester(semester - 1);
                                            it_tmpSemesterCourse = tmpSemesterCourse.begin();
                                            it_semesterCourseFromDatabase = semesterCourseFromDatabase.begin();
                                            while ((it_tmpSemesterCourse != tmpSemesterCourse.cend()) && (errorIdentifier == OK)) {
                                                if (it_semesterCourseFromDatabase != semesterCourseFromDatabase.end()) {
                                                    if (it_tmpSemesterCourse->empty()) {
                                                        *it_tmpSemesterCourse = *it_semesterCourseFromDatabase;
                                                    }
                                                } else {
                                                    if (it_tmpSemesterCourse->empty()) {
                                                        errorIdentifier = ERR_course_id;
                                                        errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " +
                                                                        to_string(lineOfFile + 1) + "course of study: " +
                                                                        it_courseOfStudy->getCourseOfStudyId() + " semester: " +
                                                                        to_string(semester + 1) + " can't inherit a course id from database";
                                                    }
                                                }
                                                it_toControl = find(toControl.begin(), toControl.end(), *it_tmpSemesterCourse);
                                                if (it_toControl == toControl.end()) {
                                                    toControl.push_back(*it_tmpSemesterCourse);
                                                } else {
                                                    errorIdentifier = ERR_course_id;
                                                    errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " +
                                                                    to_string(lineOfFile + 1) + "course of study: " +
                                                                    it_courseOfStudy->getCourseOfStudyId() + " semester: " +
                                                                    to_string(semester + 1) + " duplicate in course inserted " + *it_tmpSemesterCourse;
                                                }
                                                it_tmpSemesterCourse++;
                                                it_semesterCourseFromDatabase++;
                                            }
                                            if (errorIdentifier == OK) {
                                                it_courseOfStudy->setCompleteListOfCoursesBySemester(semester - 1, tmpSemesterCourse);
                                                tmpSemesterCourse.clear();
                                            }
                                        }
                                    } else {
                                        semester++;
                                    }
                                } while ((position < readFromLine.length()) && (errorIdentifier == OK));
                                if ((((it_courseOfStudyConst->getGraduationType() == "BS") && (semester != 6)) ||
                                    ((it_courseOfStudyConst->getGraduationType() == "MS") && (semester != 4))) && (errorIdentifier == OK)) {
                                    errorIdentifier = ERR_semester;
                                    errorHandling = "ERROR: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile) +
                                                    " the course " + it_courseOfStudyConst->getCourseOfStudyId() +
                                                    " has a wrong number of semesters";
                                }
                            }
                            patternField = 0;
                            break;
                        }
                        default: {
                            errorIdentifier = ERR_professor_format;
                            errorHandling = "Error: file: " + courseOfStudyFileName +
                                            "number of element for the pattern of the line greater than " + to_string(4);
                            break;
                        }
                    }
                }
                if (((patternField < 3) || ((patternField == 3) && (readFromFile.back() != ';')) ||
                     ((patternField == 4) && (readFromFile.back() == ';'))) && (errorIdentifier == OK)) {
                    errorIdentifier = ERR_classroom_format;
                    errorHandling = "Error: file: " + courseOfStudyFileName + " row: " + to_string(lineOfFile + 1) +
                                    " the number of fields in pattern is different than expected";
                }
                lineOfFile++;
            }
        }
    }  else {
        errorIdentifier = ERR_missing_file;
        errorHandling = "no db_corsi_studio.txt file on which perform an update";
    }
    if (fileName.is_open()) {
        fileName.close();
    }

    return (int) errorIdentifier;
}