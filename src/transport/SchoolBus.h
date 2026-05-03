#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Bus.h"
#include "../education/School.h"
#include "../education/Student.h"

class SchoolBus : public Bus
{
private:
    School* schoolPtr;

    // BONUS: student assignment system
    string* studentList;
    int studentCount;
    int studentCapacity;

    int maxCapacity;
    bool emergencyMode;

    void resizeStudentList();

public:
    SchoolBus(const string& no, School* s);
    virtual ~SchoolBus();

    // school association
    void setSchool(School* s);
    School* getSchool() const;

    // student assignment
    bool assignStudent(const Student& st);
    bool isStudentAssigned(const string& rollNo);
    void autoLoadStudents();

    // emergency mode
    void activateEmergencyMode();
    void disableEmergencyMode();
    bool isInEmergencyMode() const;

    // override movement
    void moveToNextStop() override;

    // display
    void printAssignedStudents() const;
    void displayInfo() const override;
};
