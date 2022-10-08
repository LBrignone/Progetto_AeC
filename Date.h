//
// Created by Luca Brignone on 16/08/22.
//

#ifndef PROGETTO_DATE_H
#define PROGETTO_DATE_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
    int getMinutes() const;
    bool setMinutes(int minutes);
    int getHour() const;
    bool setHour(int hour);
    int getDay() const;
    bool setDay(int day);
    int getMonth() const;
    bool setMonth(int month);
    int getYear() const;
    bool setYear(int year);
    string getCompleteDate() const;
    void getAcademicYear(ostream& os);
    bool operator <= (const Date& date) const;
    bool operator >= (const Date& date) const;
    bool operator > (const Date& date) const;
    bool operator < (const Date& date) const;
    bool operator == (const Date& date) const;
    int operator - (const Date& rValDate) const;
    const Date operator ++ (int);
    ostream& operator << (ostream& os);

private:
    int _hour = 0;
    int _minutes = 0;
    int _day = 0;
    int _month = 0;
    int _year = 0;
};


#endif //PROGETTO_DATE_H
