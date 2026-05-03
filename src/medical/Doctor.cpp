#include "Doctor.h"

// ---------------------------
// Constructor
// ---------------------------
Doctor::Doctor(string id, string n, string spec)
{
    doctorID = id;
    name = n;
    specialization = spec;
}

// ---------------------------
// Setters
// ---------------------------
void Doctor::setDoctorID(string id)
{
    doctorID = id;
}

void Doctor::setName(string n)
{
    name = n;
}

void Doctor::setSpecialization(string spec)
{
    specialization = spec;
}

// ---------------------------
// Getters
// ---------------------------
string Doctor::getDoctorID()
{
    return doctorID;
}

string Doctor::getName()
{
    return name;
}

string Doctor::getSpecialization()
{
    return specialization;
}

// ---------------------------
// Operator Overload
// ---------------------------
ostream& operator<<(ostream& os, const Doctor& doc)
{
    os << "ID:" << doc.doctorID
        << " | Name:" << doc.name
        << " | Spec:" << doc.specialization;
    return os;
}
