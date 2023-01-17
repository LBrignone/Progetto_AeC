//
// Created by Luca Brignone on 24/09/22.
//

#include "FillDatabaseList.h"
#include "ConstConversion.hpp"

// if the database has the course we are looking for (course id + academic year) an update of itself is performed
// possible version(s) not included previously are inserted consequentially to their relative course (course id + academic year)
bool fillCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCoursesList, list<Professor>& professorList) {
    t_errorCodes errorIdentifier = OK;
    int i = 0;
    bool fromInsert;
    string errorString;
    list<Course>::const_iterator itCourseMainConst, itCourseMainLastConst;
    list<Course>::iterator itCourseMain, itCourseDummy;
    list<AssociateProfessor>::iterator itAssociateProfessorHourCheck;
    list<AssociateProfessor> associateProfessorFromDatabase;

    itCourseDummy = dummyCoursesList.begin();
    if (dummyCoursesList.size() == versionCounter) {
        while ((itCourseDummy != dummyCoursesList.end()) && (errorIdentifier == OK)) {
            fromInsert = false;

            itCourseMainConst = findCourse(databaseList, itCourseDummy->getId(), itCourseDummy->getStartYear(), generateVersion(i));
            itCourseMain = constItToNonConstIt(databaseList, itCourseMainConst);
            if (itCourseDummy->getParallelCoursesId().empty()) {
                itCourseDummy->setParallelCoursesId(generateVersion(i));
            }
            if (versionCoherencyTest(errorString, i + 1, itCourseDummy->getParallelCoursesId()) || itCourseDummy->getParallelCoursesId().empty()) {
                if (itCourseMainConst != databaseList.cend()) {
                    itCourseMainLastConst = findCourseLastForIdAndYear(databaseList, itCourseDummy->getId(), itCourseDummy->getStartYear(), itCourseMainConst);
                    if (itCourseMainConst->isActiveCourse() != itCourseDummy->isActiveCourse()) {
                        itCourseMain->setActiveCourse(itCourseDummy->isActiveCourse());
                    }
                    if (itCourseMainConst->getParallelCoursesNumber() != itCourseDummy->getParallelCoursesNumber()) {
                        itCourseMain->setParallelCoursesNumber(itCourseDummy->getParallelCoursesNumber());
                    }
                    if (itCourseDummy->getExamType() != "NO_TYPE") {
                        itCourseMain->setExamType(itCourseDummy->getExamType());
                    }
                    if (itCourseDummy->getExamClassroomType() != '\0') {
                        itCourseMain->setExamClassroomType(itCourseDummy->getExamClassroomType());
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
                    // if there's something to modify it'll be updated with the function otherwise the database remain intact
                    if (!itCourseDummy->getListAssistant().empty()) {
                        associateProfessorFromDatabase = itCourseMain->getListAssistant();
                        if (!fillAssociateProfessor(errorString, associateProfessorFromDatabase, itCourseDummy->getListAssistant(), professorList)) {
                            errorIdentifier = ERR_professor_list;
                            errorHandling = "and version " + itCourseDummy->getParallelCoursesId() + " has " + errorString;
                        } else {
                            // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                            if (itCourseMain->setListAssistant(associateProfessorFromDatabase, errorString) != OK) {
                                errorIdentifier = ERR_professor_hour;
                                errorHandling = errorString;
                            }
                        }
                    }
                    itCourseMain->setListGroupedId(itCourseDummy->getListGroupedId());
                    itCourseMain++;
                } else {
                    // here the database course version's list is ended but the inserted course versions has some more elements
                    // the exceeding elements must be controlled so that all the fields are complete with data
                    if (itCourseDummy->getParallelCoursesNumber() == -1) {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the number of parallel courses";
                    } else if (itCourseDummy->getExamType() == "NO_TYPE") {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the type of exam";
                    } else if (itCourseDummy->getExamClassroomType() == '\0') {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the classroom type";
                    }else if (itCourseDummy->getEntranceTime() == -1) {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the entrance time";
                    } else if (itCourseDummy->getExitTime() == -1) {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the exit time";
                    } else if (itCourseDummy->getExamDuration() == -1) {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the exam duration";
                    } else if (itCourseDummy->getPartecipants() == -1) {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the number of enrolled students";
                    } else if (!itCourseDummy->getListAssistant().empty()) {
                        associateProfessorFromDatabase.clear();
                        if (!fillAssociateProfessor(errorString, associateProfessorFromDatabase, itCourseDummy->getListAssistant(), professorList)) {
                            errorIdentifier = ERR_professor_format;
                            errorHandling = "and version " + itCourseDummy->getParallelCoursesId() + " has " + errorString;
                        } else {
                            // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                            if (itCourseDummy->setListAssistant(itCourseDummy->getListAssistant(), errorString) != OK) {
                                errorIdentifier = ERR_professor_hour;
                                errorHandling = errorString;
                            }
                        }
                    } else {
                        errorIdentifier = ERR_missing_field;
                        errorHandling = "the course " + itCourseDummy->getId() + " with version number " + itCourseDummy->getParallelCoursesId() +
                                        "has not defined the professor's organization list";
                    }
                    // after the given course is controlled the same one is inserted in the database maintaining the versions ascending order
                    if (errorIdentifier == OK) {
                        databaseList.insert(itCourseMainLastConst, *itCourseDummy);
                    }
                }
            } else {
                errorIdentifier = ERR_version;
                errorHandling = "the version in dummy course's list doesn't respect the ascending order";
            }
            itCourseDummy++;
            i++;
        }
        // here the dummy course version's list is ended, but the database has more versions for the given id and year that must be erased
        itCourseDummy--;
        itCourseMainConst = findCourse(databaseList, itCourseDummy->getId(), itCourseDummy->getStartYear(), generateVersion(i));
        while ((itCourseMainConst != databaseList.cend()) && (errorIdentifier == OK)) {
            itCourseMain = constItToNonConstIt(databaseList, itCourseMainConst);
            databaseList.erase(itCourseMain);
            i++;
            itCourseMainConst = findCourse(databaseList, itCourseDummy->getId(), itCourseDummy->getStartYear(), generateVersion(i));
        }
    } else {
        errorIdentifier = ERR_incoherent_version_number;
        errorHandling = "the number of elements in dummy list is incoherent with regard to counter of versions";
    }

    return errorIdentifier == OK;
}

