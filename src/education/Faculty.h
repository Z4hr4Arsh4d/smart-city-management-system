#pragma once
#include <iostream>
#include <string>
using namespace std;

class Faculty
{
private:
    string id;
    string name;
    string subject;
    string qualification;
    string department;
    string role;

public:
    // ---------------- Constructors ----------------
    Faculty();
    Faculty(string id, string name, string subject,
        string qualification, string department, string role);

    // ---------------- Getters ----------------
    string getId() const;
    string getName() const;
    string getSubject() const;
    string getQualification() const;
    string getDepartment() const;
    string getRole() const;

    // ---------------- Setters ----------------
    void setId(const string& id);
    void setName(const string& name);
    void setSubject(const string& subject);
    void setQualification(const string& qualification);
    void setDepartment(const string& department);
    void setRole(const string& role);

    // ---------------- Display ----------------
    void displayInfo() const;
};
