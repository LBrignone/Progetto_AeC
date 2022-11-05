//
// Created by Luca Brignone on 17/08/22.
//

#include "Course.h"

Course::Course(const Course& toCopy) {
    this->_id = toCopy._id;
    this->_startYear = toCopy._startYear;
    this->_parallelCoursesId = toCopy._parallelCoursesId;
    this->_title = toCopy._title;
    this->_cfu = toCopy._cfu;
    this->_parallelCoursesNumber = toCopy._parallelCoursesNumber;
    this->_activeCourse = toCopy._activeCourse;
    this->_courseLessonH = toCopy._courseLessonH;
    this->_courseExerciseH = toCopy._courseExerciseH;
    this->_courseLabH = toCopy._courseLabH;
    this->_assistant = toCopy._assistant;
    this->_examType = toCopy._examType;
    this->_examClassroomType = toCopy._examClassroomType;
    this->_entryTime = toCopy._entryTime;
    this->_exitTime = toCopy._exitTime;
    this->_examDuration = toCopy._examDuration;
    this->_partecipants = toCopy._partecipants;
    this->_coursesGroupedId = toCopy._coursesGroupedId;
    this->_isScheduled = toCopy._isScheduled;
    this->_constrain = toCopy._constrain;
}

string Course::getId() const {
    return _id;
}

bool Course::setId(const string &id) {
    int positionIdString = 2;
    bool errorInId = false;
    if ((id[0] == '0') && (id[1] == '1')) {
        while ((positionIdString < 6) && !errorInId) {
            if ((id[positionIdString] > 64) && (id[positionIdString] < 91)) { // A == 65 - Z == 90
                positionIdString++;
            } else {
                errorInId = true;
            }
        }
    } else {
        errorInId = true;
    }
    if (errorInId) {
        return false;
    } else {
        _id = id;
        return true;
    }
}

bool Course::generateNewId(const string &lastId) {
    bool isIncremented = false;
    int i = lastId.size() - 1;

    if (lastId != "") {
        string localCopy = lastId;
        while ((i > 1) && !isIncremented) {
            if (localCopy[i] == 'Z') {
                localCopy[i] = 'A';
                i--;
            } else {
                localCopy[i]++;
                i = localCopy.size() - 1;
                isIncremented = true;
            }
        }
        if (isIncremented) {
            _id = localCopy;
            return true;
        } else {
            return false;
        }
    } else {
        _id = "01AAAAA";
        return true;
    }
}

int Course::getStartYear() const {
    return _startYear.getYear();
}

bool Course::setStartYear(const int& startYear) {
    if (!_startYear.setYear(startYear)) { // se il set dell'anno di inizio non è riuscito
        return false;
    } else {
        return true;
    }
}

string Course::getParallelCoursesId() const {
    return _parallelCoursesId;
}

bool Course::setParallelCoursesId(const string& parallelCoursesId) {
    bool correctSequence = true;
    if (parallelCoursesId[0] == 'P') {
        for (int i = 1; i < 4; i++) {
            if ((parallelCoursesId[i] < '0') || (parallelCoursesId[i] > '9')) {
                correctSequence = false;
            }
        }
        if (correctSequence) {
            _parallelCoursesId = parallelCoursesId;
        }
    } else {
        correctSequence = false;
    }
    return correctSequence;
}

void Course::clearParallelCourseId() {
    _parallelCoursesId.clear();
}
string Course::getTitle() const {
    return _title;
}

void Course::setTitle(const string &title) {
    _title = title;
}

int Course::getCfu() const {
    return _cfu;
}

bool Course::setCfu(const int& cfu) {
    if (cfu > 0) {
        _cfu = cfu;
        return true;
    } else {
        return false;
    }
}

int Course::getParallelCoursesNumber() const {
    return _parallelCoursesNumber;
}

bool Course::setParallelCoursesNumber(const int& parallelCoursesNumber) {
    if (parallelCoursesNumber > 0) {
        _parallelCoursesNumber = parallelCoursesNumber;
        return true;
    } else {
        return false;
    }
}

bool Course::isActiveCourse() const {
    return _activeCourse;
}

void Course::setActiveCourse(const bool& activeCourse) {
    _activeCourse = activeCourse;
}

