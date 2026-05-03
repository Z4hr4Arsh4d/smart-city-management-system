#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Patient.h"

class PatientMinHeap
{
private:
    Patient* heap;
    int capacity;
    int size;

    int getParent(int i) const;
    int getLeftChild(int i) const;
    int getRightChild(int i) const;

    bool isHigherPriority(const Patient& a, const Patient& b) const;

    void heapifyUp(int i);
    void heapifyDown(int i);

public:
    PatientMinHeap(int cap = 100);
    ~PatientMinHeap();

    PatientMinHeap(const PatientMinHeap& other);
    PatientMinHeap& operator=(const PatientMinHeap& other);

    void insert(const Patient& patient);
    bool extractMin(Patient& result);
    bool peek(Patient& result) const;

    bool updatePatientPriority(const string& patientName, int newPriority);
    bool containsPatient(const string& patientName) const;

    int getSize() const;
    bool isEmpty() const;

    void display() const;
    void displayHeapStructure() const;

    void getAllPatientsSortedByPriority(Patient* result, int& count) const;
};
