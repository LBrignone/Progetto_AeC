//
// Created by Luca Brignone on 18/08/22.
//

#include "CourseOfStudy.h"

string CourseOfStudy::getCourseOfStudyId() const {
    return _courseOfStudyId;
}

bool CourseOfStudy::generateCourseOfStudyId(const string& lastCourseOfStudy) {
    string s_tmpCourseId;
    int i_tmpCourseId;
    stringstream ss_tmpCourseId;
    if (lastCourseOfStudy.empty()) {
        s_tmpCourseId = lastCourseOfStudy.substr(1,3);
        i_tmpCourseId = stoi(s_tmpCourseId);
        i_tmpCourseId++;
        ss_tmpCourseId << 'C' << setfill('0') << setw(3) << i_tmpCourseId;
    } else {
        _courseOfStudyId = "C001";
    }
}

bool CourseOfStudy::setCourseOfStudyId(const string& toSetcourseOfStudyId) {
    _courseOfStudyId = toSetcourseOfStudyId;
}

string CourseOfStudy::getGraduationType() const {
    return graduationTypeVect[(int)_graduationType];
}

bool CourseOfStudy::setGaraduationType(const string& graduationType) {
    int i = 0;
    while ((graduationTypeVect[i] != graduationType) && (i < graduationTypeVect.size())) {
        i++;
    }
    if((graduationTypeVect[i] != graduationType)) {
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

bool CourseOfStudy::setListOfCoursesBySemester(string& errorHandlingFormPattern, const int& semesterKey, const string& Course) {
    bool flagStringFormatError = false;
    list<string> tmpListOfCourses;
    tmpListOfCourses.push_back(Course);
    if ((Course.empty()) && (Course.size() == 7)){
        for (int i = 0; i < Course.size(); ++i) {
            if (i == 0) {
                if (Course[i] != '0') {
                    flagStringFormatError = true;
                }
            } else if (i == 1) {
                if (Course[i] != '1') {
                    flagStringFormatError = true;
                }
            } else {
                if ((Course[i] < 'A') || (Course[i] > 'Z')) {
                    flagStringFormatError = true;
                }
            }
        }
    } else {
        flagStringFormatError = true;
        errorHandlingFormPattern = "the given course id doesn't match the pattern for the field (01XXXXX): ";
    }
    if ((flagStringFormatError == false) && (((_graduationType == BS) && ((semesterKey > -2) && (semesterKey < 6))) ||
            ((_graduationType == MS) && ((semesterKey > -2) && (semesterKey < 4))))) {
        //if (_semesterOfCourse.find(semesterKey) == _semesterOfCourse.end()) {
        if (_semesterOfCourse.emplace(semesterKey, tmpListOfCourses).second) {
            return true;
        } else {
            _semesterOfCourse[semesterKey].push_back(Course);
            return true;
        }
    } else {
        errorHandlingFormPattern = "semester not congruent with the specified graduation type";
        return false;
    }
}

bool CourseOfStudy::deleteEndedCourseFormActiveCourse(string& errorHandlingToDelete, const int& semester, const string& Course) {
    string tmpError;
    if(findCourse(semester, Course) == semester) {
        _semesterOfCourse[semester].remove(Course);
        if (findCourse(-1, Course) != -1) {
            if (!setListOfCoursesBySemester(tmpError, -1, Course)) {
                errorHandlingToDelete = tmpError;
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

int CourseOfStudy::findCourse(int startSemester, const string& Course) {
    int returnKey = -2;
    int i = startSemester;
    while ((i < 6) && (returnKey == -2)) {
        if(_semesterOfCourse.find(i) != _semesterOfCourse.end())
        {
            if(std::find(_semesterOfCourse[i].begin(), _semesterOfCourse[i].end(), Course) != _semesterOfCourse[i].end()) {
                returnKey = i;
            }
        }
        i++;
    }
    return returnKey;
}

ostream& CourseOfStudy::operator << (ostream& os) {
    list<string>::const_iterator itListOfCourses;
    map<int, list<string>>::const_iterator itMapBySemester;

    os << _courseOfStudyId << ";" << _graduationType << ";" << "[";
    itMapBySemester = _semesterOfCourse.cbegin();
    // it is necessary an increment previous any computation because the first element of the map is the list of ended courses
    // but as output on database is necessary to print all the active courses by semester
    itMapBySemester++;
    // print of active courses
    while (itMapBySemester != _semesterOfCourse.cend()) {
        itListOfCourses = itMapBySemester->second.cbegin();
        os << "{";
        while (itListOfCourses != itMapBySemester->second.cend()) {
            itListOfCourses++;
            if (itListOfCourses != itMapBySemester->second.cend()) {
                os << itListOfCourses->c_str() << ",";
            } else {
                os << itListOfCourses->c_str();
            }
        }
        itMapBySemester++;
        if (itMapBySemester != _semesterOfCourse.cend()) {
            os << "},";
        } else {
            os << "}];[";
        }
    }
    // print of eneded courses
    if (_semesterOfCourse[-1].empty()) {
        os << "]";
    } else {
        itListOfCourses = _semesterOfCourse[-1].cbegin();
        while (itListOfCourses != _semesterOfCourse[-1].cend()) {
            itListOfCourses++;
            if (itListOfCourses != _semesterOfCourse[-1].cend()) {
                os << itListOfCourses->c_str() << ",";
            } else {
                os << itListOfCourses->c_str() << "]";
            }
        }
    };
}