bool Course::getActiveCourseFieldEmpty() const {
    return _activeCourseFieldEmpty;
}

void Course::setActiveCourseFieldEmpty(const bool& activeCourseFieldEmpty) {
    _activeCourseFieldEmpty = activeCourseFieldEmpty;
}

int Course::getCourseLessonH() const {
    return _courseLessonH;
}

bool Course::setCourseLessonH(const int& courseLessonH) {
    if (courseLessonH >= 0) {
        _courseLessonH = courseLessonH;
        return true;
    } else {
        return false;
    }

}

int Course::getCourseExerciseH() const {
    return _courseExerciseH;
}

bool Course::setCourseExerciseH(const int& courseExerciseH) {
    if (courseExerciseH >= 0) {
        _courseExerciseH = courseExerciseH;
        return true;
    } else {
        return false;
    }
}

int Course::getCourseLabH() const {
    return _courseLabH;
}

bool Course::setCourseLabH(const int& courseLabH) {
    if (courseLabH >= 0) {
        _courseLabH = courseLabH;
        return true;
    } else {
        return false;
    }
}

list<AssociateProfessor>& Course::getListAssistant() {
    return _assistant;
}

int Course::setListAssistant(const list<AssociateProfessor>& assistant, string& errorInAssistant) {
    t_errorCodes errorIdentifier = OK;
    int tmpLessonH = 0, tmpExerciseH = 0, tmpLabH = 0;
    list<AssociateProfessor>::const_iterator itAssociateProfessor;

    itAssociateProfessor = assistant.cbegin();
    if ((_courseLessonH != -1) && (_courseExerciseH != -1) && (_courseLabH != -1)){
        while (itAssociateProfessor != assistant.cend()) {
            tmpLessonH += itAssociateProfessor->getLessonH();
            tmpExerciseH += itAssociateProfessor->getExerciseH();
            tmpLabH += itAssociateProfessor->getLabH();
            itAssociateProfessor++;
        }
        if (tmpLessonH != _courseLessonH) {
            errorIdentifier = ERR_hour_incompatibility;
            errorInAssistant = "the sum of lesson hour for professors in list is greater than the course's lesson hour " + to_string(_courseLessonH);
        } else if (tmpExerciseH != _courseExerciseH) {
            errorIdentifier = ERR_hour_incompatibility;
            errorInAssistant = "the sum of exercise hour for professors in list is greater than the course's exercise hour " + to_string(_courseExerciseH);
        } else if (tmpLabH != _courseLabH) {
            errorIdentifier = ERR_hour_incompatibility;
            errorInAssistant = "the sum of laboratory hour for professors in list is greater than the course's laboratory hour " + to_string(_courseLabH);
        }
    } else {
        if (_courseLessonH != -1) {
            errorIdentifier = ERR_hours_not_set;
            errorInAssistant = "course has no lesson hour setted";
        } else if (_courseExerciseH != -1) {
            errorIdentifier = ERR_hours_not_set;
            errorInAssistant = "course has no exercise hour setted";
        } else if (_courseLabH != -1) {
            errorIdentifier = ERR_hours_not_set;
            errorInAssistant = "course has no laboratory hour setted";
        }
    }
    if (errorIdentifier == OK) {
        _assistant = assistant;
        return (int) errorIdentifier;
    } else {
        return (int) errorIdentifier;
    }
}

void Course::setListAssistantNoChecks(const list<AssociateProfessor>& assistant) {
    _assistant = assistant;
}

