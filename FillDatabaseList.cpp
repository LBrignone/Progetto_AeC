//
// Created by Luca Brignone on 24/09/22.
//

#include "FillDatabaseList.h"

// if the database has the course we are looking for (course id + academic year) an update of itself is performed
// possible version(s) not included previously are inserted consequentially to their relative course (course id + academic year)
bool fillCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCoursesList, list<Professor>& professorList) {
    int i = 0, accLessonH, accExH, accLabH, courseVersion = 0;
    bool errorInListElementNumber = false, errorInVersion = false, errorInProfessorList = false, errorInProfessorHour = false, errorInData = false, errorInFill = false, fromInsert;
    string errorString;
    list<Course>::iterator itCourseMain, itCourseDummy;
    list<AssociateProfessor>::iterator itAssociateProfessorHourCheck;
    list<AssociateProfessor> associateProfessorFromDatabase;

    itCourseDummy = dummyCoursesList.begin();
    if (dummyCoursesList.size() == versionCounter) {
        while ((i < versionCounter) && !errorInProfessorList && !errorInProfessorHour && !errorInData && !errorInVersion) {
            accLessonH = 0;
            accExH = 0;
            accLabH = 0;
            fromInsert = false;
            itCourseMain = findCourse(databaseList, itCourseDummy->getId(), itCourseDummy->getStartYear(),
                                      generateVersion(versionCounter));

            if (versionCoherencyTest(errorString, i, itCourseDummy->getParallelCoursesId()) || itCourseDummy->getParallelCoursesId().empty()) {
                if (itCourseMain != databaseList.end()) {
                    if ((itCourseMain->isActiveCourse() != itCourseDummy->isActiveCourse()) && !itCourseDummy->getActiveCourseFieldEmpty()) {
                        itCourseMain->setActiveCourse(itCourseDummy->isActiveCourse());
                    }
                    if (itCourseDummy->getParallelCoursesNumber() != -1) {
                        if (itCourseMain->getParallelCoursesNumber() != itCourseDummy->getParallelCoursesNumber()) {
                            itCourseMain->setParallelCoursesNumber(itCourseDummy->getParallelCoursesNumber());
                        }
                    }
                    if (itCourseDummy->getExamType() != "NO_TYPE") {
                        itCourseMain->setExamType(itCourseDummy->getExamType());
                    }
                    if (itCourseDummy->getExamClassroomType() != '\0') {
                        if (itCourseMain->getExamClassroomType() != itCourseDummy->getExamClassroomType()) {
                            itCourseMain->setExamClassroomType(itCourseDummy->getExamClassroomType());
                        }
                    }
                    if (itCourseDummy->getEntranceTime() != -1) {
                        itCourseMain->setEntranceTime(itCourseDummy->getEntranceTime());
                    }
                    if (itCourseDummy->getExitTime() != -1) {
                        itCourseMain->setExitTime(itCourseDummy->getExitTime());
                    }
                    if (itCourseDummy->getExamDuration() != -1) {
                        itCourseMain->setExamDuration(itCourseDummy->getExamDuration());
                    }
                    if (itCourseDummy->getPartecipants() != -1) {
                        itCourseMain->setPartecipants(itCourseDummy->getPartecipants());
                    }
                    if (!itCourseDummy->getListAssistant().empty()) { // if there's something to modify it'll be updated with the function otherwise the database remain intact

                        associateProfessorFromDatabase = itCourseMain->getListAssistant();
                        if (!fillAssociateProfessor(errorString, itCourseMain->getListAssistant(), itCourseDummy->getListAssistant(), professorList.end())) {
                            errorInProfessorList = true;
                            errorHandling = errorString;
                        } else {
                            // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                            if (itCourseMain->setListAssistant(associateProfessorFromDatabase, errorString) < 255) {
                                errorInProfessorHour = true;
                                errorHandling = errorString;
                            }
                        }
                    }
                    itCourseMain->setListGroupedId(itCourseDummy->getListGroupedId());
                } else {
                    // here the database course version's list is ended but the inserted course versions has some more elements
                    // the exceeding elements must be controlled so that all the fields are complete with data
                    if (itCourseDummy->getActiveCourseFieldEmpty()) {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined if the given course is active";
                    }
                    if (itCourseDummy->getParallelCoursesNumber() == -1) {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the number of parallel courses";
                    }
                    if (itCourseDummy->getExamType() == "NO_TYPE") {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the type of exam";
                    }
                    if (itCourseDummy->getExamClassroomType() == '\0') {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the classroom type";
                    }
                    if (itCourseDummy->getEntranceTime() == -1) {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the entrance time";
                    }
                    if (itCourseDummy->getExitTime() == -1) {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the exit time";
                    }
                    if (itCourseDummy->getExamDuration() == -1) {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the exam duration";
                    }
                    if (itCourseDummy->getPartecipants() != -1) {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the number of enrolled students";
                    }
                    if (!itCourseDummy->getListAssistant().empty()) { // if there's something to modify it'll be updated with the function otherwise the database remain intact
                        associateProfessorFromDatabase = itCourseMain->getListAssistant();
                        if (!fillAssociateProfessor(errorString, associateProfessorFromDatabase, itCourseDummy->getListAssistant(), professorList.end())) {
                            errorInProfessorList = true;
                            errorHandling = errorString;
                        } else {
                            // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                            if (itCourseMain->setListAssistant(associateProfessorFromDatabase, errorString) < 255) {
                                errorInProfessorHour = true;
                                errorHandling = errorString;
                            }
                        }
                    } else {
                        errorInData = true;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + to_string(i) + "has not defined the professor's hour organization list";
                    }
                    // after the given course is controlled the same one is inserted in the database maintaining the versions ascending order
                    if (!errorInData) {
                        itCourseMain++;
                        databaseList.insert(itCourseMain, *itCourseDummy);
                        fromInsert = true;
                    }
                }
            } else {
                errorInVersion = true;
                errorHandling = "the version in dummy course's list doesn't respect the ascending order";
            }
            if (!fromInsert) {
                itCourseMain++;
            }
            itCourseDummy++;
            i++;
        }
        // here the dummy course version's list is ended, but the database has more versions for the given id and year that must be erased
        itCourseDummy--;
        itCourseMain = findCourse(databaseList, generateVersion(i), itCourseDummy->getStartYear());
        while (itCourseMain != databaseList.end()) {
            databaseList.erase(itCourseMain);
            i++;
            itCourseMain = findCourse(databaseList, generateVersion(i), itCourseDummy->getStartYear());
        }
    } else {
        errorInListElementNumber = true;
        errorHandling = "the number of elements in dummy list is incoherent with regard to counter of versions";
    }

    if (!errorInListElementNumber && !errorInProfessorList && !errorInProfessorHour && !errorInVersion && !errorInData) {
        return true;
    } else {
        return false;
    }
}

