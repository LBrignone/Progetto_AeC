//
// Created by Luca Brignone on 06/09/22.
//

#include "ConstConversion.hpp"
#include "InsertFileHandling.h"

// here is handled the update or changes for existing courses
int CourseToInsertFile(string& errorHandling, const string& courseFileName, list<Course>& databaseCourseList, list<Professor>& professorList, list<CourseOfStudy>& courseOfStudy) {
    t_errorCodes errorIdentifier = OK;
    ifstream fileName;
    string readFromFile, readFromLine, errorLine;
    int row = 0, patternFiled = 0;
    Course dummyCourse;
    list<Course> dummyCoursesList;

    fileName.open(courseFileName, ifstream::in);
    if (!fileName.is_open()) {
        errorIdentifier = ERR_open_file;
        errorHandling = "Error: file: " + courseFileName + " not found.";
    } else {
        while (getline(fileName, readFromFile) && (errorIdentifier == OK)) {
            patternFiled = 0;
            int startYear;
            string courseId, courseProfessorOrganization;
            stringstream lineToInsertFromFile(readFromFile);
            list<Course>::const_iterator itCourseListIdConst, itCourseListYearConst;
            list<Course>::iterator itCourseListId, itCourseListYear;

            if (readFromFile.empty()) {
                errorIdentifier = ERR_empty_file;
                errorHandling = "Error: file " + courseFileName + "is empty";
            }
            while (getline(lineToInsertFromFile, readFromLine, ';') && (errorIdentifier == OK)) {
                Date beginYear, endYear;

                switch (patternFiled) {
                    case 0:{
                        if (!readFromLine.empty()) {
                            if (!dummyCourse.setId(readFromLine)) {
                                errorIdentifier = ERR_id_field;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                " the course id is not valid";
                            }
                        } else {
                            errorIdentifier = ERR_missing_field;
                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                            " the course id must be present";
                        }
                        break;
                    }
                    case 1:{
                        if (!readFromLine.empty()) {
                            if (readFromLine[4] == '-') {
                                try {
                                    beginYear.setYear(stoi(readFromLine.substr(0, 4)));
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    errorIdentifier = ERR_academic_year;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                    "incorrect element impossible to convert the academic start year field to int: " + readFromLine.substr(0, 4);
                                }
                                try {
                                    endYear.setYear(stoi(readFromLine.substr(5, 4)));
                                }
                                catch (const invalid_argument& excepFromStoi) {
                                    errorIdentifier = ERR_academic_year;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                    "incorrect element impossible to convert the academic ending year field to int: " + readFromLine.substr(6, 4);
                                }
                                if ((endYear < beginYear) || ((endYear - beginYear) != 0)) {
                                    errorIdentifier = ERR_academic_year;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                    " the starting year is after the ending academic year";
                                }
                            } else {
                                errorIdentifier = ERR_academic_year;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                " incorrect pattern for academic year" + readFromLine;
                            }
                            if (!dummyCourse.setStartYear(beginYear.getYear())) {
                                errorIdentifier = ERR_academic_year;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                " the given academic year is below 0 (zero): " + readFromLine;
                            }
                            itCourseListYearConst = findCourse(databaseCourseList, dummyCourse.getId(), dummyCourse.getStartYear());
                            if (itCourseListYearConst != databaseCourseList.cend()) {
                                dummyCourse.inheritCourse(itCourseListYearConst) ;
                            } else {
                                itCourseListIdConst = findCourse(databaseCourseList, dummyCourse.getId());
                                if (itCourseListIdConst != databaseCourseList.cend()) {
                                    itCourseListIdConst = findCourseLastForId(databaseCourseList, dummyCourse.getId(), itCourseListIdConst);
                                    dummyCourse.inheritCourse(itCourseListIdConst);
                                } else {
                                    errorIdentifier = ERR_missing_field;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                    " can't find course id " + readFromLine + " into the list of courses";
                                }
                            }
                        } else {
                            errorIdentifier = ERR_file_format;
                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                            " the course's academic year must be present";
                        }
                        break;
                    }
                    case 2:{
                        if (!readFromLine.empty()) {
                            if ((readFromLine != "attivo") && (readFromLine != "non_attivo")) {
                                errorIdentifier = ERR_file_format;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                " the given course has wrong definition of active or not active course: " + readFromLine;
                            } else if ((readFromLine == "attivo") != dummyCourse.isActiveCourse()) {
                                dummyCourse.setActiveCourse(true);
                                removeCourseFromEndedCourses(errorHandling, dummyCourse, databaseCourseList, courseOfStudy);
                            } else if ((readFromLine == "non_attivo") != !dummyCourse.isActiveCourse()) {
                                dummyCourse.setActiveCourse(false);
                                putCourseInEndedCourses(errorHandling, dummyCourse, databaseCourseList, courseOfStudy);
                            }
                            // if there's no change in course's status ("attivo/non_attivo") remains valid the status inherited from database
                        }
                        break;
                    }
                    case 3:{
                        if (!readFromLine.empty()) {
                            try {
                                if (!dummyCourse.setParallelCoursesNumber(stoi(readFromLine))) {
                                    errorIdentifier = ERR_file_format;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                    " the given number of parallel course is below 0 (zero): " + readFromLine;
                                }
                            }
                            catch (const invalid_argument &excepFromStoi) {
                                errorIdentifier = ERR_file_format;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                " incorrect element impossible to convert the number of parallel courses field to int: " +
                                                readFromLine;
                            }
                        }
                        break;
                    }
                    case 4:{
                        if (!readFromLine.empty()) {
                            courseProfessorOrganization = readFromLine;
                        }
                        break;
                    }
                    case 5:{
                        int patternOfExamOrganization = 0;
                        string examField;
                        stringstream examOrganization(readFromLine.substr(1, readFromLine.size() - 2));

                        if (!readFromLine.empty()) {
                            if (readFromLine == "{}") {
                                errorIdentifier = ERR_file_format;
                                errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row) +
                                                " the exam organization has the field identifiers (\"{}\") but without contents";
                            }


                            while (getline(examOrganization, examField, ',') && (errorIdentifier == OK)) {
                                switch (patternOfExamOrganization) {
                                    case 0: {
                                        if (!examField.empty()) {
                                            try {
                                                if (!dummyCourse.setExamDuration(stoi(examField))) {
                                                    errorIdentifier = ERR_file_format;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                    to_string(row + 1) +
                                                                    " the given exam duration is below 0 (zero): " +
                                                                    examField;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorIdentifier = ERR_file_format;
                                                errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                to_string(row + 1) +
                                                                " incorrect element impossible to convert exam duration field to int: " +
                                                                examField;
                                            }
                                        }
                                        break;
                                    }
                                    case 1: {
                                        if (!examField.empty()) {
                                            try {
                                                if (!dummyCourse.setEntranceTime(stoi(examField))) {
                                                    errorIdentifier = ERR_file_format;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                    to_string(row + 1) +
                                                                    " the given entrance time is below 0 (zero): " +
                                                                    examField;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorIdentifier = ERR_file_format;
                                                errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                to_string(row + 1) +
                                                                " incorrect element impossible to convert entrance time field to int: " +
                                                                examField;
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        if (!examField.empty()) {
                                            try {
                                                if (!dummyCourse.setExitTime(stoi(examField))) {
                                                    errorIdentifier = ERR_file_format;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                    to_string(row + 1) +
                                                                    " the given exit time is below 0 (zero): " +
                                                                    examField;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorIdentifier = ERR_file_format;
                                                errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                to_string(row + 1) +
                                                                " incorrect element impossible to convert exit time field to int: " +
                                                                examField;
                                            }
                                        }
                                        break;
                                    }
                                    case 3: {
                                        if (!examField.empty()) {
                                            if (!dummyCourse.setExamType(examField)) {
                                                errorIdentifier = ERR_file_format;
                                                errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                to_string(row + 1) +
                                                                "the given exam type doesn't match the acronym set (S/SO/O/P): " +
                                                                examField;
                                            }
                                        }
                                        break;
                                    }
                                    case 4: {
                                        if (!examField.empty()) {
                                            if (!dummyCourse.setExamClassroomType(examField[0])) {
                                                errorIdentifier = ERR_file_format;
                                                errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                to_string(row + 1) +
                                                                "the given classroom type doesn't match the acronym set (A/L): " +
                                                                examField;
                                            }
                                        }
                                        break;
                                    }
                                    case 5: {
                                        if (!examField.empty()) {
                                            try {
                                                if (!dummyCourse.setPartecipants(stoi(examField))) {
                                                    errorIdentifier = ERR_file_format;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                    to_string(row + 1) +
                                                                    "the given number of students is below 0 (zero): " +
                                                                    examField;
                                                }
                                            }
                                            catch (const invalid_argument &excepFromStoi) {
                                                errorIdentifier = ERR_file_format;
                                                errorHandling = "Error: file: " + courseFileName + " row: " +
                                                                to_string(row + 1) +
                                                                " incorrect element impossible to convert number of students field to int: " +
                                                                examField;
                                            }
                                        }
                                        break;
                                    }
                                    default: {
                                        errorIdentifier = ERR_file_format;
                                        errorHandling = "Error: file: " + courseFileName + " row: " +
                                                        to_string(row + 1) +
                                                        " unexpected element number greater than: " + to_string(6);
                                    }
                                }
                                patternOfExamOrganization++;
                            }
                        }
                        break;
                    }
                    case 6: {
                        // the dummy course is coming from a find, so the grouped courses are always inherited
                        // below the code control if the inherited list of grouped courses has to be maintained or performs corrective actions
                        string courseToAppend;

                        if (!readFromLine.empty()) { // in case the field read (containing the list of grouped courses) is empty no changes must be performed at the already existing list
                            if (readFromLine == "{}"){
                                // here the inserted course doesn't have grouped courses
                                // all the grouped courses inherited from the database be deleted

                                dummyCourse.deleteGroupedId();
                            } else {
                                // here a new grouped courses list is present so it'll be updated
                                stringstream groupedCourses(readFromLine.substr(1, readFromLine.size() - 2));
                                dummyCourse.deleteGroupedId();
                                while (getline(groupedCourses, courseToAppend, ',') && (errorIdentifier == OK)) {
                                    if (!dummyCourse.appendGroupedId(courseToAppend)) {
                                        errorIdentifier = ERR_file_format;
                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                        "the given course id in grouped courses doesn't matche the course's pattern (01AAAAA): " +
                                                        courseToAppend;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    default:{
                        errorIdentifier = ERR_file_format;
                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                        " unexpected element number greater than: " + to_string(7);
                    }
                }
                patternFiled++;
            }
// -------> here the professor organization for each version is reconstructed and memorized
            if (!courseProfessorOrganization.empty()) {
                if ((courseProfessorOrganization.front() == '[') && (courseProfessorOrganization.back() == ']')) {
                    stringstream versionOrganization(courseProfessorOrganization.substr(1, courseProfessorOrganization.size() - 2));

                    if (!courseProfessorOrganization.empty()) {
                        int  level = 0, levelIncrement = 0, levelDecrement = 0, versionCounter = 0;
                        bool isLevelCorrect = false;
                        string professorOrganizationForVersion, mainProfessorCourse;
                        vector<int> patternFieldForEachLevel {0, 0, 0};
                        Professor dummyProfessor;
                        AssociateProfessor dummyAssociateProfessor;
                        list<AssociateProfessor> dummyAssociateProfessorsList;
                        list<Course>::const_iterator itCourseFromFindConst;
                        list<Professor>::const_iterator itProfessorFromFindConst;
                        list<Professor>::iterator itProfessorFromFind, itProfessorMain, itProfessorDummy;

                        while (getline(versionOrganization, professorOrganizationForVersion, ',') && (errorIdentifier == OK)) {
                            levelIncrement = 0;
                            levelDecrement = 0;
                            isLevelCorrect = false;

                            while (!isLevelCorrect) {
                                if (professorOrganizationForVersion[0] == '[') {
                                    professorOrganizationForVersion = professorOrganizationForVersion.substr(1, professorOrganizationForVersion.size() - 1);
                                    levelIncrement++;
                                } else if (professorOrganizationForVersion[0] == '{') {
                                    professorOrganizationForVersion = professorOrganizationForVersion.substr(1, professorOrganizationForVersion.size() - 1);
                                    levelIncrement++;
                                } else if (professorOrganizationForVersion[professorOrganizationForVersion.size() - 1] == '}') {
                                    professorOrganizationForVersion = professorOrganizationForVersion.substr(0, professorOrganizationForVersion.size() - 1);
                                    levelDecrement++;
                                } else if (professorOrganizationForVersion[professorOrganizationForVersion.size() - 1] == ']') {
                                    professorOrganizationForVersion = professorOrganizationForVersion.substr(0, professorOrganizationForVersion.size() - 1);
                                    levelDecrement++;
                                } else {
                                    isLevelCorrect = true;
                                }
                            }
                            level += levelIncrement;

                            switch (level) {
                                case 1:{
                                    switch (patternFieldForEachLevel[level - 1] % 2) {
                                        case 0:{
                                            // here the field read is regular professor
                                            if (!professorOrganizationForVersion.empty()){
                                                mainProfessorCourse = professorOrganizationForVersion;
                                            } else {
                                                mainProfessorCourse.clear();
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 1:{
                                            // here the field read is version id
                                            if (!professorOrganizationForVersion.empty()) {
                                                itCourseFromFindConst = findCourse(dummyCoursesList, dummyCourse.getId(), dummyCourse.getStartYear(), professorOrganizationForVersion);
                                                if (dummyCoursesList.empty() || (itCourseFromFindConst == dummyCoursesList.cend())) {
                                                    if (!dummyCourse.setParallelCoursesId(professorOrganizationForVersion)) {
                                                        errorIdentifier = ERR_file_format;
                                                        errorHandling = "Error: file: " + courseFileName + "row: " + to_string(row) +
                                                                        "the given version id is not compatible with the pattern for that field (P000): " +
                                                                        professorOrganizationForVersion;
                                                    }
                                                } else {
                                                    // in case the passed version id already exists an error is risen
                                                    errorIdentifier = ERR_file_format;
                                                    errorHandling = "Error: file: " + courseFileName + "row: " + to_string(row) +
                                                                    "the given version id already exist and it has been previously set: " +
                                                                    professorOrganizationForVersion;
                                                }
                                            } else {
                                                // the dummy course is a copy of the course already memorized in courses list a part for the professor organization
                                                // and the version id so if the version id field read is empty a clear of the same field on the dummy element is necessary
                                                dummyCourse.clearParallelCourseId();
                                            }
                                            versionCounter++;
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        default:{
                                            errorIdentifier = ERR_file_format;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                            " unexpected element number there may be an incorrect number or type of brackets, plese controll the regular professor and version id of the element " +
                                                            to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
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
                                            if (patternFieldForEachLevel[level - 1] == 0) {
                                                dummyAssociateProfessor.setIsMain(true);
                                                if (!mainProfessorCourse.empty() && professorOrganizationForVersion.empty()) {
                                                    dummyAssociateProfessor.setToCek(true);
                                                    professorOrganizationForVersion = mainProfessorCourse;
                                                } else if (mainProfessorCourse.empty() && !professorOrganizationForVersion.empty()) {
                                                    dummyAssociateProfessor.setToCek(true);
                                                } else if (mainProfessorCourse != professorOrganizationForVersion) {
                                                    errorIdentifier = ERR_file_format;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                    "the regular professor for the version " + dummyCourse.getParallelCoursesId() + " is " +
                                                                    mainProfessorCourse + " which is different from the one on first place of  the course organization: " +
                                                                    professorOrganizationForVersion;
                                                }
                                            }
                                            if ((!professorOrganizationForVersion.empty()) && (errorIdentifier == OK)) {
                                                itProfessorFromFindConst = findProfessor(professorList, professorOrganizationForVersion);
                                                itProfessorFromFind = constItToNonConstIt(professorList, itProfessorFromFindConst);
                                                if (itProfessorFromFindConst != professorList.cend()) {
                                                    dummyAssociateProfessor.setProfessorPointer(itProfessorFromFind);
                                                } else {
                                                    // here a new professor is created if the professor read from the file can't be found in the professor's list
                                                    // (it must be controlled in the professor's list if the other fields are filled in)
                                                    if (!dummyProfessor.setId(professorOrganizationForVersion)) {
                                                        errorIdentifier = ERR_file_format;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                        "incorrect professor id: " + professorOrganizationForVersion;
                                                    }
                                                    if (errorIdentifier == OK) {
                                                        professorList.push_back(dummyProfessor);
                                                        itProfessorFromFindConst = findProfessor(professorList, professorOrganizationForVersion);
                                                        itProfessorFromFind = constItToNonConstIt(professorList, itProfessorFromFindConst);
                                                        if (itProfessorFromFind != professorList.end()) {
                                                            dummyAssociateProfessor.setProfessorPointer(itProfessorFromFind);
                                                        } else {
                                                            errorIdentifier = ERR_file_format;
                                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                            "error creating the unexisting professor with id: " + professorOrganizationForVersion;
                                                        }
                                                    }
                                                }
                                            } else {
                                                // the associate professor has a "pointer" to the relative professor
                                                // in cases this isn't specified it'll be inherited but for now it'll point to the end of the professor's list
                                                dummyAssociateProfessor.setProfessorPointer(professorList.end());
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 1:{
                                            if (!professorOrganizationForVersion.empty()) {
                                                try {
                                                    if (!dummyAssociateProfessor.setLessonH(stoi(professorOrganizationForVersion))) {
                                                        errorIdentifier = ERR_hour_set;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                        "the given lesson hour is below 0 (zero): " + professorOrganizationForVersion;
                                                    }
                                                }
                                                catch (const invalid_argument& excepFromStoi) {
                                                    errorIdentifier = ERR_stoi_conversion;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                    " incorrect element impossible to convert the lesson hour field to int: " +
                                                                    professorOrganizationForVersion + " (field number: " + to_string(patternFieldForEachLevel[level - 1]) + ")";
                                                }
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 2:{
                                            if (!professorOrganizationForVersion.empty()) {
                                                try {
                                                    if (!dummyAssociateProfessor.setExerciseH(stoi(professorOrganizationForVersion))) {
                                                        errorIdentifier = ERR_hour_set;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                        "the given exercise hour is below 0 (zero): " + professorOrganizationForVersion;
                                                    }
                                                }
                                                catch (const invalid_argument &excepFromStoi) {
                                                    errorIdentifier = ERR_stoi_conversion;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                    " incorrect element impossible to convert the exercise hour field to int: " +
                                                                    professorOrganizationForVersion + " (field number: " + to_string(patternFieldForEachLevel[level - 1]) + ")";
                                                }
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        case 3:{
                                            if (!professorOrganizationForVersion.empty()) {
                                                try {
                                                    if (!dummyAssociateProfessor.setLabH(stoi(professorOrganizationForVersion))) {
                                                        errorIdentifier = ERR_hour_set;
                                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                        "the given laboratory hour is below 0 (zero): " + professorOrganizationForVersion;
                                                    }
                                                }
                                                catch (const invalid_argument &excepFromStoi) {
                                                    errorIdentifier = ERR_stoi_conversion;
                                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                                    " incorrect element impossible to convert the laboratory hour field to int: " +
                                                                    professorOrganizationForVersion + " (field number: " + to_string(patternFieldForEachLevel[level - 1]) + ")";
                                                }
                                            }
                                            // here the associate professor should be complete with all the data, so below if there is no errors
                                            // a push to a temporary list is made
                                            if (errorIdentifier == OK) {
                                                dummyAssociateProfessorsList.push_back(dummyAssociateProfessor);
                                                dummyAssociateProfessor.clear(professorList.end());
                                            }
                                            patternFieldForEachLevel[level - 1]++;
                                            break;
                                        }
                                        default:{
                                            errorIdentifier = ERR_file_format;
                                            errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                            " unexpected element number there may be an incorrect number or type of brackets, please control the professor (id: " +
                                                            dummyAssociateProfessor.getProfessorPointer()->getId() + ") and version (id: " + dummyCourse.getParallelCoursesId() +
                                                            "of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                            break;
                                        }
                                    }
                                    break;
                                }
                                default:{
                                    errorIdentifier = ERR_file_format;
                                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
                                                    " unexpected element number there may be an incorrect number or type of brackets, please control the professor (id: " +
                                                    dummyAssociateProfessor.getProfessorPointer()->getId() + ") and version (id: " + dummyCourse.getParallelCoursesId() +
                                                    "of the element " + to_string(patternFieldForEachLevel[0]/2) + " of the course's professor organization";
                                    break;
                                }
                            }
                            level-=levelDecrement;
                            if (level == 0) {
                                patternFieldForEachLevel[2] = 0;
                                if (errorIdentifier == OK) {
                                    dummyCourse.setListAssistantNoChecks(dummyAssociateProfessorsList);
                                    dummyCoursesList.push_back(dummyCourse);
                                    dummyAssociateProfessorsList.clear();
//                                    if (== OK) {
//                                    } else {
//                                        errorIdentifier = ERR_hour_set;
//                                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row + 1) +
//                                                        " version number: " + to_string(versionCounter) + " when pushing db temporary list " +
//                                                        errorLine;
//                                    }
                                }
                            }
                        }
                        // here the row of given file is completely decoded
                        // the following part will take care of controlling the database (databaseCourseList) with regard to updated versions
                        if (errorIdentifier == OK) {
                            if (itCourseListYearConst != databaseCourseList.end()) {
                                if (!fillCourseDatabase(errorLine, versionCounter, databaseCourseList, dummyCoursesList, professorList)) {
                                    errorIdentifier = ERR_update_database;
                                    errorHandling = "Error: file: " + courseFileName + " the line defining an update for course " +
                                                    itCourseListYearConst->getId() + " and year " + to_string(itCourseListYearConst->getStartYear()) +
                                                    "-" + to_string(itCourseListYearConst->getStartYear() + 1) + " has " + errorLine;
                                }
                            } else if (itCourseListIdConst != databaseCourseList.end()) {
                                if (!insertCourseDatabase(errorLine, versionCounter, databaseCourseList, dummyCoursesList, professorList)) {
                                    errorIdentifier = ERR_update_database;
                                    errorHandling = "Error: file: " + courseFileName + " the line defining an insertion for course " +
                                                    itCourseListYearConst->getId() + " and year " + to_string(dummyCourse.getStartYear()) + "-" +
                                                    to_string(dummyCourse.getStartYear() + 1) + " which define a new course's organization has " + errorLine;
                                }
                            }
                        }
                    } else {
                        // here the square brackets are present but empty so is an error
                        errorIdentifier = ERR_file_format;
                        errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row) +
                                        "the parallel version organization has the field identifiers (\"[]\") but without contents";
                    }
                } else {
                    errorIdentifier = ERR_file_format;
                    errorHandling = "Error: file: " + courseFileName + " row: " + to_string(row) +
                                    " incorrect start and ending character of the pattern: " + courseProfessorOrganization.front() +
                                    " " + courseProfessorOrganization.back();
                }
            } else {
                if (dummyCourse.getParallelCoursesNumber() <= itCourseListIdConst->getParallelCoursesNumber()) {
                    if (itCourseListYearConst != databaseCourseList.end()) {
                        // this part will be performed if both the id and the academic year is present, and is going to update the database with the correct data
                        if (!fillCourseDatabase(errorLine, dummyCourse.getParallelCoursesNumber(), databaseCourseList, dummyCoursesList, professorList)) {
                            errorIdentifier = ERR_update_database;
                            errorHandling = "Error: file: " + courseFileName + " the line defining an update for course " + itCourseListYearConst->getId() +
                                            " and year " + to_string(itCourseListYearConst->getStartYear()) + "-" + to_string(itCourseListYearConst->getStartYear() + 1) +
                                            " has " + errorLine;
                        }
                    } else if (itCourseListIdConst != databaseCourseList.end()) {
                        // this part will be done only if the course id is present and will result in a fill of missing fields
                        // in the dummy list and an insertion of them in database in the  proper position
                        if (insertCourseDatabase(errorLine, dummyCourse.getParallelCoursesNumber(), databaseCourseList, dummyCoursesList, professorList)) {
                            errorIdentifier = ERR_update_database;
                            errorHandling = "Error: file: " + courseFileName + " the line defining an insertion for course " + itCourseListYearConst->getId() +
                                            " and year " + to_string(dummyCourse.getStartYear()) + "-" + to_string(dummyCourse.getStartYear() + 1) +
                                            " which define a new course's organization has " + errorLine;
                        }
                    }
                } else {
                    errorIdentifier = ERR_parallel_course_number_inherit;
                    errorHandling = "Error: file: " + courseFileName + " the line defining an insertion for course " + itCourseListYearConst->getId() +
                                    " and year " + to_string(dummyCourse.getStartYear()) + "-" + to_string(dummyCourse.getStartYear() + 1) +
                                    " require a complete inheritance of course's hour organization but the number of version to insert is greater than the number from which is possible to inherit data";
                }
            }
            row++;
        }
    }
    if (fileName.is_open()) {
        fileName.close();
    }
    return (int) errorIdentifier;
}
