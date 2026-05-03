#pragma once
#include <string>
#include <iostream>
using namespace std;

#include "Doctor.h"

class DoctorList
{
private:
    struct Node
    {
        Doctor data;
        Node* next;
        Node(const Doctor& d);
    };

    Node* head;
    int count;

    void copyFrom(const DoctorList& other);

public:
    // Constructors & destructor
    DoctorList();
    DoctorList(const DoctorList& other);
    DoctorList& operator=(const DoctorList& other);
    ~DoctorList();

    // Core Operations
    void addDoctor(const Doctor& doc);
    bool removeDoctorByID(const string& id);
    bool getDoctorByID(const string& id, Doctor& out) const;
    bool getDoctorByName(const string& name, Doctor& out) const;
    bool containsDoctorID(const string& id) const;

    // Utility
    int size() const;
    bool isEmpty() const;
    void clear();
    void display() const;
};