// if the course we are looking for in database has only the course id the missing element are inherited from last element
// of database with same course id version(s) previously not included in database rise an error due to incapability of
// inheriting missing elements for that version(s)
bool insertCourseDatabase (string& errorHandling, int versionCounter, list<Course>& databaseList, list<Course>& dummyCourseList, const list<Professor>& profesorList) {
    t_errorCodes errorIdentifier = OK;
    int versionNum = 1;
    string errorLine;
    list<Course>::const_iterator itLastDbCourseIdConst, itDbCourseIdConst;
    list<Course>::iterator itDummyCourseList, itLastDbCourseId, itDbCourseId;
    list<AssociateProfessor> associateProfessorFromDummyNewOrg;

    // first the course id that we are looking for is searched in database
    itLastDbCourseIdConst = findCourse(databaseList, dummyCourseList.begin()->getId());
    if (itLastDbCourseIdConst != databaseList.cend()) {
        // when the id previously found exist the last element of it is searched
        itLastDbCourseIdConst = findCourseLastForId(databaseList, dummyCourseList.begin()->getId(), itLastDbCourseIdConst);
        // the decrement below is necessary because the function returns the iterator to the next element in respect of
        // last valid element with the searched id, so in order to gain proper information about the searched last course
        // is necessary to proceed as follows
        itLastDbCourseIdConst--;
        itLastDbCourseId = constItToNonConstIt(databaseList, itLastDbCourseIdConst);
        // at the same time the first element with same course id and academic year is searched (the P001 version is expected)
        itDbCourseIdConst = findCourse(databaseList, itLastDbCourseId->getId(), itLastDbCourseId->getStartYear(),generateVersion(versionNum - 1));
        itDbCourseId = constItToNonConstIt(databaseList, itDbCourseIdConst);
        itLastDbCourseId++;
    }
    itDummyCourseList = dummyCourseList.begin();
    if (dummyCourseList.begin()->getParallelCoursesNumber() == versionCounter) {
        while ((versionNum < (versionCounter + 1)) && (errorIdentifier == OK)) {
            if (itDummyCourseList->getParallelCoursesId().empty()) {
                itDummyCourseList->setParallelCoursesId(generateVersion(versionNum - 1));
            }
            if (versionCoherencyTest(errorLine, versionNum, itDummyCourseList->getParallelCoursesId()) || itDummyCourseList->getParallelCoursesId().empty()) {
                // if there's some missing field in dummy course's list it will be inherited
                // otherwise when the dummy list is empty all the associate professors' organization will be inherited from the database
                if (itDbCourseId != itLastDbCourseId) {
                    if (!itDummyCourseList->getListAssistant().empty()) {
                        associateProfessorFromDummyNewOrg = itDummyCourseList->getListAssistant();
                        if (!insertAssociateProfessor(errorLine, itDbCourseId->getListAssistant(), associateProfessorFromDummyNewOrg, profesorList)) {
                            errorIdentifier = ERR_professor_list;
                            errorHandling = errorLine;
                        } else {
                            // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                            if (itDummyCourseList->setListAssistant(associateProfessorFromDummyNewOrg, errorLine) != OK) {
                                errorIdentifier = ERR_professor_hour;
                                errorHandling = errorLine;
                            }
                        }
                    } else {
                        if (itDummyCourseList->setListAssistant(itDbCourseId->getListAssistant(), errorLine) != OK) {
                            errorIdentifier = ERR_professor_hour;
                            errorHandling = errorLine;
                        }
                    }
                } else {
                    list<AssociateProfessor> emptyList;

                    if (!itDummyCourseList->getListAssistant().empty()) {
                        associateProfessorFromDummyNewOrg = itDummyCourseList->getListAssistant();
                        if (!insertAssociateProfessor(errorLine, emptyList, associateProfessorFromDummyNewOrg, profesorList)) {
                            errorIdentifier = ERR_professor_list;
                            errorHandling = errorLine;
                        } else {
                            // here the updated database is controlled with regard to hour coherency between the total amount and the sum for each professor
                            if (itDummyCourseList->setListAssistant(associateProfessorFromDummyNewOrg, errorLine) !=
                                OK) {
                                errorIdentifier = ERR_professor_hour;
                                errorHandling = errorLine;
                            }
                        }
                    } else {
                        errorIdentifier = ERR_version;
                        errorHandling = " the version " + generateVersion(versionNum - 1) + " haven't a version in database from which inherit";
                    }
                }
            } else {
                errorIdentifier = ERR_version;
                errorHandling = "the version to be handled doesn't respect the ascending order";
            }
            itDbCourseId++;
            itDummyCourseList++;
            versionNum++;
        }
        if (errorIdentifier == OK) {
            // the following increment is used to point at next list's element so the insertion could take
            // place in the correct place (it inserts an element before the pointed element)
            databaseList.insert(itLastDbCourseId, dummyCourseList.begin(), dummyCourseList.end());
        }
    } else {
        errorIdentifier = ERR_incoherent_version_number;
        errorHandling = " the number of version(s) for the new course doesn't match the number of version(s) coming from the database's last element for same id";
    }

    return errorIdentifier == OK;
}

