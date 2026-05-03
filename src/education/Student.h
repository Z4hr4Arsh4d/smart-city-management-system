#pragma once
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string rollNumber;
    string name;
    string grade;
    string department;
    string* subjects;
    string section;
    int subjectsCount;

public:
    // Constructors
    Student();
    Student(string rollNumber, string name, string grade, string department, string section);

    // Copy Control
    Student(const Student& other);
    Student& operator=(const Student& other);

    // Getters
    string getRollNumber() const;
    string getName() const;
    string getGrade() const;
    string getDepartment() const;
    string getSection() const;

    // Setters
    void setRollNumber(const string& rollNumber);
    void setName(const string& name);
    void setGrade(const string& grade);
    void setDepartment(const string& department);
    void setSection(const string& section);

    // Subject Operations
    void addSubject(string sub);
    bool takesSubject(string sub);
    int getSubjectsCount();
    string getSubjectAt(int index);

    // Display
    void display();

    // Destructor
    ~Student();
};
