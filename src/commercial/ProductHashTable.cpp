#include "ProductHashTable.h"

// -------------------- HashNode Constructor --------------------
ProductHashTable::HashNode::HashNode(const string& k, const Product& v)
    : key(k), value(v), next(nullptr)
{
}

// -------------------- Hash Function --------------------
int ProductHashTable::hashFunction(const string& key) const
{
    unsigned long hash = 0;
    unsigned long p = 31;
    unsigned long power = 1;

    for (size_t i = 0; i < key.size(); i++)
    {
        hash = (hash + (key[i] * power)) % capacity;
        power = (power * p) % capacity;
    }
    return static_cast<int>(hash % capacity);
}

// -------------------- Constructor --------------------
ProductHashTable::ProductHashTable(int cap)
    : capacity(cap)
{
    table = new HashNode * [capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = nullptr;
}

// -------------------- Destructor --------------------
ProductHashTable::~ProductHashTable()
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode* curr = table[i];
        while (curr)
        {
            HashNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete[] table;
}

// -------------------- Insert --------------------
void ProductHashTable::insert(const string& key, const Product& value)
{
    int index = hashFunction(key);
    HashNode* newNode = new HashNode(key, value);

    newNode->next = table[index];
    table[index] = newNode;
}

// -------------------- Search by Key --------------------
bool ProductHashTable::search(const string& key, Product& value)
{
    int index = hashFunction(key);
    HashNode* curr = table[index];

    while (curr)
    {
        if (curr->key == key)
        {
            value = curr->value;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// -------------------- Search by Category --------------------
bool ProductHashTable::searchByCategory(const string& category, Product& value)
{
    for (int i = 0; i < capacity; i++)
    {
        HashNode* curr = table[i];
        while (curr)
        {
            if (curr->value.getCategory() == category)
            {
                value = curr->value;
                return true;
            }
            curr = curr->next;
        }
    }
    return false;
}

// -------------------- Display Table --------------------
void ProductHashTable::display() const
{
    cout << "\n=== Product Hash Table ===\n";

    for (int i = 0; i < capacity; i++)
    {
        cout << "Bucket " << i << ": ";

        HashNode* curr = table[i];

        if (!curr)
        {
            cout << "(empty)\n";
            continue;
        }

        while (curr)
        {
            cout << "[Key: " << curr->key << ", " << curr->value << "] -> ";
            curr = curr->next;
        }

        cout << "NULL\n";
    }

    cout << endl;
}
