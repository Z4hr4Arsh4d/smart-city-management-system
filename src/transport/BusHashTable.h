#pragma once
#include <string>
#include <iostream>
#include "Bus.h"

using namespace std;

struct BusNode
{
    Bus* data;
    BusNode* next;

    BusNode(Bus* b);
};

class BusHashTable
{
private:
    BusNode** table;
    int tableSize;
    int itemCount;

    int hash(const string& key) const;
    float loadFactor() const;
    bool needResize() const;
    void resizeTable();

public:
    BusHashTable(int size = 50);
    ~BusHashTable();

    bool insert(Bus* b);
    Bus* search(const string& busNo);
    bool remove(const string& busNo);

    void print() const;
};
