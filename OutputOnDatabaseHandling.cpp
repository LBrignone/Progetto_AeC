//
// Created by Luca Brignone on 04/10/22.
//

#include "OutputOnDatabaseHandling.h"

int updateStudentDatabase(string& errorHandling, string& databaseFileName, const list<Student>& updatedStudentList) {
    t_typeErrorDefinitionReadingFile errorIdentifier;
    ofstream fileName;

    fileName.open(databaseFileName, ofstream::trunc);
    if (fileName.is_open()) {
        errorIdentifier = ERR_open_file;
        errorHandling = "Error: file " + databaseFileName + " not found";
    } else {
        list<Student>::const_iterator itListStudent;

        itListStudent = updatedStudentList.cbegin();
        while (itListStudent != updatedStudentList.cend()) {
            fileName << itListStudent;
        }
    }

    fileName.close();
}