int Course::appendAssistant(const AssociateProfessor &toAppend, string &errorInAppend) {
    t_errorCodes errorIdentifier = OK;
    int tmpLessonH = 0, tmpExerciseH = 0, tmpLabH = 0;
    list<AssociateProfessor>::iterator itAssociateProfessorList;

    itAssociateProfessorList = _assistant.begin();
    if ((_courseLessonH != -1) && (_courseExerciseH != -1) && (_courseLabH != -1)) {
        if (_assistant.empty()) {
            _assistant.push_back(toAppend);
        } else {
            while (itAssociateProfessorList != _assistant.end()) {
                tmpLessonH += itAssociateProfessorList->getLessonH();
                tmpExerciseH += itAssociateProfessorList->getExerciseH();
                tmpLabH += itAssociateProfessorList->getLabH();
            }
            tmpLessonH += toAppend.getLessonH();
            tmpExerciseH += toAppend.getExerciseH();
            tmpLabH += toAppend.getLabH();
            if (tmpLessonH > _courseLessonH) {
                errorIdentifier = ERR_hour_incompatibility;
                errorInAppend = "Error: the sum of lesson hour for professors in list is greater than the course's lesson hour" + to_string(_courseLessonH);
            } else if (tmpExerciseH > _courseLabH) {
                errorIdentifier = ERR_hour_incompatibility;
                errorInAppend = "Error: the sum of exercise hour for professors in list is greater than the course's lesson hour" + to_string(_courseLessonH);
            } else if (tmpLabH > _courseLabH) {
                errorIdentifier = ERR_hour_incompatibility;
                errorInAppend = "Error: the sum of laboratory hour for professors in list is greater than the course's lesson hour" + to_string(_courseLessonH);
            } else {
                _assistant.push_back(toAppend);
            }
        }
    } else {
        if (_courseLessonH == -1) {
            errorIdentifier = ERR_hours_not_set;
            errorInAppend = "Error: course has no lesson hour setted";
        } else if (_courseExerciseH == -1) {
            errorIdentifier = ERR_hours_not_set;
            errorInAppend = "Error: course has no exercise hour setted";
        } else if (_courseLabH == -1) {
            errorIdentifier = ERR_hours_not_set;
            errorInAppend = "Error: course has no laboratory hour setted";
        }
    }
    return (int) errorIdentifier;
}

string Course::getMainProfessor() {
    list<AssociateProfessor>::iterator isMainProfessor;
    isMainProfessor = _assistant.begin();

    while ((!isMainProfessor->getIsMain()) && (isMainProfessor != _assistant.end())) {
        isMainProfessor++;
    }

    if(isMainProfessor->getIsMain()) {
        return (isMainProfessor->getProfessorPointer())->getId();
    } else {
        return "";
    }
}

string Course::getExamType() const {
    return examTypeVect[(int)_examType];
}

bool Course::setExamType(const string& examType) {
    int i = 0;
    vector<string>::iterator itToExamTypeCell;

    itToExamTypeCell = find(examTypeVect.begin(), examTypeVect.end(), examType);
    if (itToExamTypeCell != examTypeVect.end()) {
        _examType = (t_examType)(itToExamTypeCell - examTypeVect.begin());
        return true;
    } else {
        _examType = NO_TYPE;
        return false;
    }
}

char Course::getExamClassroomType() const {
    return _examClassroomType;
}

bool Course::setExamClassroomType(char examClassroomType) {
    if ((examClassroomType == 'A') || (examClassroomType == 'L')) {
        _examClassroomType = examClassroomType;
        return true;
    } else {
        return false;
    }

}

int Course::getEntranceTime() const {
    return _entryTime;
}

bool Course::setEntranceTime(int entranceTime) {
    if (entranceTime > 0) {
        _entryTime = entranceTime;
        return true;
    } else {
        return false;
    }
}

int Course::getExitTime() const {
    return _exitTime;
}

bool Course::setExitTime(int exitTime) {
    if (exitTime > 0) {
        _exitTime = exitTime;
        return true;
    } else {
        return false;
    }
}

int Course::getExamDuration() const {
    return _examDuration;
}

bool Course::setExamDuration(int examDuration) {
    if (examDuration > 0) {
        _examDuration = examDuration;
        return true;
    } else {
        return false;
    }
}

int Course::getPartecipants() const {
    return _partecipants;
}

bool Course::setPartecipants(int partecipants) {
    if (partecipants >= 0) {
        _partecipants = partecipants;
        return true;
    } else {
        return false;
    }
}

list<string> Course::getListGroupedId() const {
    return _coursesGroupedId;
}