// if the course we are looking for in database has only the course id the missing element are inherited from last element of database with same course id
// version(s) previously not included in database rise an error due to incapability of inheriting missing elements for that version(s)
bool insertCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCourseList, list<Professor>& profesorList) {
    int i = 0;
    bool errorNumVersion = false, errorInProfessorList = false, errorInProfessorHour = false;
    string errorLine;
    list<Course>::iterator itDummyCourseList, itLastDbCourseId;
    list<AssociateProfessor> associateProfessorFromDummyNewOrg;
    list<Course>::iterator itDbCourseId;

    // first the course id that we are looking for is searched in database
    itLastDbCourseId = findCourse(databaseList, dummyCourseList.begin()->getId());
    if (itLastDbCourseId == databaseList.end()) {
        // when the id previously found exist the last element of it is searched
        itLastDbCourseId = findCourseLastForId(databaseList, dummyCourseList.begin()->getId(), itLastDbCourseId);
        // at the same time the first element with same course id and academic year is searched (the P001 version is expected)
        itDbCourseId = findCourse(databaseList, itLastDbCourseId->getId(), itLastDbCourseId->getStartYear(),generateVersion(i));
    }
    itDummyCourseList = dummyCourseList.begin();
    if ((dummyCourseList.begin()->getParallelCoursesNumber() == versionCounter) && (itLastDbCourseId->getParallelCoursesNumber() <= versionCounter)){
        while (i < versionCounter) {
            if ((versionCoherencyTest(errorLine, i, itDummyCourseList->getParallelCoursesId()) || itDummyCourseList->getParallelCoursesId().empty()) && versionCoherencyTest(errorLine, i, itDbCourseId->getParallelCoursesId())) {
                if (!itDummyCourseList->getActiveCourseFieldEmpty()) {
                    itDummyCourseList->setActiveCourse(itDbCourseId->isActiveCourse());
                }
                if (itDummyCourseList->getParallelCoursesNumber() == -1) {
                    itDummyCourseList->setParallelCoursesNumber(itDbCourseId->getParallelCoursesNumber());
                }
                if (itDummyCourseList->getExamType() == "NO_TYPE") {
                    itDummyCourseList->setExamType(itDbCourseId->getExamType());
                }
                if (itDummyCourseList->getExamClassroomType() == '\0') {
                    itDummyCourseList->setExamClassroomType(itDbCourseId->getExamClassroomType());
                }
                if (itDummyCourseList->getEntranceTime() == -1) {
                    itDummyCourseList->setEntranceTime(itDbCourseId->getEntranceTime());
                }
                if (itDummyCourseList->getExitTime() == -1) {
                    itDummyCourseList->setExitTime(itDbCourseId->getExitTime());
                }
                if (itDummyCourseList->getExamDuration() == -1) {
                    itDummyCourseList->setExamDuration(itDbCourseId->getExamDuration());
                }
                if (itDummyCourseList->getPartecipants() == -1) {
                    itDummyCourseList->setPartecipants(itDbCourseId->getPartecipants());
                }
                // if there's some missing field in dummy course's list it will be inherited
                // otherwise when the dummy list is empty all the associate professors' organization will be inherited from the database
                if (!itDummyCourseList->getListAssistant().empty()) {
                    associateProfessorFromDummyNewOrg = itDummyCourseList->getListAssistant();
                    if (!insertAssociateProfessor(errorLine, itDbCourseId->getListAssistant(), associateProfessorFromDummyNewOrg, profesorList.end())) {
                        errorInProfessorList = true;
                        errorHandling = errorLine;
                    } else {
                        // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                        if (itDummyCourseList->setListAssistant(associateProfessorFromDummyNewOrg, errorLine) < 255) {
                            errorInProfessorHour = true;
                            errorHandling = errorLine;
                        }
                    }
                }
            } else {
                errorNumVersion = true;
                errorHandling = "the version to be handled doesn't respect the ascending order";
            }
            itDbCourseId++;
            itDummyCourseList++;
            i++;
        }
        itLastDbCourseId++;
        if (!errorInProfessorHour && !errorInProfessorList && !errorNumVersion) {
            databaseList.insert(itLastDbCourseId, dummyCourseList.begin(), dummyCourseList.end());
        }
    } else {
        errorNumVersion = true;
        errorHandling = " the number of version(s) for the new course doesn't match the number of version(s) coming from the database's last element for same id";
    }

    if (!errorNumVersion && !errorInProfessorList && !errorInProfessorHour) {
        return true;
    } else {
        return false;
    }
}

