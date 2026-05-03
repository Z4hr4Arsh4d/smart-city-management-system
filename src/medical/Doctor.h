#pragma once
#include <string>
#include <iostream>
using namespace std;

struct Doctor
{
private:
    string doctorID;
    string name;
    string specialization;

public:
    // Constructor
    Doctor(string id = "", string n = "", string spec = "");

    // Setters
    void setDoctorID(string id);
    void setName(string n);
    void setSpecialization(string spec);

    // Getters
    string getDoctorID();
    string getName();
    string getSpecialization();

    // Overloaded output operator
    friend ostream& operator<<(ostream& os, const Doctor& doc);
};
