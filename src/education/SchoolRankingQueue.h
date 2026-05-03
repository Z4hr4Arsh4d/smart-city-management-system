#pragma once
#include <iostream>
#include <string>
using namespace std;

#include "School.h"

class SchoolRankingQueue
{
private:
    School** heap;   // dynamic array of School pointers
    int capacity;
    int size;

    void swap(School*& a, School*& b);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    SchoolRankingQueue(int cap = 200);
    ~SchoolRankingQueue();

    void insert(School* s);
    School* extractMax();

    bool isEmpty() const;

    void printRanking();
    void buildRanking(School** arr, int count);
};
