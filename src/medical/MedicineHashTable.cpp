#include "MedicineHashTable.h"

// ----------------------
// HashNode Constructor
// ----------------------
HashNode::HashNode(string k, Medicine v)
    : key(k), med(v), next(nullptr)
{
}

// ----------------------
// Constructor
// ----------------------
HashTable::HashTable()
{
    table = new HashNode * [TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = nullptr;
}

// ----------------------
// Polynomial Rolling Hash (string)
// ----------------------
int HashTable::hashFunction(const string& key) const
{
    int hash = 0;
    int prime = 31;
    int mod = TABLE_SIZE;
    int power = 1;

    for (int i = key.length() - 1; i >= 0; i--)
    {
        hash = (hash + (key[i] - 'A' + 1) * power) % mod;
        power = (power * prime) % mod;
    }

    return abs(hash) % TABLE_SIZE;
}

// ----------------------
// Integer Hash
// ----------------------
int HashTable::hashFunction(int key) const
{
    return abs(key) % TABLE_SIZE;
}

// ----------------------
// Copy Constructor
// ----------------------
HashTable::HashTable(const HashTable& other)
{
    table = new HashNode * [TABLE_SIZE];

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        table[i] = nullptr;

        HashNode* current = other.table[i];
        HashNode** thisCurrent = &table[i];

        while (current != nullptr)
        {
            *thisCurrent = new HashNode(current->key, current->med);
            thisCurrent = &((*thisCurrent)->next);
            current = current->next;
        }
    }
}

// ----------------------
// Assignment Operator
// ----------------------
HashTable& HashTable::operator=(const HashTable& other)
{
    if (this != &other)
    {
        // Clear existing
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            HashNode* current = table[i];
            while (current != nullptr)
            {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }

        // Deep copy
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            table[i] = nullptr;

            HashNode* current = other.table[i];
            HashNode** thisCurrent = &table[i];

            while (current != nullptr)
            {
                *thisCurrent = new HashNode(current->key, current->med);
                thisCurrent = &((*thisCurrent)->next);
                current = current->next;
            }
        }
    }
    return *this;
}

// ----------------------
// Destructor
// ----------------------
HashTable::~HashTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode* current = table[i];
        while (current != nullptr)
        {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

// ----------------------
// Insert or Update
// ----------------------
void HashTable::insert(const string& key, const Medicine& value)
{
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current != nullptr)
    {
        if (current->key == key)
        {
            current->med = value; // update
            return;
        }
        current = current->next;
    }

    // Insert at head
    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

// ----------------------
// Search by Key
// ----------------------
bool HashTable::search(const string& key, Medicine& value)
{
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current)
    {
        if (current->key == key)
        {
            value = current->med;
            return true;
        }
        current = current->next;
    }
    return false;
}

// ----------------------
// Search by Medicine Name
// ----------------------
bool HashTable::searchByName(const string& name, Medicine& value)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode* current = table[i];
        while (current != nullptr)
        {
            if (current->med.getMedicineName() == name)
            {
                value = current->med;
                return true;
            }
            current = current->next;
        }
    }
    return false;
}

// ----------------------
// Contains
// ----------------------
bool HashTable::contains(const string& key) const
{
    int index = hashFunction(key);
    HashNode* current = table[index];

    while (current)
    {
        if (current->key == key)
            return true;

        current = current->next;
    }
    return false;
}

// ----------------------
// Delete Key
// ----------------------
bool HashTable::deleteKey(const string& key)
{
    int index = hashFunction(key);
    HashNode* current = table[index];
    HashNode* prev = nullptr;

    while (current)
    {
        if (current->key == key)
        {
            if (prev == nullptr)
                table[index] = current->next;
            else
                prev->next = current->next;

            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }

    return false;
}

// ----------------------
// Display Table
// ----------------------
void HashTable::display() const
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode* current = table[i];
        if (!current) continue;

        cout << "All Medicines " << i << ":\n";
        while (current)
        {
            cout << "  Key: " << current->key
                << " | " << current->med << "\n";
            current = current->next;
        }
    }
}

// ----------------------
// Get a Bucket Chain
// ----------------------
HashNode* HashTable::getChain(int index) const
{
    if (index >= 0 && index < TABLE_SIZE)
        return table[index];
    return nullptr;
}
