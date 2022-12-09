//
// Created by Luca Brignone on 16/08/22.
//

#include "Date.h"

Date::Date(const Date& dateToCopy) {
    this->_minutes = dateToCopy._minutes;
    this->_hour = dateToCopy._hour;
    this->_day = dateToCopy._day;
    this->_month = dateToCopy._month;
    this->_year = dateToCopy._year;
}

Date::Date() {
    _minutes = 0;
    _hour = 0;
    _day = 0;
    _month = 0;
    _year = 0;
}

Date::Date(const int& hour) {
    _hour = hour;
}

Date::Date(const int& day, const int& month, const int& year) {
    _day = day;
    _month = month;
    _year = year;
}

Date::Date(const int& minutes, const int& hour, const int& day, const int& month, const int& year) {
    _minutes = minutes;
    _hour = hour;
    _day = day;
    _month = month;
    _year = year;
}

int Date::getMinutes() const {
    return _minutes;
}

bool Date::setMinutes(int minutes) {
    if (minutes >= 0) {
        _minutes = minutes;
        return true;
    } else {
        return false;
    }
}

int Date::getHour() const {
    return _hour;
}

bool Date::setHour(int hour) {
    if (hour >= 0) {
        _hour = hour;
        return true;
    } else {
        return false;
    }
}

int Date::getDay() const {
    return _day;
}

bool Date::setDay(int day) {
    if (_month != 0) {
        if ((day >= 0) && (((_month == 2) && (day < 29)) ||
                           (((_month == 4) || (_month == 6) || (_month == 9) || (_month == 11)) && (day < 31)) ||
                           (((_month == 1) || (_month == 3) || (_month == 5) || (_month == 7) || (_month == 8) ||
                             (_month == 10) || (_month == 12)) && (day < 32)))) {
            _day = day;
            return true;
        } else {
            return false;
        }
    } else {
        _day = day;
        return true;
    }
}

int Date::getMonth() const {
    return _month;
}

bool Date::setMonth(int month) {
    if ((month > 0) && (month < 13)) {
        _month = month;
        return true;
    } else {
        return false;
    }
}

int Date::getYear() const {
    return _year;
}

bool Date::setYear(int year) {
    if (year >= 0) {
        _year = year;
        return true;
    } else {
        return false;
    }
}

string Date::getCompleteDate() const {
    stringstream tmp;
    tmp << setfill ('0') << setw (4) <<_year << "-" << setfill ('0') << setw (2) << _month << "-" << setfill ('0') << setw (2) << _day;
    return tmp.str();
}

void Date::getAcademicYear(ostream& os) const {
    os << setfill ('0') << setw (4) << _year << "-" << setfill ('0') << setw (4) << (_year + 1);
}

string Date::getAcademicYear() const {
    stringstream tmp;
    tmp << setfill ('0') << setw (4) << _year << "-" << setfill ('0') << setw (4) << (_year + 1);
    return tmp.str();
}

void Date::getTimeSlot(ostream& os) {
    os << setfill ('0') << setw (4) << _hour << ":00-" << setfill ('0') << setw (4) << (_hour + 1) << ":00;";
}

void Date::increaseAcademicYear() {
    this->_year += 1;
}

void Date::increaseTimeSlot() {
    this->_hour += 2;
}

Date& Date::operator =(const Date& date) {
    Date tmpDate(date);
    if ((this) != &date) {
        _minutes = date._minutes;
        _hour = date._hour;
        _day = date._day;
        _month = date._month;
        _year = date._year;
    }
    return *this;
}

