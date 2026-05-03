#include "Student.h"

// ---------------------------------------------------------
// Default Constructor
// ---------------------------------------------------------
Student::Student()
{
    rollNumber = "";
    name = "";
    grade = "";
    department = "";
    subjects = new string[20];
    section = "";
    subjectsCount = 0;
}

// ---------------------------------------------------------
// Parameterized Constructor
// ---------------------------------------------------------
Student::Student(string rollNumber, string name, string grade, string department, string section)
{
    this->rollNumber = rollNumber;
    this->name = name;
    this->grade = grade;
    this->department = department;
    this->section = section;

    subjects = new string[20];
    subjectsCount = 0;
}

// ---------------------------------------------------------
// Copy Constructor (Deep Copy)
// ---------------------------------------------------------
Student::Student(const Student& other)
{
    rollNumber = other.rollNumber;
    name = other.name;
    grade = other.grade;
    department = other.department;
    section = other.section;
    subjectsCount = other.subjectsCount;

    subjects = new string[20];
    for (int i = 0; i < subjectsCount; i++)
        subjects[i] = other.subjects[i];
}

// ---------------------------------------------------------
// Assignment Operator (Deep Copy)
// ---------------------------------------------------------
Student& Student::operator=(const Student& other)
{
    if (this == &other)
        return *this;

    rollNumber = other.rollNumber;
    name = other.name;
    grade = other.grade;
    department = other.department;
    section = other.section;

    delete[] subjects;

    subjects = new string[20];
    subjectsCount = other.subjectsCount;

    for (int i = 0; i < subjectsCount; i++)
        subjects[i] = other.subjects[i];

    return *this;
}

// ---------------------------------------------------------
// Getters
// ---------------------------------------------------------
string Student::getRollNumber() const { return rollNumber; }
string Student::getName() const { return name; }
string Student::getGrade() const { return grade; }
string Student::getDepartment() const { return department; }
string Student::getSection() const { return section; }

// ---------------------------------------------------------
// Setters
// ---------------------------------------------------------
void Student::setRollNumber(const string& rollNumber) { this->rollNumber = rollNumber; }
void Student::setName(const string& name) { this->name = name; }
void Student::setGrade(const string& grade) { this->grade = grade; }
void Student::setDepartment(const string& department) { this->department = department; }
void Student::setSection(const string& section) { this->section = section; }

// ---------------------------------------------------------
// Subject Functions
// ---------------------------------------------------------
void Student::addSubject(string sub)
{
    subjects[subjectsCount++] = sub;
}

bool Student::takesSubject(string sub)
{
    for (int i = 0; i < subjectsCount; i++)
        if (subjects[i] == sub)
            return true;

    return false;
}

int Student::getSubjectsCount()
{
    return subjectsCount;
}

string Student::getSubjectAt(int index)
{
    if (index >= 0 && index < subjectsCount)
        return subjects[index];
    return "";
}

// ---------------------------------------------------------
// Display
// ---------------------------------------------------------
void Student::display()
{
    cout << "Roll Number: " << rollNumber << endl;
    cout << "Name: " << name << endl;
    cout << "Grade: " << grade << endl;
    cout << "Department: " << department << endl;
    cout << "Section: " << section << endl;

    cout << "Subjects: ";
    for (int i = 0; i < subjectsCount; i++)
    {
        cout << subjects[i];
        if (i < subjectsCount - 1)
            cout << ", ";
    }
    cout << endl;
}

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------
Student::~Student()
{
    delete[] subjects;
}
