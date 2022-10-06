cmake_minimum_required(VERSION 3.22)
project(Progetto)

set(CMAKE_CXX_STANDARD 14)

add_executable(Progetto main.cpp Person.cpp Professor.cpp Date.cpp Student.cpp Classroom.cpp AssociateProfessor.cpp AssociateProfessor.h Course.cpp Course.h CourseOfStudy.cpp CourseOfStudy.h AddFileHandling.cpp AddFileHandling.h findSomethingInList.cpp findSomethingInList.h PatternConstrainVerification.cpp PatternConstrainVerification.h UpdateFileHandling.cpp UpdateFileHandling.h InsertFileHandling.cpp InsertFileHandling.h FillDatabaseList.cpp FillDatabaseList.h OutputOnDatabaseHandling.cpp OutputOnDatabaseHandling.h ErrorHandling.cpp ErrorHandling.h)
