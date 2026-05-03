#include "StudentHashTable.h"

// ------------------------------------------------------
// StudentNode Constructor
// ------------------------------------------------------
StudentNode::StudentNode(Student s) : data(s), next(nullptr) {}


// ------------------------------------------------------
// Constructor
// ------------------------------------------------------
StudentHashTable::StudentHashTable(int size)
{
    tableSize = size;
    itemCount = 0;

    table = new StudentNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = nullptr;
}


// ------------------------------------------------------
// Destructor
// ------------------------------------------------------
StudentHashTable::~StudentHashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        StudentNode* curr = table[i];
        while (curr != nullptr)
        {
            StudentNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] table;
}


// ------------------------------------------------------
// Hash Function
// ------------------------------------------------------
int StudentHashTable::hash(string key)
{
    int sum = 0;
    for (char ch : key)
        sum += ch;

    return sum % tableSize;
}


// ------------------------------------------------------
// Load Factor
// ------------------------------------------------------
float StudentHashTable::loadFactor()
{
    return (float)itemCount / tableSize;
}

bool StudentHashTable::needResize()
{
    return loadFactor() > 0.7f;
}


// ------------------------------------------------------
// Resize Table (Rehashing)
// ------------------------------------------------------
void StudentHashTable::resizeTable()
{
    int oldSize = tableSize;
    tableSize *= 2;

    StudentNode** oldTable = table;

    table = new StudentNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = nullptr;

    itemCount = 0;

    for (int i = 0; i < oldSize; i++)
    {
        StudentNode* curr = oldTable[i];
        while (curr != nullptr)
        {
            insertStudent(curr->data);
            StudentNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    delete[] oldTable;
}


// ------------------------------------------------------
// Insert Student
// ------------------------------------------------------
bool StudentHashTable::insertStudent(Student s)
{
    if (needResize())
        resizeTable();

    int index = hash(s.getRollNumber());

    StudentNode* curr = table[index];
    while (curr != nullptr)
    {
        if (curr->data.getRollNumber() == s.getRollNumber())
        {
            cout << "Student with roll " << s.getRollNumber() << " already exists.\n";
            return false;
        }
        curr = curr->next;
    }

    StudentNode* newNode = new StudentNode(s);
    newNode->next = table[index];
    table[index] = newNode;

    itemCount++;
    return true;
}


// ------------------------------------------------------
// Search Student
// ------------------------------------------------------
Student* StudentHashTable::searchStudent(string roll)
{
    int index = hash(roll);

    StudentNode* curr = table[index];
    while (curr != nullptr)
    {
        if (curr->data.getRollNumber() == roll)
            return &curr->data;

        curr = curr->next;
    }
    return nullptr;
}


// ------------------------------------------------------
// Delete Student
// ------------------------------------------------------
bool StudentHashTable::deleteStudent(string roll)
{
    int index = hash(roll);

    StudentNode* curr = table[index];
    StudentNode* prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->data.getRollNumber() == roll)
        {
            if (prev == nullptr)
                table[index] = curr->next;
            else
                prev->next = curr->next;

            delete curr;
            itemCount--;
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    return false;
}
