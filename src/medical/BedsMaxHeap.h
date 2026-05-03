#pragma once
#include <string>
#include <iostream>
using namespace std;

// ---------------------------
// Heap Element
// ---------------------------
struct BedHeapElement
{
    int hospitalID;
    string hospitalName;
    int availableBeds;

    BedHeapElement(int id = -1, string name = "", int beds = 0)
        : hospitalID(id), hospitalName(name), availableBeds(beds) {
    }

    bool operator<(const BedHeapElement& other) const
    {
        return availableBeds < other.availableBeds;
    }

    bool operator>(const BedHeapElement& other) const
    {
        return availableBeds > other.availableBeds;
    }
};

// ---------------------------
// Max-Heap for Hospital Beds
// ---------------------------
class BedsMaxHeap
{
private:
    BedHeapElement* heap;
    int size;
    int capacity;

    int getParent(int index) const;
    int getLeftChild(int index) const;
    int getRightChild(int index) const;

    void swap(BedHeapElement& a, BedHeapElement& b);
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    BedsMaxHeap(int cap = 100);
    ~BedsMaxHeap();

    BedsMaxHeap(const BedsMaxHeap& other);
    BedsMaxHeap& operator=(const BedsMaxHeap& other);

    void insert(int hospitalID, string hospitalName, int availableBeds);
    BedHeapElement extractMax();
    BedHeapElement getMax() const;

    bool updateBeds(int hospitalID, int newBedCount);
    bool contains(int hospitalID) const;
    bool getHospitalByID(int hospitalID, BedHeapElement& result) const;

    void displayHospitalsByBedAvailability() const;
    void getTopHospitalsByBeds(int count) const;

    int getSize() const;
    bool isEmpty() const;
    void clear();
    void displayHeapStructure() const;
};
