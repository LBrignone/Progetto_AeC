//
// Created by Luca Brignone on 18/08/22.
//

#ifndef PROGETTO_COURSEOFSTUDY_H
#define PROGETTO_COURSEOFSTUDY_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

typedef enum {BS, MS, NO_TYPE} t_graduationType;

class CourseOfStudy {
public:
    CourseOfStudy() {};
    ~CourseOfStudy() {};
    string getCourseOfStudyId() const;
    bool generateCourseOfStudyId(const string& lastCourseOfStudy);
    bool setCourseOfStudyId(const string& toSetcourseOfStudyId);
    string getGraduationType() const;
    bool setGaraduationType(const string& graduationType);
    const list<string>& getListOfCoursesBySemester(const int& key) const;
    bool setListOfCoursesBySemester(string& errorHandlingFormPattern, const int& semesterKey, const string& courseId);
    bool deleteEndedCourseFormActiveCourse(string& errorHandling, const string& courseId,const bool& allInactive);
    bool activateCourseFormEndedCourse(string& errorHandling, const string& courseId, const bool& allActive);
    int findCourse(int startSemester, const string& courseId);
    ostream& operator <<(ostream& os) const;

private:
    string _courseOfStudyId;
    t_graduationType _graduationType = NO_TYPE;
    // the following map contains in order by semester the respective courses for the given semester
    //NOTE: the list of ended courses is memorized with key -1
    map<int, list<string>> _semesterOfCourse;

    vector<string> graduationTypeVect {"BS", "MS", "NO_TYPE"};
};


#endif //PROGETTO_COURSEOFSTUDY_H
