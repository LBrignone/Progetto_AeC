//
// Created by Luca Brignone on 18/08/22.
//

#include "CourseOfStudy.h"

string CourseOfStudy::getCourseOfStudyId() const {
    return _courseOfStudyId;
}

bool CourseOfStudy::generateCourseOfStudyId(const string& lastCourseOfStudy) {
    int i_tmpCourseId;
    stringstream ss_tmpCourseId;

    if (!lastCourseOfStudy.empty()) {
        if (lastCourseOfStudy[0] == 'C' && lastCourseOfStudy.size() == 4) {
            try {
                i_tmpCourseId = stoi(lastCourseOfStudy.substr(1,3), nullptr, 10);
            }
            catch (const invalid_argument& excepFromStoi) {
                return false;
            }
            i_tmpCourseId++;
            ss_tmpCourseId << 'C' << setfill('0') << setw(3) << i_tmpCourseId;
            _courseOfStudyId = ss_tmpCourseId.str();
            return true;
        } else {
            return false;
        }
    } else {
        _courseOfStudyId = "C001";
        return true;
    }
}

bool CourseOfStudy::setCourseOfStudyId(const string& toSetcourseOfStudyId) {
    if (!toSetcourseOfStudyId.empty()) {
        if (toSetcourseOfStudyId[0] == 'C' && toSetcourseOfStudyId.size() == 4) {
            try {
                stoi(toSetcourseOfStudyId.substr(1,3), nullptr, 10);
            }
            catch (const invalid_argument& excepFromStoi) {
                return false;
            }
            _courseOfStudyId = toSetcourseOfStudyId;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

string CourseOfStudy::getGraduationType() const {
    return graduationTypeVect[(int)_graduationType];
}

bool CourseOfStudy::setGaraduationType(const string& graduationType) {
    int i = 0;
    while ((graduationTypeVect[i] != graduationType) && (i < graduationTypeVect.size())) {
        i++;
    }
    if(i < 2) {
        _graduationType = (t_graduationType)i;
        return true;
    } else {
        _graduationType = NO_TYPE;
        return false;
    }
}

const list<string>& CourseOfStudy::getListOfCoursesBySemester(const int & key) const {
    return _semesterOfCourse.at(key);
}

// the course id is inserted in the map with regard to given semester, with proper controls about course coherency
bool CourseOfStudy::setListOfCoursesBySemester(string& errorHandling, const int& semesterKey, const string& courseId) {
    bool statusToReturn = true;
    list<string> tmpListOfCourses;
    map<int, list<string>>::const_iterator itMapOfCoursesBySemester;
    list<string>::const_iterator itCoursesList;

    if (!courseId.empty() && (courseId.size() == 7)){
        for (int i = 0; i < courseId.size(); ++i) {
            if (i == 0) {
                if (courseId[i] != '0') {
                    statusToReturn = false;
                    i = 7;
                }
            } else if (i == 1) {
                if (courseId[i] != '1') {
                    statusToReturn = false;
                    i = 7;
                }
            } else if ((courseId[i] < 'A') || (courseId[i] > 'Z')) {
                    statusToReturn = false;
                    i = 7;
            } else {
                statusToReturn = true;
            }
        }
    } else {
        statusToReturn = false;
    }
    if (statusToReturn) {
        if (((_graduationType == BS) && ((semesterKey > -2) && (semesterKey < 7))) ||
            ((_graduationType == MS) && ((semesterKey > -2) && (semesterKey < 5)))) {
            // here it is performed a control which aims at find possible duplication of the course in all semesters
            // if the course id is present in the list of ended courses this duplication will be neglected
            itMapOfCoursesBySemester = _semesterOfCourse.cbegin();
            while ((itMapOfCoursesBySemester != _semesterOfCourse.cend()) && statusToReturn) {
                itCoursesList = itMapOfCoursesBySemester->second.cbegin();
                while ((itCoursesList != itMapOfCoursesBySemester->second.cend()) && statusToReturn) {
                    if ((courseId == *itCoursesList) && (itMapOfCoursesBySemester->first == semesterKey)) {
                        statusToReturn = false;
                        errorHandling = "the course is already present in the semester";
                    }
                    itCoursesList++;
                }
                itMapOfCoursesBySemester++;
            }
            if (statusToReturn) {
                this->_semesterOfCourse[semesterKey].push_back(courseId);
            }
        } else {
            statusToReturn = false;
            errorHandling = "semester not congruent with the specified graduation type ";
        }
    } else {
        errorHandling = "the given course id doesn't match the pattern for the field (01XXXXX): ";
    }
    return statusToReturn;
}

bool CourseOfStudy::deleteEndedCourseFormActiveCourse(string& errorHandling, const string& courseId, const bool& allInactive) {
    string tmpError;
    int startSemesterSearch = 0, semesterMapIndex = 0;

    while ((startSemesterSearch < 6) && (semesterMapIndex != -2) && errorHandling.empty()) {
        semesterMapIndex = this->findCourse(startSemesterSearch, courseId);
        if ((semesterMapIndex != -2) && (semesterMapIndex != -1)) {
            // allInactive = false -> all the courses are "non_attivo", so the remove is necessary
            if (!allInactive) {
                this->_semesterOfCourse[semesterMapIndex].remove(courseId);
            }
            // here the ended course's list is looked for the wanted id so that if it already exists, it won't be rewritten
            if (this->findCourse(-1, courseId) != -1) {
                if (!this->setListOfCoursesBySemester(tmpError, -1, courseId)) {
                    errorHandling = tmpError;
                }
            }
            startSemesterSearch = semesterMapIndex;
        }
        startSemesterSearch++;
    }
    return errorHandling.empty();
}

bool CourseOfStudy::activateCourseFormEndedCourse(string& errorHandling, const string& courseId, const bool& allActive) {
    string tmpError;
    int semesterMapIndex;

    semesterMapIndex = this->findCourse(-1, courseId);
    if (semesterMapIndex == -1) {
        _semesterOfCourse[-1].remove(courseId);
        return true;
    }
    return false;
}

int CourseOfStudy::findCourse(int startSemester, const string& courseId) {
    int returnKey = -2;
    int i = startSemester;
    while ((i < 6) && (returnKey == -2)) {
        if(_semesterOfCourse.find(i) != _semesterOfCourse.end())
        {
            if(std::find(_semesterOfCourse[i].begin(), _semesterOfCourse[i].end(), courseId) != _semesterOfCourse[i].end()) {
                returnKey = i;
            }
        }
        i++;
    }
    return returnKey;
}

int CourseOfStudy::findCourse(int startSemester, const string& courseId) const {
    int returnKey = -2;
    int i = startSemester;
    while ((i < 6) && (returnKey == -2)) {
        if(_semesterOfCourse.find(i) != _semesterOfCourse.end())
        {
            if(std::find(_semesterOfCourse.at(i).begin(), _semesterOfCourse.at(i).end(), courseId) != _semesterOfCourse.at(i).end()) {
                returnKey = i;
            }
        }
        i++;
    }
    return returnKey;
}

ostream& CourseOfStudy::operator <<(ostream& os) const {
    bool flag = false;
    list<string>::const_iterator itListOfCourses;
    map<int, list<string>>::const_iterator itMapBySemester;
    map<int, list<string>>::const_iterator itFromFind, itEnd;

    os << _courseOfStudyId << ";" << graduationTypeVect[_graduationType] << ";" << "[";
    itMapBySemester = _semesterOfCourse.cbegin();
    // it is necessary an increment the map's iterator if the map already contains the ended courses because the first element
    // of the map is the list of ended courses but as output on database is necessary to previously print all the active courses by semester
    itFromFind = _semesterOfCourse.find(-1);
    if (itFromFind == _semesterOfCourse.end()) {
        flag = true;
    } else {
        itMapBySemester++;
    }
    // print of active courses
    while (itMapBySemester != _semesterOfCourse.cend()) {
        if (itMapBySemester != _semesterOfCourse.find(0)) {
            os << ",";
        }
        itListOfCourses = itMapBySemester->second.cbegin();
        os << "{";
        while (itListOfCourses != itMapBySemester->second.cend()) {
            if (itListOfCourses != itMapBySemester->second.cbegin()) {
                os << ",";
            }
            os << *itListOfCourses;
            itListOfCourses++;
        }
        os << "}";
        itMapBySemester++;
    }
    os << "]";
    // print of ended courses
    if (!flag) {
        os << ";[";
        itListOfCourses = _semesterOfCourse.at(-1).cbegin();
        while (itListOfCourses != _semesterOfCourse.at(-1).cend()) {
            if (itListOfCourses != _semesterOfCourse.at(-1).cbegin()) {
                os << ",";
            }
            os << itListOfCourses->c_str();
            itListOfCourses++;
        }
        os << "]";
    }
    return os;
}