bool Date::operator <= (const Date &date) const {
    bool tmp;
    if (_year < date._year) {
        tmp = true;
    } else if (_year > date._year) {
        tmp = false;
    } else {
        if (_month < date._month) {
            tmp = true;
        } else if (_month > date._month) {
            tmp = false;
        } else {
            if(_day < date._day) {
                tmp = true;
            } else if (_day > date._day){
                tmp = false;
            } else {
                if (_hour < date._hour) {
                    return true;
                } else if (_hour > date._hour) {
                    return false;
                } else {
                    if (_minutes <= date._minutes) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
    }
    return tmp;
}

bool Date::operator>=(const Date &date) const {
    bool tmp;
    if (_year > date._year) {
        tmp = true;
    } else if (_year < date._year) {
        tmp = false;
    } else {
        if (_month > date._month) {
            tmp = true;
        } else if (_month < date._month) {
            tmp = false;
        } else {
            if (_day > date._day) {
                tmp = true;
            } else if (_day < date._day) {
                tmp = false;
            } else {
                if (_hour > date._hour) {
                    return true;
                } else if (_hour < date._hour) {
                    return false;
                } else {
                    if (_minutes >= date._minutes) {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        }
    }
    return tmp;
}

bool Date::operator > (const Date& date) const {
    return !(*(this) <= date);
}

bool Date::operator < (const Date& date) const {
    return !(*(this) >= date);
}

bool Date::operator == (const Date& date) const {
    if ((_year == date.getYear()) && (_month == date.getMonth()) && (_day == date.getDay()) && (_hour == date.getHour()) && (_minutes == date.getMinutes())) {
        return true;
    } else {
        return false;
    }
}

bool Date::operator !=(const Date& date) const {
    if (*this == date) {
        return false;
    } else {
        return true;
    }
}

// the "-" operator overload will return a difference in days between the given dates
int Date::operator - (const Date& rValDate) const {
    int tmp = 0, tmpMonth;

    if (_month == 2) {
        tmp = _day;
    } else if ((_month == 4) || (_month == 6) || (_month == 9) || (_month == 11)) {
        tmp = _day;
    } else if ((_month == 1) || (_month == 3) || (_month == 5) || (_month == 7) || (_month == 8) || (_month == 10) || (_month == 12)) {
        tmp = _day;
    }
    if (rValDate._month == 2) {
        tmp = 28 - rValDate._day + tmp;
    } else if ((rValDate._month == 4) || (rValDate._month == 6) || (rValDate._month == 9) || (rValDate._month == 11)) {
        tmp = 30 - rValDate._day + tmp;
    } else if ((rValDate._month == 1) || (rValDate._month == 3) || (rValDate._month == 5) || (rValDate._month == 7) || (rValDate._month == 8) || (rValDate._month == 10) || (rValDate._month == 12)) {
        tmp = 31 - rValDate._day + tmp;
    }
    if ((_month - rValDate._month) > 1) {
        tmpMonth = _month - 1;
        while (tmpMonth > rValDate._month) {
            if (tmpMonth == 2) {
                tmp += 28;
            } else if ((tmpMonth == 4) || (tmpMonth == 6) || (tmpMonth == 9) || (tmpMonth == 11)) {
                tmp += 30;
            } else if ((tmpMonth == 1) || (tmpMonth == 3) || (tmpMonth == 5) || (tmpMonth == 7) || (tmpMonth == 8) || (tmpMonth == 10) || (tmpMonth == 12)) {
                tmp += 31;
            }
            tmpMonth--;
        }
    } else if ((_month - rValDate._month) < 0) {
        tmpMonth = rValDate._month + 1;
        while (tmpMonth < 13) {
            if (tmpMonth == 2) {
                tmp += 28;
            } else if ((tmpMonth == 4) || (tmpMonth == 6) || (tmpMonth == 9) || (tmpMonth == 11)) {
                tmp += 30;
            } else if ((tmpMonth == 1) || (tmpMonth == 3) || (tmpMonth == 5) || (tmpMonth == 7) || (tmpMonth == 8) || (tmpMonth == 10) || (tmpMonth == 12)) {
                tmp += 31;
            }
            tmpMonth++;
        }
        tmpMonth = _month - 1;
        while (tmpMonth > 0) {
            if (tmpMonth == 2) {
                tmp += 28;
            } else if ((tmpMonth == 4) || (tmpMonth == 6) || (tmpMonth == 9) || (tmpMonth == 11)) {
                tmp += 30;
            } else if ((tmpMonth == 1) || (tmpMonth == 3) || (tmpMonth == 5) || (tmpMonth == 7) || (tmpMonth == 8) || (tmpMonth == 10) || (tmpMonth == 12)) {
                tmp += 31;
            }
            tmpMonth--;
        }
    }
    while ((_year - rValDate._year) > 1) {
        tmp += 365;
    }
    return tmp;
}

Date Date::operator ++ (int) {
    Date old = *this;
    if (_month == 2) {
        if (_day < 28) {
            _day++;
        } else {
            _day = 1;
            _month++;
        }
    } else if ((_month == 4) || (_month == 6) || (_month == 9) || (_month == 11)) {
        if (_day < 30) {
            _day++;
        } else {
            _day = 1;
            _month++;
        }
    } else if ((_month == 1) || (_month == 3) || (_month == 5) || (_month == 7) || (_month == 8) || (_month == 10) || (_month == 12)) {
        if (_day < 31) {
            _day++;
        } else {
            _day = 1;
            if (_month < 12) {
                _month++;
            } else {
                _month = 1;
                _year++;
            }
        }
    }
    return old;
}

ostream& Date::operator << (ostream& os) const {
    os << setfill ('0') << setw (4) <<_year << "-" << setfill ('0') << setw (2) << _month << "-" << setfill ('0') << setw (2) << _day;
    return os;
}