#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Medicine.h"

// Node for separate chaining in hash table
struct HashNode
{
    string key;
    Medicine med;
    HashNode* next;

    HashNode(string k, Medicine v);
};

class HashTable
{
private:
    static const int TABLE_SIZE = 100;
    HashNode** table;

    int hashFunction(const string& key) const;
    int hashFunction(int key) const;

public:
    HashTable();
    HashTable(const HashTable& other);
    HashTable& operator=(const HashTable& other);
    ~HashTable();

    void insert(const string& key, const Medicine& value);
    bool search(const string& key, Medicine& value);
    bool searchByName(const string& name, Medicine& value);

    bool contains(const string& key) const;
    bool deleteKey(const string& key);

    void display() const;

    HashNode* getChain(int index) const;
};