// the list of associate professor is updated in database and if there's some exceding element is handled with proper controls
// performed only for course id + academic year
bool fillAssociateProfessor (string& errorHandling, list<AssociateProfessor>& associateProfessorListDb, const list<AssociateProfessor> &associateProfessorListDummy, list<Professor>::iterator professorListEnd) {
    bool errorIncoherent = false, errorMissing = false; // error identifiers
    bool writeOrInherit;
    int associateProfessorElement = 0;
    list<AssociateProfessor>::iterator itAssociateProfessorMain;
    list<AssociateProfessor>::const_iterator itAssociateProfessorDummy;

    itAssociateProfessorMain = associateProfessorListDb.begin();
    itAssociateProfessorDummy = associateProfessorListDummy.begin();
    while (itAssociateProfessorDummy != associateProfessorListDummy.end()) {
        // the following if is necessary to separate two behaviour
        // - the number of element of the two lists are coherent in number (same number of elements till now)
        // - the dummy list of associate professor is longer than the main (database) one
        //	 the exceeding elements will be handled in the else because a verification of all fields regading the dummy
        //	 list of professor with their respective values must be performed
        writeOrInherit = false;
        if (itAssociateProfessorMain != associateProfessorListDb.end()) {
            if (itAssociateProfessorDummy->getIsMain() && itAssociateProfessorDummy->getToCheck()) {
                // the given regular professor here appear only before the version id or as first field in the hour's organization for the professor
                // in the file, this necessitates to control the coherency for the given id with the database, if they match is OK
                if (itAssociateProfessorDummy->getProfessorPointer()->getId() == itAssociateProfessorMain->getProfessorPointer()->getId()) {
                    itAssociateProfessorMain->setProfessorPointer(itAssociateProfessorDummy->getProfessorPointer());
                    writeOrInherit = true;
                } else {
                    errorIncoherent = true;
                    errorHandling = "the given regular professor ("+ itAssociateProfessorDummy->getProfessorPointer()->getId() +") does not coincide with the regular professor in database";
                }
            } else {
                // this part is common for any professor in the list, is only needed to distinguish if the id field is empty, in which case the id
                // will be inherited (nothing is modified in database)
                if (itAssociateProfessorDummy->getProfessorPointer() != professorListEnd) {
                    itAssociateProfessorMain->setProfessorPointer(itAssociateProfessorDummy->getProfessorPointer());
                    writeOrInherit = true;
                }
            }
        } else {
            // here the list of associate professor in database is finished so missing fields couldn't be inherited
            // here will take place all the controls to guarantee the presence of all fields
            if (itAssociateProfessorDummy->getProfessorPointer() != professorListEnd) {
                itAssociateProfessorMain->setProfessorPointer(itAssociateProfessorDummy->getProfessorPointer());
            } else {
                errorMissing = true;
                errorHandling = "the first field (id) of the " + to_string(associateProfessorElement) + " element in professor organization is missing and there's no way to inherit it";
            }
            if (itAssociateProfessorDummy->getLessonH() != -1) {
                itAssociateProfessorMain->setLessonH(itAssociateProfessorDummy->getLessonH());
            } else {
                errorMissing = true;
                errorHandling = "the second field (lesson hour) of the " + to_string(associateProfessorElement) + " element in professor organization is missing and there's no way to inherit it";
            }
            if (itAssociateProfessorDummy->getExerciseH() != -1) {
                itAssociateProfessorMain->setExerciseH(itAssociateProfessorDummy->getExerciseH());
            } else {
                errorMissing = true;
                errorHandling = "the third field of the " + to_string(associateProfessorElement) + " element in professor organization is missing and there's no way to inherit it";
            }
            if (itAssociateProfessorDummy->getLabH() != -1) {
                itAssociateProfessorMain->setLabH(itAssociateProfessorDummy->getLabH());
            } else {
                errorMissing = true;
                errorHandling = "the fourth field of the " + to_string(associateProfessorElement) + " element in professor organization is missing and there's no way to inherit it";
            }
        }
        if (writeOrInherit) {
            // this part is common for all associate professors in the list (if the dummy list is not ended) in which case the given field will be
            // inherited (nothing is done to the database) or overwritten with an updated version
            // here there won't be controls because the fields are already controlled in a previous step ad now is shure they are coherent with th patterns
            if (itAssociateProfessorDummy->getProfessorPointer() != professorListEnd) {
                itAssociateProfessorMain->setProfessorPointer(itAssociateProfessorDummy->getProfessorPointer());
            }
            if (itAssociateProfessorDummy->getLessonH() != -1) {
                itAssociateProfessorMain->setLessonH(itAssociateProfessorDummy->getLessonH());
            }
            if (itAssociateProfessorDummy->getExerciseH() != -1) {
                itAssociateProfessorMain->setExerciseH(itAssociateProfessorDummy->getExerciseH());
            }
            if (itAssociateProfessorDummy->getLabH() != -1) {
                itAssociateProfessorMain->setLabH(itAssociateProfessorDummy->getLabH());
            }
        }
        itAssociateProfessorMain++;
        itAssociateProfessorDummy++;
        associateProfessorElement++;
    }
    while (itAssociateProfessorMain != associateProfessorListDb.end()) {
        associateProfessorListDb.erase(itAssociateProfessorMain);
        itAssociateProfessorMain++;
    }

    if (!errorIncoherent && !errorMissing) {
        return true;
    } else {
        return false;
    }
}

