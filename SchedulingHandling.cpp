//
// Created by Luca Brignone on 12/10/22.
//

#include "SchedulingHandling.h"

int schedulingInitializer(string& errorHandling, const int& sessionNumber, const Date& sessionBegin, const Date& sessionEnd,
                          const list<Professor>& professorList, const list<Classroom>& classroomList, const list<Course>& courseList,
                          const list<CourseOfStudy>& courseOfStudyList) {
    t_errorCodes errorIdentifier = OK;
    bool dayScheduled = false;
    string errorLine;
    Date sessionEqualSemester, sessionOtherSemester;
    list<Course> copyOfCourseList(courseList);
    list<Course>::const_iterator itOriginalCourseList;
    list<Course>::iterator itCopy;
    map<Date, pair<Date, vector<examScheduled>>> sessionSchedule;
    pair<Date, pair<Date, vector<examScheduled>>> toInsertInSessionSchedule;

    itOriginalCourseList = courseList.cbegin();
    while(itOriginalCourseList != courseList.cend()){
        if (courseIdISInSemester(itOriginalCourseList->getId(), sessionNumber, courseOfStudyList)) {

        }
    }
    while((sessionEqualSemester != sessionEnd) && (errorIdentifier == OK) && !dayScheduled) {
        schedulingPermutationOnDay(errorLine, sessionNumber, sessionEqualSemester, professorList, classroomList, copyOfCourseList, courseOfStudyList, toInsertInSessionSchedule, dayScheduled);
        sessionEqualSemester++;
    }
}

int schedulingPermutationOnDay(string& errorHandling, const int& sessionNumber, const Date& dayToSchedule, const list<Professor>& professorList,
                               const list<Classroom>& classroomList, list<Course>& course, const list<CourseOfStudy>& courseOfStudyList,
                               pair<Date, pair<Date, vector<examScheduled>>>& examSchedulingPerDay, bool& isDayScheduled) {
    t_errorCodes errorIdentifier = OK;
    bool slotScheduled = false;
    int i = 0;
    Date timeSlot(8);
    list<Classroom> copyOfClassroomList(classroomList);
    pair<Date, vector<examScheduled>> toInsertInDaySchedule;

    while ((i < 6) && (errorIdentifier == OK) && !slotScheduled) {
        schedulingPermutationOnTimeSlot(errorHandling, timeSlot, professorList, course, copyOfClassroomList, courseOfStudyList, toInsertInDaySchedule, slotScheduled);
    }
}

int schedulingPermutationOnTimeSlot(string& errorHandling, const Date& timeSlotBegin, const list<Professor>& professorList,
                                    list<Course>& availCourseList, list<Classroom>& updatedAvailClassroom, const list<CourseOfStudy>& courseOfStudyList,
                                    pair<Date, vector<examScheduled>>& examSchedulingPerSlotHour, bool& isSlotScheduled) {

}