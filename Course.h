//
// Created by Luca Brignone on 17/08/22.
//

#ifndef PROGETTO_COURSE_H
#define PROGETTO_COURSE_H

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "Date.h"
#include "ErrorHandling.h"
#include "AssociateProfessor.h"

using namespace std;

class Course {
public:
    string getId() const;
    bool setId(const string& id);
    bool generateNewId(const string& lastId);
    int getStartYear() const;
    bool setStartYear(const int& startYear);
    string getParallelCoursesId() const;
    bool setParallelCoursesId(const string& parallelCoursesId);
    void clearParallelCourseId();
    string getTitle() const;
    void setTitle(const string &title);
    int getCfu() const;
    bool setCfu(const int& cfu);
    int getParallelCoursesNumber() const;
    bool setParallelCoursesNumber(const int& parallelCoursesNumber);
    bool isActiveCourse() const;
    void setActiveCourse(const bool& activeCourse);
    bool getActiveCourseFieldEmpty() const;
    void setActiveCourseFieldEmpty(const bool& activeCourse);
    int getCourseLessonH() const;
    bool setCourseLessonH(const int& courseLessonH);
    int getCourseExerciseH() const;
    bool setCourseExerciseH(const int& courseExerciseH);
    int getCourseLabH() const;
    bool setCourseLabH(const int& courseLabH);
    list<AssociateProfessor>& getListAssistant();
    int setListAssistant(const list<AssociateProfessor> &assistant, string& errorInAssistant);
    int appendAssistant(const AssociateProfessor &toAppend, string &errorInAppend);
    string getMainProfessor();
    string getExamType() const;
    bool setExamType(const string& examType);
    char getExamClassroomType() const;
    bool setExamClassroomType(char examClassroomType);
    int getEntranceTime() const;
    bool setEntranceTime(int entranceTime);
    int getExitTime() const;
    bool setExitTime(int exitTime);
    int getExamDuration() const;
    bool setExamDuration(int examDuration);
    int getPartecipants() const;
    bool setPartecipants(int partecipants);
    list<string> getListGroupedId() const;
    bool setListGroupedId(const list<string> &groupingId);
    bool appendGroupedId(const string& toAppend);
    void deleteLastElementGroupedId();
    bool getExamIsScheduled(int i) const;
    void setExamIsScheduled(int i);
    void resetExamIsScheduled(int i);
    Course& inheritCourse(const list<Course>::iterator& toInherit);
    ostream& printCourseOrganization(ostream& os) const;
    ostream& printCourseOrganizationAcademicYearOpening(ostream& os) const;
    ostream& printCourseOrganizationVersionOpening(ostream& os, const bool& first) const; // see implementation to further comment
    ostream& printCourseOrganizationAcademicYearClosing(ostream& os) const;
    Course& operator = (const Course& toCopy);
    Course& operator = (const list<Course>::iterator& toCopy);
    ostream& operator << (ostream& os);

private:
    typedef enum {S, O, SO, P, NO_TYPE} t_examType;

    string _id;
    Date _startYear;
    string _parallelCoursesId = "";
    string _title;
    int _cfu = -1;
    int _parallelCoursesNumber = -1;
    bool _activeCourse = true;
    bool _activeCourseFieldEmpty = false;
    int _courseLessonH = -1;
    int _courseExerciseH = -1;
    int _courseLabH = -1;
    list<AssociateProfessor> _assistant;
    t_examType _examType = NO_TYPE;
    char _examClassroomType = '\0';
    int _entryTime = -1;
    int _exitTime = -1;
    int _examDuration = -1;
    int _partecipants = -1;
    list<string> _coursesGroupedId;
    vector<bool> _isScheduled = {false, false, false, false};

    vector<string> error {"ERR_hour_incompatibility", "ERR_negative_hour", "ERR_hours_not_set", "OK"};
    vector<string> examTypeVect {"S", "O", "SO", "P", "NO_TYPE"};
};

#endif //PROGETTO_COURSE_H
