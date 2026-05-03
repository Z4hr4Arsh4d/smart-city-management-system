#include "Patient.h"

// ---------------- Constructor ----------------
Patient::Patient(string n, int p)
    : PatientName(n), Priototy(p)
{
}

// ---------------- Setters ----------------
void Patient::setPatientName(string n)
{
    PatientName = n;
}

void Patient::setPriototy(int p)
{
    Priototy = p;
}

// ---------------- Getters ----------------
string Patient::getPatientName() const
{
    return PatientName;
}

int Patient::getPriototy() const
{
    return Priototy;
}

// ---------------- Operator Overload ----------------
ostream& operator<<(ostream& os, const Patient& pat)
{
    os << "Name:" << pat.PatientName
        << " | Prioroty:" << pat.Priototy;
    return os;
}
