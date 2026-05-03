#pragma once
#include <iostream>
#include <string>
#include "Faculty.h"
using namespace std;

struct FacultyNode
{
    Faculty data;
    FacultyNode* next;

    FacultyNode(const Faculty& f)
        : data(f), next(nullptr) {
    }
};

class FacultyHashTable
{
private:
    FacultyNode** table;
    int tableSize;
    int itemCount;

    int hash(string key);
    float loadFactor();
    bool needResize();
    void resizeTable();

public:
    FacultyHashTable(int size = 50);
    ~FacultyHashTable();

    bool insertFaculty(const Faculty& f);
    Faculty* searchFaculty(string id);
    bool deleteFaculty(string id);

    // Needed for School::printFacultyWithAndWithoutRoles()
    FacultyNode** getTable() const { return table; }
    int getSize() const { return tableSize; }
};