// the list of associate professor is completed with elements read from the last course corresponding version from database
// performed only for course id
bool insertAssociateProfessor (string& errorHandling, const list<AssociateProfessor>& associateProfessorListDb, list<AssociateProfessor>& associateProfessorListDummy, list<Professor>::iterator professorListEnd) {
    bool errorInData = false, errorInFormat = false;
    int associateProfessorElement = 0;
    list<AssociateProfessor>::iterator itAssociateProfessorDummy;
    list<AssociateProfessor>::const_iterator itAssociateProfessorMain;

    itAssociateProfessorMain = associateProfessorListDb.begin();
    itAssociateProfessorDummy = associateProfessorListDummy.begin();
    while (itAssociateProfessorDummy != associateProfessorListDummy.end()) {
        if (itAssociateProfessorMain != associateProfessorListDb.end()) {
            if (itAssociateProfessorDummy->getProfessorPointer() != professorListEnd) {
                if ((itAssociateProfessorDummy->getProfessorPointer()->getId() != itAssociateProfessorMain->getProfessorPointer()->getId()) && itAssociateProfessorDummy->getToCheck()) {
                    errorInData = true;
                    errorHandling = "the course's regular professor with id: " +
                                    itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " doesn't match the inherited regular professor's id: " +
                                    itAssociateProfessorMain->getProfessorPointer()->getId();
                }
            } else {
                itAssociateProfessorDummy->setProfessorPointer(itAssociateProfessorMain->getProfessorPointer());
            }
            if (itAssociateProfessorDummy->getLessonH() == -1) {
                itAssociateProfessorDummy->setLessonH(itAssociateProfessorMain->getLessonH());
            }
            if (itAssociateProfessorDummy->getExerciseH() == -1) {
                itAssociateProfessorDummy->setExerciseH(itAssociateProfessorMain->getExerciseH());
            }
            if (itAssociateProfessorDummy->getLabH() == -1) {
                itAssociateProfessorDummy->setLabH(itAssociateProfessorMain->getLabH());
            }
            if (associateProfessorElement == 0) {
                if (!itAssociateProfessorDummy->getIsMain()) {
                    errorInData = true;
                    errorHandling = "the first professor " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " is not set as regular professor";
                }
            } else {
                if (itAssociateProfessorDummy->getIsMain()) {
                    errorInData = true;
                    errorHandling = "the professor " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " is set as regular professor but s/he is not";
                }
            }
        } else {
            errorInFormat = true;
            errorHandling = "the number of associate professor is greater than the one present for the database's associate professor for the given course";
        }
        itAssociateProfessorDummy++;
        itAssociateProfessorDummy++;
        associateProfessorElement++;
    }
    if (!errorInData && !errorInFormat) {
        return true;
    } else {
        return false;
    }
}
