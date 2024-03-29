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
    Course() {};
    Course(const Course& toCopy);
    ~Course() {};
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
    const list<AssociateProfessor>& getListAssistant() const;
    int setListAssistant(const list<AssociateProfessor>& assistant, string& errorInAssistant);
    void setListAssistantNoChecks(const list<AssociateProfessor>& assistant);
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
    void deleteGroupedId();
    void inheritCourse(const list<Course>::const_iterator& toInherit);
    void clearCFields();
    void clearAFields();
    ostream& printCourseOrganization(ostream& os) const;
    ostream& printCourseOrganizationAcademicYearOpening(ostream& os) const;
    ostream& printCourseOrganizationVersionOpening(ostream& os, const bool& first) const; // see implementation to further comment
    void printCourseOrganizationAcademicYearClosing(ostream& os) const;
    bool operator <(const Course& course) const;
    Course& operator =(const Course& toCopy);
    Course& operator =(const list<Course>::iterator& toCopy);
    ostream& operator <<(ostream& os) const;

private:
    typedef enum {S, O, SO, P, NO_TYPE} t_examType;

    string _id;
    Date _startYear;
    string _parallelCoursesId;
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

    vector<string> examTypeVect {"S", "O", "SO", "P", "NO_TYPE"};
};

#endif //PROGETTO_COURSE_H