bool Course::setListGroupedId(const list<string>& groupingId) {
    list<string>::iterator groupingListIt;
    string tmpGroupingId;
    bool errorInId = false;
    int positionIdString;

    groupingListIt = _coursesGroupedId.begin();
    while ((groupingListIt != _coursesGroupedId.end()) && !errorInId) {
        positionIdString = 2;
        if ((groupingListIt->at(0) == '0') && (groupingListIt->at(1) == '1')) {
            while ((positionIdString < 6) && !errorInId) {
                if ((groupingListIt->at(positionIdString) > 64) && (groupingListIt->at(positionIdString) < 91)) { // A == 65 - Z == 90
                    positionIdString++;
                } else {
                    errorInId = true;
                }
            }
        } else {
            errorInId = true;
        }
        groupingListIt++;
    }

    if (errorInId) {
        return false;
    } else {
        _coursesGroupedId = groupingId;
        return true;
    }
}

bool Course::appendGroupedId(const string& toAppend) {
    int positionToCheck = 2;
    bool errorInId = false;
    if ((toAppend[0] == '0') && (toAppend[1] == '1')) {
        while ((positionToCheck < 7) && !errorInId) {
            if ((toAppend[positionToCheck] > 64) && (toAppend[positionToCheck] < 91)) { // A == 65 - Z == 90
                positionToCheck++;
            } else {
                errorInId = true;
            }
        }
    } else {
        errorInId = true;
    }
    if (errorInId) {
        return false;
    } else {
        _coursesGroupedId.push_back(toAppend);
        return true;
    }
}

void Course::deleteGroupedId() {
    _coursesGroupedId.erase(_coursesGroupedId.begin(), _coursesGroupedId.end());
}

bool Course::getExamIsScheduled(int i) const {
    return _isScheduled[i];
}

void Course::setExamIsScheduled(int i) {
    _isScheduled[i] = true;
}

void Course::resetExamIsScheduled(int i) {
    _isScheduled[i] = false;
}

void Course::increaseConstrain() {
    _constrain++;
}

void Course::decreaseConstrain() {
    _constrain--;
}

void Course::resetConstrain() {
    _constrain = 0;
}

void Course::inheritCourse(const list<Course>::const_iterator& toInherit) {
    this->_id = toInherit->_id;
    this->_title = toInherit->_title;
    this->_parallelCoursesNumber = toInherit->_parallelCoursesNumber;
    this->_activeCourse = toInherit->_activeCourse;
    this->_cfu = toInherit->_cfu;
    this->_courseLessonH = toInherit->_courseLessonH;
    this->_courseExerciseH = toInherit->_courseExerciseH;
    this->_courseLabH = toInherit->_courseLabH;
    this->_assistant = toInherit->_assistant;
    this->_examType = toInherit->_examType;
    this->_examClassroomType = toInherit->_examClassroomType;
    this->_entryTime = toInherit->_entryTime;
    this->_exitTime = toInherit->_exitTime;
    this->_examDuration = toInherit->_examDuration;
    this->_partecipants = toInherit->_partecipants;
    this->_coursesGroupedId = toInherit->_coursesGroupedId;
}

void Course::clearCFields() {
    _id.clear();
    _title.clear();
    _cfu = -1;
    _courseLessonH = -1;
    _courseExerciseH = -1;
    _courseLabH = -1;
}

void Course::clearAFields() {
    _startYear.setYear(0);
    _activeCourse = true;
    _parallelCoursesId.clear();
    _parallelCoursesNumber = -1;
    _assistant.clear();
    _examType = NO_TYPE;
    _examClassroomType = '\0';
    _entryTime = -1;
    _exitTime = -1;
    _examDuration = -1;
    _partecipants = -1;
    _coursesGroupedId.clear();
}

ostream& Course::printCourseOrganization(ostream& os) const {
    os << "c;" << _id << ";" << _title << ";" << _cfu << ";" << _courseLessonH << ";" << _courseExerciseH << ";" << _courseLabH << endl;
    return os;
}

ostream& Course::printCourseOrganizationAcademicYearOpening(ostream& os) const {
    os << "a;" << _startYear.getYear() << "-" << (_startYear.getYear() + 1) << ";";
    if (_activeCourse) {
        os << "attivo;";
    } else {
        os << "non_attivo;";
    }
    os << _parallelCoursesNumber << ";[";
    return os;
}

