#include "FacultyHashTable.h"

// --------------------------------------------------------
// Hash Function
// --------------------------------------------------------
int FacultyHashTable::hash(string key)
{
    int sum = 0;
    for (char c : key)
        sum += c;
    return sum % tableSize;
}

// --------------------------------------------------------
// Load Factor
// --------------------------------------------------------
float FacultyHashTable::loadFactor()
{
    return (float)itemCount / tableSize;
}

bool FacultyHashTable::needResize()
{
    return loadFactor() > 0.7f;
}

// --------------------------------------------------------
// Resize Table (Rehashing)
// --------------------------------------------------------
void FacultyHashTable::resizeTable()
{
    int oldSize = tableSize;
    tableSize *= 2;

    FacultyNode** oldTable = table;

    table = new FacultyNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = nullptr;

    itemCount = 0;

    for (int i = 0; i < oldSize; i++)
    {
        FacultyNode* curr = oldTable[i];

        while (curr)
        {
            insertFaculty(curr->data);
            FacultyNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    delete[] oldTable;
}

// --------------------------------------------------------
// Constructor
// --------------------------------------------------------
FacultyHashTable::FacultyHashTable(int size)
{
    tableSize = size;
    itemCount = 0;

    table = new FacultyNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = nullptr;
}

// --------------------------------------------------------
// Destructor
// --------------------------------------------------------
FacultyHashTable::~FacultyHashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        FacultyNode* curr = table[i];
        while (curr)
        {
            FacultyNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] table;
}

// --------------------------------------------------------
// Insert Faculty
// --------------------------------------------------------
bool FacultyHashTable::insertFaculty(const Faculty& f)
{
    if (needResize())
        resizeTable();

    int index = hash(f.getId());

    FacultyNode* curr = table[index];
    while (curr)
    {
        if (curr->data.getId() == f.getId())
        {
            cout << "Faculty with ID " << f.getId() << " already exists.\n";
            return false;
        }
        curr = curr->next;
    }

    FacultyNode* newNode = new FacultyNode(f);
    newNode->next = table[index];
    table[index] = newNode;

    itemCount++;
    return true;
}

// --------------------------------------------------------
// Search Faculty
// --------------------------------------------------------
Faculty* FacultyHashTable::searchFaculty(string id)
{
    int index = hash(id);

    FacultyNode* curr = table[index];
    while (curr)
    {
        if (curr->data.getId() == id)
            return &curr->data;

        curr = curr->next;
    }
    return nullptr;
}

// --------------------------------------------------------
// Delete Faculty
// --------------------------------------------------------
bool FacultyHashTable::deleteFaculty(string id)
{
    int index = hash(id);

    FacultyNode* curr = table[index];
    FacultyNode* prev = nullptr;

    while (curr)
    {
        if (curr->data.getId() == id)
        {
            if (!prev)
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
