#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "OrgNode.h"
#include "FacultyHashTable.h"
#include "StudentHashTable.h"

class School
{
private:
    string id;
    string name;
    string sector;

    string* subjects;
    int subjectsCount;

    float rating;

    OrgNode* organogramRoot;

    FacultyHashTable* facultyTable;
    StudentHashTable* studentTable;

public:
    // Constructors / Destructor
    School();
    School(string id, string name, string sector);
    ~School();

    // Basic setters & getters
    void setId(string x);
    string getId();

    void setName(string n);
    string getName();

    void setSector(string s);
    string getSector();

    void setRating(float r);
    float getRating();

    // Subject functions
    void addSubject(string sub);
    bool offersSubject(string sub);

    // Faculty functions
    bool registerFaculty(Faculty f);
    Faculty* findFaculty(string id);
    void removeFaculty(string id);

    bool registerFacultyWithRole(const Faculty& f, const string& parentRole);
    bool assignFacultyToRole(const string& roleName, const string& facultyId);

    // Student functions
    bool registerStudent(const Student& s);
    Student* findStudent(string roll);
    void removeStudent(string roll);
	int getSubjectsCount() const;
	string getSubjectAt(int index) const;
    

    // Organogram functions
    void initOrganogram();
    void addRole(string parentRole, string newRole);
    OrgNode* getOrganogramRoot();
    void ensureOrganogram();
    void printOrganogram();

    // Reporting Functions
    void printFacultyWithAndWithoutRoles();
    void collectRoleFacultyIds(OrgNode* root, string* ids, int& count);
};
