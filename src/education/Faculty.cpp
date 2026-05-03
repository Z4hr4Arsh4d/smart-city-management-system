#include "Faculty.h"

// ---------------- Constructors ----------------
Faculty::Faculty()
{
    id = "";
    name = "";
    subject = "";
    qualification = "";
    department = "";
    role = "";
}

Faculty::Faculty(string id, string name, string subject,
    string qualification, string department, string role)
{
    this->id = id;
    this->name = name;
    this->subject = subject;
    this->qualification = qualification;
    this->department = department;
    this->role = role;
}


// ---------------- Getters ----------------
string Faculty::getId() const { return id; }
string Faculty::getName() const { return name; }
string Faculty::getSubject() const { return subject; }
string Faculty::getQualification() const { return qualification; }
string Faculty::getDepartment() const { return department; }
string Faculty::getRole() const { return role; }


// ---------------- Setters ----------------
void Faculty::setId(const string& id) { this->id = id; }
void Faculty::setName(const string& name) { this->name = name; }
void Faculty::setSubject(const string& subject) { this->subject = subject; }
void Faculty::setQualification(const string& qualification) { this->qualification = qualification; }
void Faculty::setDepartment(const string& department) { this->department = department; }
void Faculty::setRole(const string& role) { this->role = role; }


// ---------------- Display ----------------
void Faculty::displayInfo() const
{
    cout << "Faculty ID: " << id << endl;
    cout << "Name      : " << name << endl;
    cout << "Subject   : " << subject << endl;
    cout << "Qualification: " << qualification << endl;
    cout << "Department: " << department << endl;

    if (!role.empty())
        cout << "Assigned Role: " << role << endl;

    cout << endl;
}