// the list of associate professor is updated in database and if there's some exceeding element is handled with proper controls
// performed only for course id + academic year
bool fillAssociateProfessor (string& errorHandling, list<AssociateProfessor>& associateProfessorListDb, const list<AssociateProfessor> &associateProfessorListDummy, const list<Professor>& professorList) {
    t_errorCodes errorIdentifier = OK;
    int associateProfessorElement = 0;
    list<AssociateProfessor>::iterator itAssociateProfessorMain;
    list<AssociateProfessor>::const_iterator itAssociateProfessorDummy;

    itAssociateProfessorMain = associateProfessorListDb.begin();
    itAssociateProfessorDummy = associateProfessorListDummy.cbegin();
    while ((itAssociateProfessorDummy != associateProfessorListDummy.cend()) && (errorIdentifier == OK)) {
        // the following if is necessary to separate two behaviour
        // - the number of element of the two lists are coherent (same number of elements till now)
        // - the dummy list of associate professor is longer than the main (database) one
        //	 the exceeding elements will be handled in the else because a verification of all fields regarding the dummy
        //	 list of professor with their respective values must be performed
        if ((itAssociateProfessorMain != associateProfessorListDb.end()) && (!associateProfessorListDb.empty())) {
            if (itAssociateProfessorDummy->getIsMain() && itAssociateProfessorDummy->getToCheck()) {
                // the given regular professor here appear only before the version id or as first field in the hour's organization for the professor
                // in the file, this necessitates to control the coherency for the given id with the database, if they match is OK
                if (itAssociateProfessorDummy->getProfessorPointer()->getId() == itAssociateProfessorMain->getProfessorPointer()->getId()) {
                    itAssociateProfessorMain->setProfessorPointer(itAssociateProfessorDummy->getProfessorPointer());
                } else {
                    errorIdentifier = ERR_regular_professor;
                    errorHandling = "the given regular professor ("+ itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    ") does not coincide with the regular professor in database";
                }
            } else {
                // this part is common for any professor in the list, is only needed to distinguish if the id field is empty, in which case the id
                // will be inherited (nothing is modified in database)
                if (itAssociateProfessorDummy->getProfessorPointer() != professorList.cend()) {
                    itAssociateProfessorMain->setProfessorPointer(itAssociateProfessorDummy->getProfessorPointer());
                }
            }
            // here there won't be controls because the fields are already controlled in a previous step ad now is sure they are coherent with the patterns
            if (itAssociateProfessorDummy->getLessonH() != -1) {
                itAssociateProfessorMain->setLessonH(itAssociateProfessorDummy->getLessonH());
            }
            if (itAssociateProfessorDummy->getExerciseH() != -1) {
                itAssociateProfessorMain->setExerciseH(itAssociateProfessorDummy->getExerciseH());
            }
            if (itAssociateProfessorDummy->getLabH() != -1) {
                itAssociateProfessorMain->setLabH(itAssociateProfessorDummy->getLabH());
            }
            itAssociateProfessorMain++;
        } else {
            // here the list of associate professor in database is finished so missing fields couldn't be inherited
            // here will take place all the controls to guarantee the presence of all fields
            if (itAssociateProfessorDummy->getProfessorPointer() == professorList.cend()) {
                errorIdentifier = ERR_missing_field;
                errorHandling = "the first field (id) of the " + to_string(associateProfessorElement + 1) +
                                " element in professor organization is missing and there's no way to inherit it";
            } else if (itAssociateProfessorDummy->getLessonH() == -1) {
                errorIdentifier = ERR_missing_field;
                errorHandling = "the second field (lesson hour) of the " + to_string(associateProfessorElement + 1) +
                                " element in professor organization is missing and there's no way to inherit it";
            } else if (itAssociateProfessorDummy->getExerciseH() == -1) {
                errorIdentifier = ERR_missing_field;
                errorHandling = "the third field of the " + to_string(associateProfessorElement + 1) +
                                " element in professor organization is missing and there's no way to inherit it";
            } else if (itAssociateProfessorDummy->getLabH() == -1) {
                errorIdentifier = ERR_missing_field;
                errorHandling = "the fourth field of the " + to_string(associateProfessorElement + 1) +
                                " element in professor organization is missing and there's no way to inherit it";
            }
            if (errorIdentifier == OK) {
                associateProfessorListDb.push_back(*itAssociateProfessorDummy);
            }
        }
        itAssociateProfessorDummy++;
        associateProfessorElement++;
    }
    while (itAssociateProfessorMain != associateProfessorListDb.end()) {
        itAssociateProfessorMain = associateProfessorListDb.erase(itAssociateProfessorMain);
    }

    return errorIdentifier == OK;
}

