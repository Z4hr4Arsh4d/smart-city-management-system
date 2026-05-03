#include "BusHashTable.h"

// ---------------------------------------------------------
// BusNode Constructor
// ---------------------------------------------------------
BusNode::BusNode(Bus* b)
{
    data = b;
    next = nullptr;
}

// ---------------------------------------------------------
// Hash Function
// ---------------------------------------------------------
int BusHashTable::hash(const string& key) const
{
    long long sum = 0;
    for (char c : key)
        sum = (sum * 31 + c) % tableSize;

    return (int)sum;
}

float BusHashTable::loadFactor() const
{
    return (float)itemCount / tableSize;
}

bool BusHashTable::needResize() const
{
    return loadFactor() > 0.75f;
}

// ---------------------------------------------------------
// Resize Hash Table
// ---------------------------------------------------------
void BusHashTable::resizeTable()
{
    int oldSize = tableSize;
    tableSize *= 2;

    BusNode** oldTable = table;

    table = new BusNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = nullptr;

    itemCount = 0;

    // reinsert all items
    for (int i = 0; i < oldSize; i++)
    {
        BusNode* curr = oldTable[i];
        while (curr != nullptr)
        {
            insert(curr->data);
            BusNode* temp = curr;
            curr = curr->next;
            delete temp; // delete old node only
        }
    }

    delete[] oldTable;
}

// ---------------------------------------------------------
// Constructor
// ---------------------------------------------------------
BusHashTable::BusHashTable(int size)
{
    tableSize = size;
    itemCount = 0;

    table = new BusNode * [tableSize];
    for (int i = 0; i < tableSize; i++)
        table[i] = nullptr;
}

// ---------------------------------------------------------
// Destructor
// ---------------------------------------------------------
BusHashTable::~BusHashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        BusNode* curr = table[i];
        while (curr != nullptr)
        {
            BusNode* temp = curr;
            curr = curr->next;
            delete temp; // NOT deleting Bus*
        }
    }
    delete[] table;
}

// ---------------------------------------------------------
// Insert Bus
// ---------------------------------------------------------
bool BusHashTable::insert(Bus* b)
{
    if (needResize())
        resizeTable();

    int index = hash(b->getBusNo());

    BusNode* curr = table[index];
    while (curr != nullptr)
    {
        if (curr->data->getBusNo() == b->getBusNo())
        {
            cout << "Bus already exists: " << b->getBusNo() << endl;
            return false;
        }
        curr = curr->next;
    }

    BusNode* newNode = new BusNode(b);
    newNode->next = table[index];
    table[index] = newNode;

    itemCount++;
    return true;
}

// ---------------------------------------------------------
// Search
// ---------------------------------------------------------
Bus* BusHashTable::search(const string& busNo)
{
    int index = hash(busNo);

    BusNode* curr = table[index];
    while (curr != nullptr)
    {
        if (curr->data->getBusNo() == busNo)
            return curr->data;

        curr = curr->next;
    }
    return nullptr;
}

// ---------------------------------------------------------
// Remove Bus
// ---------------------------------------------------------
bool BusHashTable::remove(const string& busNo)
{
    int index = hash(busNo);

    BusNode* curr = table[index];
    BusNode* prev = nullptr;

    while (curr != nullptr)
    {
        if (curr->data->getBusNo() == busNo)
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

// ---------------------------------------------------------
// Print Table (Debug)
// ---------------------------------------------------------
void BusHashTable::print() const
{
    cout << "\n======= BUS HASH TABLE =======\n";

    for (int i = 0; i < tableSize; i++)
    {
        cout << "[" << i << "]: ";
        BusNode* curr = table[i];

        while (curr != nullptr)
        {
            cout << curr->data->getBusNo();
            if (curr->next) cout << " -> ";
            curr = curr->next;
        }
        cout << "\n";
    }

    cout << "==============================\n";
}
