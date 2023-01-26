//
// Created by Luca Brignone on 17/08/22.
//

#ifndef PROGETTO_ASSOCIATEPROFESSOR_H
#define PROGETTO_ASSOCIATEPROFESSOR_H

#include <list>

#include "Professor.h"

using namespace std;

class AssociateProfessor {
public:
    AssociateProfessor() {};
    AssociateProfessor(const AssociateProfessor& toCopy);
    ~AssociateProfessor() {};
    list<Professor>::iterator getProfessorPointer() const;
    void setProfessorPointer(list<Professor>::iterator addressOfProfessor);
    int getLessonH() const;
    bool setLessonH(const int& lessonH);
    int getExerciseH() const;
    bool setExerciseH(const int& exerciseH);
    int getLabH() const;
    bool setLabH(const int& labH);
    bool getIsMain() const;
    void setIsMain(const bool& isMain);
    bool getToCheck() const;
    void setToCek(const bool& modify);
    // the following clear method initialize the private data that comprehend the pointer to the professor which is initialized
    // by pointing the end of professor's list
    void clear(const list<Professor>::iterator initToProfessorListEnd);
    AssociateProfessor& operator =(const AssociateProfessor& toCopy);

private:
    list<Professor>::iterator _itToProfessor;
    int _lessonH = -1;
    int _exerciseH = -1;
    int _labH = -1;
    bool _isMain = false;
    bool _toCek = false;
};


#endif //PROGETTO_ASSOCIATEPROFESSOR_H
