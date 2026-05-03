#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Product.h"

class ProductHashTable
{
private:
    struct HashNode
    {
        string key;
        Product value;
        HashNode* next;

        HashNode(const string& k, const Product& v);
    };

    HashNode** table;
    int capacity;

    int hashFunction(const string& key) const;

public:
    ProductHashTable(int cap = 10);
    ~ProductHashTable();

    void insert(const string& key, const Product& value);
    bool search(const string& key, Product& value);
    bool searchByCategory(const string& category, Product& value);

    void display() const;
};