// the list of associate professor is completed with elements read from the last course corresponding version from database
// performed only for course id
bool insertAssociateProfessor (string& errorHandling, const list<AssociateProfessor>& associateProfessorListDb, list<AssociateProfessor>& associateProfessorListDummy, const list<Professor>& professorList) {
    t_errorCodes errorIdentifier = OK;
    int associateProfessorElement = 0;
    list<AssociateProfessor>::iterator itAssociateProfessorDummy;
    list<AssociateProfessor>::const_iterator itAssociateProfessorMain;

    itAssociateProfessorMain = associateProfessorListDb.begin();
    itAssociateProfessorDummy = associateProfessorListDummy.begin();
    while (itAssociateProfessorDummy != associateProfessorListDummy.end()) {
        if (itAssociateProfessorMain != associateProfessorListDb.cend()) {
            if (itAssociateProfessorDummy->getProfessorPointer() != professorList.cend()) {
                if ((itAssociateProfessorDummy->getProfessorPointer()->getId() != itAssociateProfessorMain->getProfessorPointer()->getId()) && itAssociateProfessorDummy->getToCheck()) {
                    errorIdentifier = ERR_regular_professor;
                    errorHandling = "the course's regular professor with id: " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " doesn't match the inherited regular professor's id: " + itAssociateProfessorMain->getProfessorPointer()->getId();
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
                    errorIdentifier = ERR_regular_professor;
                    errorHandling = "the first professor " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " is not set as regular professor";
                }
            } else {
                if (itAssociateProfessorDummy->getIsMain()) {
                    errorIdentifier = ERR_regular_professor;
                    errorHandling = "the professor " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " is set as regular professor but s/he is not";
                }
            }
        } else {
            errorHandling = "the number of associate professor is greater than the one present for the database's associate professor for the given course";
            if (itAssociateProfessorDummy->getProfessorPointer() == professorList.cend()) {
                errorIdentifier = ERR_professor_pointer;
                errorHandling += " the course's professor can't be inherited from database";
            }
            if (itAssociateProfessorDummy->getLessonH() == -1) {
                errorIdentifier = ERR_professor_hour;
                errorHandling += " the course professor's lesson hour can't be inherited from database";
            }
            if (itAssociateProfessorDummy->getExerciseH() == -1) {
                errorIdentifier = ERR_professor_hour;
                errorHandling += " the course professor's exercise hour can't be inherited from database";
            }
            if (itAssociateProfessorDummy->getLabH() == -1) {
                errorIdentifier = ERR_professor_hour;
                errorHandling += " the course professor's laboratory hour can't be inherited from database";
            }
            if (associateProfessorElement == 0) {
                if (!itAssociateProfessorDummy->getIsMain()) {
                    errorIdentifier = ERR_regular_professor;
                    errorHandling += " the first professor " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " is not set as regular professor";
                }
            } else {
                if (itAssociateProfessorDummy->getIsMain()) {
                    errorIdentifier = ERR_regular_professor;
                    errorHandling += " the professor " + itAssociateProfessorDummy->getProfessorPointer()->getId() +
                                    " is set as regular professor but s/he is not";
                }
            }
        }
        itAssociateProfessorDummy++;
        if (itAssociateProfessorMain!= associateProfessorListDb.cend()) {
            itAssociateProfessorMain++;
        }
        associateProfessorElement++;
    }

    return errorIdentifier == OK;
}