// this method uses the flag first to know if the version which is going to be printed is the first
// it is necessary to do so because there's a variation in the string to be built
ostream& Course::printCourseOrganizationVersionOpening(ostream& os, const bool& first) const {
    list<AssociateProfessor>::const_iterator itListAssociateProfessor;

    if (first) {
        os << "{";
        itListAssociateProfessor = _assistant.cbegin();
        if (itListAssociateProfessor->getIsMain()) {
            os << itListAssociateProfessor->getProfessorPointer()->getId() << ",";
        } else {
            throw isNotMain();
        }
    } else {
        os << ",{";
        itListAssociateProfessor = _assistant.cbegin();
        if (itListAssociateProfessor->getIsMain()) {
            os << itListAssociateProfessor->getProfessorPointer()->getId() << ",";
        } else {
            throw isNotMain();
        }
    }
    os << _parallelCoursesId << ",[";
    return os;
}

void Course::printCourseOrganizationAcademicYearClosing(ostream& os) const {
    list<string>::const_iterator itListGroupedCourses;

    os << "];{" << _examDuration << "," << _entryTime << "," << _exitTime << "," << examTypeVect[_examType] << "," << _examClassroomType <<
            "," << _partecipants << "};{";
    itListGroupedCourses = _coursesGroupedId.cbegin();
    while (itListGroupedCourses != _coursesGroupedId.cend()) {
        if (itListGroupedCourses != _coursesGroupedId.cbegin()) {
            os << ",";
        }
        os << itListGroupedCourses->c_str();
        itListGroupedCourses++;
    }
    os << "}";
}

Course& Course::operator=(const Course &toCopy) {
    _id = toCopy._id;
    _startYear = toCopy._startYear;
    _parallelCoursesId = toCopy._parallelCoursesId;
    _title = toCopy._title;
    _cfu = toCopy._cfu;
    _parallelCoursesNumber = toCopy._parallelCoursesNumber;
    _activeCourse = toCopy._activeCourse;
    _courseLessonH = toCopy._courseLessonH;
    _courseExerciseH = toCopy._courseExerciseH;
    _courseLabH = toCopy._courseLabH;
    _assistant = toCopy._assistant;
    _examType = toCopy._examType;
    _examClassroomType = toCopy._examClassroomType;
    _entryTime = toCopy._entryTime;
    _exitTime = toCopy._exitTime;
    _examDuration = toCopy._examDuration;
    _partecipants = toCopy._partecipants;
    _coursesGroupedId = toCopy._coursesGroupedId;
    _isScheduled = toCopy._isScheduled;
    _constrain = toCopy._constrain;
    return *this;
}

Course& Course::operator = (const list<Course>::iterator& toCopy) {
    _id = toCopy->_id;
    _startYear = toCopy->_startYear;
    _parallelCoursesId = toCopy->_parallelCoursesId;
    _title = toCopy->_title;
    _cfu = toCopy->_cfu;
    _parallelCoursesNumber = toCopy->_parallelCoursesNumber;
    _activeCourse = toCopy->_activeCourse;
    _courseLessonH = toCopy->_courseLessonH;
    _courseExerciseH = toCopy->_courseExerciseH;
    _courseLabH = toCopy->_courseLabH;
    _assistant = toCopy->_assistant;
    _examType = toCopy->_examType;
    _examClassroomType = toCopy->_examClassroomType;
    _entryTime = toCopy->_entryTime;
    _exitTime = toCopy->_exitTime;
    _examDuration = toCopy->_examDuration;
    _partecipants = toCopy->_partecipants;
    _coursesGroupedId = toCopy->_coursesGroupedId;
    _isScheduled = toCopy->_isScheduled;
    _constrain = toCopy->_constrain;
    return *this;
}

ostream& Course::operator <<(ostream& os) const {
    list<AssociateProfessor>::const_iterator itListAssociateProfessor;

    itListAssociateProfessor = _assistant.cbegin();
    while (itListAssociateProfessor != _assistant.cend()) {
        if(itListAssociateProfessor != _assistant.cbegin()) {
            os<<",";
        }
        os << "{" << itListAssociateProfessor->getProfessorPointer()->getId() << "," << itListAssociateProfessor->getLessonH()
           << "," << itListAssociateProfessor->getExerciseH() << "," <<  itListAssociateProfessor->getLabH() << "}";
        itListAssociateProfessor++;
    }
    os << "]}";
    return os;
}