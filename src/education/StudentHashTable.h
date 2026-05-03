#pragma once
#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

struct StudentNode
{
    Student data;
    StudentNode* next;

    StudentNode(Student s);
};

class StudentHashTable
{
private:
    StudentNode** table;
    int tableSize;
    int itemCount;

    int hash(string key);
    float loadFactor();
    bool needResize();
    void resizeTable();

public:
    StudentHashTable(int size = 50);
    ~StudentHashTable();

    bool insertStudent(Student s);
    Student* searchStudent(string roll);
    bool deleteStudent(string roll);
};
