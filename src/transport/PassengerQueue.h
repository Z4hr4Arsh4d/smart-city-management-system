#pragma once
#include <iostream>
#include <string>
using namespace std;

class PassengerQueue
{
private:
    string* arr;
    int capacity;
    int front;   // first passenger index
    int rear;    // last passenger index
    int count;   // number of passengers in queue

public:
    PassengerQueue(int cap = 100);
    ~PassengerQueue();

    bool isFull() const;
    bool isEmpty() const;

    bool enqueue(const string& passengerName);
    bool dequeue(string& passengerName);

    string peek() const;
    int size() const;

    void printQueue() const;
};
