//
// Created by Luca Brignone on 16/08/22.
//

#include "Professor.h"

bool Professor::getChangeInUnavail() {
    return changeInUnavail;
}

void Professor::setChangeInUnavail(const bool& newState) {
    changeInUnavail = newState;
}

void Professor::resetChangeInUnavail() {
    changeInUnavail = false;
}

bool Professor::isAvailExamProgramming(const Date& data, const Date& academicYear) {
    bool flag = true;
    map<Date, list<AvailForExam>>::iterator availMapIter;
    list<AvailForExam>::iterator availListIter;
    list<AvailForExam>::iterator availListExamIter;

    availListExamIter = _unavailabilityForExam.begin();
    availMapIter = _unavailability.find(academicYear);
    if (availMapIter != _unavailability.end()){
        availListIter = availMapIter->second.begin();
        while ((flag == true) && (availListIter != availMapIter->second.end())) {
            if ((data <= availListIter->stop) && (data >= availListIter->start)) {
                flag = false;
            }
            availListIter++;
        }
    }
    while ((flag == true) && (availListExamIter != _unavailabilityForExam.end())) {
        if ((data <= availListExamIter->stop) && (data >= availListExamIter->start)){
            flag = false;
        }
        availListExamIter ++;
    }
    return flag;
}

list<AvailForExam> Professor::getUnavailListByAcademicYear (const Date& academicYear) {
    map<Date, list<AvailForExam>>::iterator itMapByAcademicYear;

    itMapByAcademicYear = _unavailability.find(academicYear);
    return itMapByAcademicYear->second;

}

void Professor::appendUnavailability(const Date &startUnavail, const Date &stopUnavail, const Date& academicYear) {
    AvailForExam availForExamDummy;
    pair<Date, list<AvailForExam>> dummyUnavailDate;
    pair<map<Date, list<AvailForExam>>:: iterator, bool> itMapUnavailability;

    availForExamDummy.start = startUnavail;
    availForExamDummy.stop = stopUnavail;
    dummyUnavailDate.first = academicYear;
    dummyUnavailDate.second.push_back(availForExamDummy);
    itMapUnavailability = _unavailability.insert(dummyUnavailDate);
    if (!itMapUnavailability.second) {
        itMapUnavailability.first->second.push_back(availForExamDummy);
    }
}

bool Professor::appendUnavailability(const AvailForExam& unavailDates, const Date& academicYear) {
    // all the controls on date's coherency MUST be performed before colling this function (NO control is performed inside)
    bool alreadyExist = false;
    pair<Date, list<AvailForExam>> dummyUnavailDate;
    pair<map<Date, list<AvailForExam>>:: iterator, bool> itMapUnavailability;

    dummyUnavailDate.first = academicYear;
    dummyUnavailDate.second.push_back(unavailDates);
    itMapUnavailability = _unavailability.insert(dummyUnavailDate);
    if (!itMapUnavailability.second) {
        itMapUnavailability.first->second.push_back(unavailDates);
        alreadyExist = true;
    }
    if (!alreadyExist) {
        // if the key does not exist the pair will be inserted at correct position
        return true;
    } else {
        // if the key instead exist the value will be inserted through push back at the and of the list
        return false;
    }
}

void Professor::appendUnavailabilityForExam(const Date &startUnavail, const Date &stopUnavail) {
    AvailForExam AvailForExamDummy;
    AvailForExamDummy.start = startUnavail;
    AvailForExamDummy.stop = stopUnavail;
    _unavailabilityForExam.push_back(AvailForExamDummy);
}

void Professor::clearMapAcademicYearUnavailability(const Date& academicYear) {
    _unavailability.erase(academicYear);
}

bool Professor::setId(const string& id){
    stringstream tmp;
    if ((id != "") && (id.size()==7)) {
        if (id[0] == 'd') {
            try {
                stoi(id.substr(1, id.size() - 1));
            }
            catch (const invalid_argument& excepFromStoi) {
                return false;
            }
            _id = id;
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

const Professor Professor::operator ++ (int) {
    stringstream toRebuild;
    int tmp = stoi(_id.substr(1, _id.size() - 1));

    tmp++;
    toRebuild << 'd' << setfill('0') << setw(6) << tmp;
    _id = toRebuild.str();
    return *this;
}

bool Professor::operator < (const Professor& toCompare) {
    int lVal, rVal;

    lVal = stoi(_id.substr(1, _id.size() - 1));
    rVal = stoi(toCompare.getId().substr(1, toCompare.getId().size() - 1));
    return lVal < rVal;
}

ostream& Professor::operator << (ostream& os) {
    os << _id << ";" << (this)->getName() << ";" << (this)->getSurname() << ";" << (this)->getMail();
    return os;
}