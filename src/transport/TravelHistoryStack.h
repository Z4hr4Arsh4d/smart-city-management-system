#pragma once
#include <string>
#include <iostream>
using namespace std;

class TravelHistoryStack
{
private:
    string* arr;
    int capacity;
    int top;    // index of last pushed item

public:
    // Constructor / Destructor
    TravelHistoryStack(int cap = 100);
    ~TravelHistoryStack();

    // Stack operations
    bool isFull() const;
    bool isEmpty() const;

    bool push(const string& location);
    bool pop(string& location);
    string peek() const;

    void printHistory() const;
    void clear();
};
