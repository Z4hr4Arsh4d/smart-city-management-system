#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Patient
{
public:
    string PatientName;
    int Priototy;


    // Constructor
    Patient(string n = "", int p = 0);

    // Setters
    void setPatientName(string n);
    void setPriototy(int p);

    // Getters
    string getPatientName() const;
    int getPriototy() const;

    // Print operator
    friend ostream& operator<<(ostream& os, const Patient& pat);
};
